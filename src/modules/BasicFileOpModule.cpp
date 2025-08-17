#include "PCH.hpp"
#include "modules/BasicFileOpModule.hpp"
#include "utilitys/DialogOptBuilder.hpp"


namespace fs = std::filesystem;

BasicFileOpModule::BasicFileOpModule(wxWindow* window, wxPanel* panel) : BaseModule(wxString("Basic File operations"), wxVERTICAL, window)
{
	SetModuleSizer<wxGridSizer>(2, 2, 4, 4);

	AddControl<wxButton>("create_BTN", wxSizerFlags(), panel, ECREATE_BUTTON, "Create File");
	AddControl<wxButton>("delete_BTN",wxSizerFlags(), panel, EDELETE_BUTTON, "Delete File");
	AddControl<wxButton>("move_BTN", wxSizerFlags(), panel, EMOVE_BUTTON, "Move File");
	AddControl<wxButton>("copy_BTN", wxSizerFlags(), panel, ECOPY_BUTTON, "Copy File");

	BindEvent("create_BTN", wxEVT_BUTTON, &BasicFileOpModule::OnPressCreateFile, this, ECREATE_BUTTON);
	BindEvent("delete_BTN", wxEVT_BUTTON, &BasicFileOpModule::OnPressDelteteFile, this, EDELETE_BUTTON);

	BuildAllLayouts();
}

void BasicFileOpModule::HandleCreateFile(wxCommandEvent& evt)
{
	std::string filePath = optDialogCreateFile->GetControl<wxTextCtrl>("inputFilePath")->GetValue();
	std::string fileName = optDialogCreateFile->GetControl<wxTextCtrl>("inputFileName")->GetValue();
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
	BuildDeleteLayout();
}

