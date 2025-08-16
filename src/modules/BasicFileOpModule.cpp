#include "PCH.hpp"
#include "modules/BasicFileOpModule.hpp"
#include "utilitys/DialogOptBuilder.hpp"


namespace fs = std::filesystem;

BasicFileOpModule::BasicFileOpModule(wxWindow* window, wxPanel* panel) : BaseModule(wxString("Basic File operations"), wxVERTICAL, window)
{
	SetModuleSizer<wxGridSizer>(2, 2, 4, 4);

	AddControl<wxButton>(wxSizerFlags(), panel, ECREATE_BUTTON, "Create File");
	AddControl<wxButton>(wxSizerFlags(), panel, EDELETE_BUTTON, "Delete File");
	AddControl<wxButton>(wxSizerFlags(), panel, EMOVE_BUTTON, "Move File");
	AddControl<wxButton>(wxSizerFlags(), panel, ECOPY_BUTTON, "Copy File");

	BuildAllLayouts();
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
