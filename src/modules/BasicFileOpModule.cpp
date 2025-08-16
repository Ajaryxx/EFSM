#include "PCH.hpp"
#include "modules/BasicFileOpModule.hpp"
#include "utilitys/DialogOptBuilder.hpp"


namespace fs = std::filesystem;

BasicFileOpModule::BasicFileOpModule(wxWindow* window, wxPanel* panel) : BaseModule(wxString("Basic File operations"), wxVERTICAL, window)
{

	SetModuleSizer<wxGridSizer>(2, 2, 4, 4);

	BuildAllLayouts();


	m_CreateButton = new wxButton(panel, ECREATE_BUTTON, "Create File");
	m_DeleteButton = new wxButton(panel, EDELETE_BUTTON, "Delete File");
	m_MoveButton = new wxButton(panel, EMOVE_BUTTON, "Move File");
	m_CopyButton = new wxButton(panel, ECOPY_BUTTON, "Copy File");

	AddControl(m_CreateButton);
	AddControl(m_DeleteButton);
	AddControl(m_MoveButton);
	AddControl(m_CopyButton);

	m_CreateButton->Bind(wxEVT_BUTTON, &BasicFileOpModule::OnPressCreateFile, this);
}

void BasicFileOpModule::HandleCreateFile(wxCommandEvent& evt)
{
	std::string filePath = optDialogCreateFile->GetValue<wxTextCtrl, wxString>("inputFilePath").ToStdString();
	std::string fileName = optDialogCreateFile->GetValue<wxTextCtrl, wxString>("inputFileName").ToStdString();
	if (fs::exists(filePath) && !fileName.empty())
	{
		std::ofstream file(fs::path(filePath) / fs::path(fileName));

		file.close();
		optDialogCreateFile->Close();
	}
	else
	{
		wxMessageBox("File Path does not exists or File Name can not be empty", "Warning");
	}
}

void BasicFileOpModule::BuildAllLayouts()
{
	BuildCreateFileLayout();
}

void BasicFileOpModule::BuildCreateFileLayout()
{
	optDialogCreateFile = new DialogOptBuilder(GetApplicationWindow(), wxID_ANY, "Create a file");

	optDialogCreateFile->SetBaseSizer<wxBoxSizer>(wxVERTICAL);

	optDialogCreateFile->AddStrechSpacer("base");

	optDialogCreateFile->AddSizer<wxBoxSizer>("filePathSizer", "base", wxSizerFlags().CentreHorizontal().Border(wxUP, 10), wxHORIZONTAL);
	optDialogCreateFile->AddControl<wxStaticText>("filePathText", "filePathSizer", wxSizerFlags(), wxID_ANY, "Filepath: ");
	optDialogCreateFile->AddControl<wxTextCtrl>("inputFilePath", "filePathSizer", wxSizerFlags(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(200, wxDefaultSize.y));
	optDialogCreateFile->AddControl<wxButton>("showFileDiaBtn", "filePathSizer", wxSizerFlags(), ESHOW_DIR_DIA, "Show Directory Dialog");
	optDialogCreateFile->Bind(wxEVT_BUTTON, [&](wxCommandEvent& evt)
		{
			wxDirDialog* dirDia = new wxDirDialog(optDialogCreateFile, "Search for a Directory to place the new File", wxEmptyString, wxDD_DIR_MUST_EXIST);

			dirDia->ShowModal();

			optDialogCreateFile->SetValue<wxTextCtrl, wxString>("inputFilePath", dirDia->GetPath());
		}, ESHOW_DIR_DIA);


	optDialogCreateFile->AddSizer<wxBoxSizer>("fileNameSizer", "base", wxSizerFlags().CentreHorizontal().Border(wxUP, 10), wxHORIZONTAL);
	optDialogCreateFile->AddControl<wxStaticText>("fileNameText", "fileNameSizer", wxSizerFlags(), wxID_ANY, "File Name: ");
	optDialogCreateFile->AddControl<wxTextCtrl>("inputFileName", "fileNameSizer", wxSizerFlags(), wxID_ANY);

	optDialogCreateFile->AddSizer<wxBoxSizer>("checkButtonsSizer", "base", wxSizerFlags().CentreHorizontal().Border(wxUP, 10), wxHORIZONTAL);
	optDialogCreateFile->AddControl<wxButton>("confirmButton", "checkButtonsSizer", wxSizerFlags(), ECONFIRM, "confirm");
	optDialogCreateFile->AddControl<wxButton>("cancelButton", "checkButtonsSizer", wxSizerFlags(), ECANCEL, "cancel");

	optDialogCreateFile->Bind(wxEVT_BUTTON, &BasicFileOpModule::HandleCreateFile, this, ECONFIRM);

	optDialogCreateFile->Bind(wxEVT_BUTTON, [&](wxCommandEvent& evt)
		{
			optDialogCreateFile->Close();

		}, ECANCEL);

	optDialogCreateFile->AddStrechSpacer("base");
	optDialogCreateFile->RefreshLayout();
	
}

void BasicFileOpModule::OnPressCreateFile(wxCommandEvent& evt)
{
	optDialogCreateFile->ShowModal();
}