void BasicFileOpModule::BuildCreateFileLayout()
{
	optDialogCreateFile = new DialogOptBuilder(GetApplicationWindow(), wxID_ANY, "Create a file");

	optDialogCreateFile->SetBaseSizer<wxBoxSizer>(wxVERTICAL);

	optDialogCreateFile->AddStrechSpacer("base");

	optDialogCreateFile->AddSizer<wxBoxSizer>("filePathSizer", "base", wxSizerFlags().CentreHorizontal().Border(wxUP, 10), wxHORIZONTAL);
	optDialogCreateFile->AddControl<wxStaticText>("filePathText", "filePathSizer", wxSizerFlags(), wxID_ANY, "Directory: ");
	optDialogCreateFile->AddControl<wxTextCtrl>("inputFilePath", "filePathSizer", wxSizerFlags(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(200, wxDefaultSize.y));
	optDialogCreateFile->AddControl<wxButton>("showFileDiaBtn", "filePathSizer", wxSizerFlags(), ESHOW_DIR_DIA_CREATE, "Show Directory Dialog");
	optDialogCreateFile->Bind(wxEVT_BUTTON, [&](wxCommandEvent& evt)
		{
			wxDirDialog* dirDia = new wxDirDialog(optDialogCreateFile, "Search for a Directory to place the new File", wxEmptyString, wxDD_DIR_MUST_EXIST);

			dirDia->ShowModal();

			optDialogCreateFile->GetControl<wxTextCtrl>("inputFilePath")->SetValue(dirDia->GetPath());
		}, ESHOW_DIR_DIA_CREATE);


	optDialogCreateFile->AddSizer<wxBoxSizer>("fileNameSizer", "base", wxSizerFlags().CentreHorizontal().Border(wxUP, 10), wxHORIZONTAL);
	optDialogCreateFile->AddControl<wxStaticText>("fileNameText", "fileNameSizer", wxSizerFlags(), wxID_ANY, "File Name: ");
	optDialogCreateFile->AddControl<wxTextCtrl>("inputFileName", "fileNameSizer", wxSizerFlags(), wxID_ANY);

	optDialogCreateFile->AddSizer<wxBoxSizer>("checkButtonsSizer", "base", wxSizerFlags().CentreHorizontal().Border(wxUP, 10), wxHORIZONTAL);
	optDialogCreateFile->AddControl<wxButton>("confirmButton", "checkButtonsSizer", wxSizerFlags(), ECONFIRM_CREATE, "confirm");
	optDialogCreateFile->AddControl<wxButton>("cancelButton", "checkButtonsSizer", wxSizerFlags(), ECANCEL_CREATE, "cancel");

	optDialogCreateFile->Bind(wxEVT_BUTTON, &BasicFileOpModule::HandleCreateFile, this, ECONFIRM_CREATE);

	optDialogCreateFile->Bind(wxEVT_BUTTON, [&](wxCommandEvent& evt)
		{
			optDialogCreateFile->Close();

		}, ECANCEL_CREATE);

	optDialogCreateFile->AddStrechSpacer("base");
	optDialogCreateFile->RefreshLayout();
	
}

void BasicFileOpModule::BuildDeleteLayout()
{
	optDialogDeleteFile = new DialogOptBuilder(GetApplicationWindow(), wxID_ANY, "Delete Files or directorys", wxDefaultPosition, wxSize(450, 400));

	optDialogDeleteFile->SetBaseSizer<wxBoxSizer>(wxVERTICAL);

	optDialogDeleteFile->AddStrechSpacer("base");

	optDialogDeleteFile->AddSizer<wxBoxSizer>("filePathSizer", "base", wxSizerFlags().CentreHorizontal().Border(wxUP, 10), wxHORIZONTAL);
	optDialogDeleteFile->AddControl<wxStaticText>("filePathText", "filePathSizer", wxSizerFlags(), wxID_ANY, "Directory: ");
	optDialogDeleteFile->AddControl<wxTextCtrl>("inputFilePath", "filePathSizer", wxSizerFlags(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(200, wxDefaultSize.y));
	optDialogDeleteFile->AddControl<wxButton>("showFileDiaBtn", "filePathSizer", wxSizerFlags(), ESHOW_DIR_DIA_DELETE, "Show Directory Dialog");
	optDialogDeleteFile->Bind(wxEVT_BUTTON, [&](wxCommandEvent& evt)
		{
			wxDirDialog* dirDia = new wxDirDialog(optDialogDeleteFile, "Search for a Directory to place the new File", wxEmptyString, wxDD_DIR_MUST_EXIST);

			dirDia->ShowModal();

			optDialogDeleteFile->GetControl<wxTextCtrl>("inputFilePath")->SetValue(dirDia->GetPath());
				
			for (const auto& item : fs::directory_iterator(dirDia->GetPath().ToStdString()))
			{
				optDialogDeleteFile->GetControl<wxCheckListBox>("checkList")->Append(fs::path(item).filename().u8string());
			}
			
		}, ESHOW_DIR_DIA_DELETE);
	
	optDialogDeleteFile->AddControl<wxCheckListBox>("checkList", "base", wxSizerFlags().CenterHorizontal().Border(wxUP, 10), ECHECKLIST_DELETE, wxDefaultPosition, wxSize(400, 200));
	
	optDialogDeleteFile->AddSizer<wxBoxSizer>("checkButtonsSizer", "base", wxSizerFlags().CentreHorizontal().Border(wxUP, 10), wxHORIZONTAL);
	optDialogDeleteFile->AddControl<wxButton>("confirmButton", "checkButtonsSizer", wxSizerFlags(), ECONFIRM_CREATE, "confirm");
	optDialogDeleteFile->AddControl<wxButton>("cancelButton", "checkButtonsSizer", wxSizerFlags(), ECANCEL_CREATE, "cancel");

	//optDialogDeleteFile->Bind(wxEVT_BUTTON, &BasicFileOpModule::HandleCreateFile, this, ECONFIRM);

	optDialogDeleteFile->Bind(wxEVT_BUTTON, [&](wxCommandEvent& evt)
		{
			optDialogDeleteFile->Close();

		}, ECANCEL_CREATE);

	optDialogDeleteFile->AddStrechSpacer("base");
	optDialogDeleteFile->RefreshLayout();
}

void BasicFileOpModule::OnPressCreateFile(wxCommandEvent& evt)
{
	optDialogCreateFile->ShowModal();
}
void BasicFileOpModule::OnPressDelteteFile(wxCommandEvent& evt)
{
	optDialogDeleteFile->ShowModal();
}