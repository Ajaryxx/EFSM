#include "PCH.hpp"
#include "modules/BasicFileOpModule.hpp"
#include "utilitys/DialogOptBuilder.hpp"
#include "utilitys/FilePathSearchUtility.hpp"


namespace fs = std::filesystem;

BasicFileOpModule::BasicFileOpModule(wxWindow* window, wxPanel* panel) : BaseModule(wxString("Basic File operations"), wxVERTICAL, window)
{
	SetModuleSizer<wxGridSizer>(2, 2, 4, 4);

	AddControl<wxButton>("create_BTN", wxSizerFlags(), panel, ECREATE_BUTTON, "Create File");
	AddControl<wxButton>("delete_BTN",wxSizerFlags(), panel, EDELETE_BUTTON, "Delete File");
	AddControl<wxButton>("move_BTN", wxSizerFlags(), panel, EMOVE_BUTTON, "Move File");
	AddControl<wxButton>("copy_BTN", wxSizerFlags(), panel, ECOPY_BUTTON, "Copy File");

	BindEvent("create_BTN", wxEVT_BUTTON, &BasicFileOpModule::OnPressCreateFile, this, ECREATE_BUTTON);
	BindEvent("delete_BTN", wxEVT_BUTTON, &BasicFileOpModule::OnPressDelete, this, EDELETE_BUTTON);

	BuildAllLayouts();
}

void BasicFileOpModule::HandleCreateFile(wxCommandEvent& evt)
{
	std::string filePath = optDialogCreateFile->GetControl<wxTextCtrl>("inputFilePath")->GetValue();
	std::string fileName = optDialogCreateFile->GetControl<wxTextCtrl>("inputFileName")->GetValue();
	if (fs::exists(filePath) && !fileName.empty())
	{
		fs::path newFilePath = fs::path(filePath) / fs::path(fileName);
		if (fs::exists(newFilePath))
		{
			int result = wxMessageBox("There is another file with the same name. Do you want to override it?", "Info", wxICON_QUESTION | wxOK | wxCANCEL);
			if (result == wxCANCEL)
			{
				return;
			}
		}
		
		std::ofstream file(newFilePath.u8string());

		file.close();

		wxMessageBox("File created succesfuly :)", "Info", wxICON_INFORMATION);

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

			int result = dirDia->ShowModal();
			if (result == wxID_CANCEL)
				return;

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

	//filePath input box stuff
	optDialogDeleteFile->AddSizer<wxBoxSizer>("filePathSizer", "base", wxSizerFlags().CentreHorizontal().Border(wxUP, 10), wxHORIZONTAL);
	optDialogDeleteFile->AddControl<wxStaticText>("filePathText", "filePathSizer", wxSizerFlags(), wxID_ANY, "Directory: ");
	optDialogDeleteFile->AddControl<wxTextCtrl>("inputFilePath", "filePathSizer", wxSizerFlags(), EDIR_PATH_INPUT, wxEmptyString, wxDefaultPosition, wxSize(200, wxDefaultSize.y));
	optDialogDeleteFile->AddControl<wxButton>("showFileDiaBtn", "filePathSizer", wxSizerFlags(), ESHOW_DIR_DIA_DELETE, "Show Directory Dialog");

	//searchbar input box stuff
	optDialogDeleteFile->AddSizer<wxBoxSizer>("searchBarSizer", "base", wxSizerFlags().Border(wxUP | wxLEFT, 10), wxHORIZONTAL);
	optDialogDeleteFile->AddControl<wxStaticText>("searchBarText", "searchBarSizer", wxSizerFlags(), wxID_ANY, "Search for a File or Directory: ");
	optDialogDeleteFile->AddControl<wxTextCtrl>("searchBar", "searchBarSizer", wxSizerFlags(), ESEARCH_INPUT, wxEmptyString, wxDefaultPosition, wxSize(150, wxDefaultSize.y));

	//check List
	optDialogDeleteFile->AddControl<wxCheckListBox>("checkList", "base", wxSizerFlags().CenterHorizontal().Border(wxUP, 10), ECHECKLIST_DELETE, wxDefaultPosition, wxSize(400, 200));
	
	//check btns
	optDialogDeleteFile->AddSizer<wxBoxSizer>("checkButtonsSizer", "base", wxSizerFlags().CentreHorizontal().Border(wxUP, 10), wxHORIZONTAL);
	optDialogDeleteFile->AddControl<wxButton>("confirmButton", "checkButtonsSizer", wxSizerFlags(), ECONFIRM_DELETE, "confirm");
	optDialogDeleteFile->AddControl<wxButton>("cancelButton", "checkButtonsSizer", wxSizerFlags(), ECANCEL_DELETE, "cancel");

	//Events
	//Show Directory Dialog
	optDialogDeleteFile->Bind(wxEVT_BUTTON, &BasicFileOpModule::HandleShowDeleteDirectoryDialog, this, ESHOW_DIR_DIA_DELETE);
	//When pressing confirm btn
	optDialogDeleteFile->Bind(wxEVT_BUTTON, &BasicFileOpModule::HandleDelete, this, ECONFIRM_DELETE);
	//If typed smthing in DirectoryPath
	optDialogDeleteFile->Bind(wxEVT_TEXT, [&](wxCommandEvent& evt) { ListElements(optDialogDeleteFile->GetControl<wxTextCtrl>("inputFilePath")->GetValue()); }, EDIR_PATH_INPUT);
	//If typed smthing in searchBar
	optDialogDeleteFile->Bind(wxEVT_TEXT, &BasicFileOpModule::HandleSearchbarType, this, ESEARCH_INPUT);
	//If checked a element in CheckBox
	optDialogDeleteFile->Bind(wxEVT_CHECKLISTBOX, &BasicFileOpModule::HandleCheckElementDeleteList, this, ECHECKLIST_DELETE);
	optDialogDeleteFile->Bind(wxEVT_BUTTON, [&](wxCommandEvent& evt){ optDialogDeleteFile->Close(); }, ECANCEL_DELETE);

	optDialogDeleteFile->AddStrechSpacer("base");
	optDialogDeleteFile->RefreshLayout();
}

void BasicFileOpModule::OnPressCreateFile(wxCommandEvent& evt)
{
	optDialogCreateFile->ShowModal();
}

void BasicFileOpModule::OnPressDelete(wxCommandEvent& evt)
{
	optDialogDeleteFile->ShowModal();
}

void BasicFileOpModule::HandleDelete(wxCommandEvent& evt)
{
	wxCheckListBox* chkLst = optDialogDeleteFile->GetControl<wxCheckListBox>("checkList");
	bool AnyChecked = false;

	optDialogDeleteFile->GetControl<wxTextCtrl>("searchBar")->SetValue("");
	

	for (size_t i = 0; i < chkLst->GetCount(); i++)
	{
		if (chkLst->IsChecked(i))
		{
			AnyChecked = true;
		}
	}
	
	if (chkLst->IsEmpty() || !AnyChecked)
		return;

	int res = wxMessageBox("ARE YOU SURE YOU WANT TO DELETE THOSE FILES/DIRECTORYS? THIS CANNOT BE UNDONE!", "WARNING!", wxOK | wxCANCEL);

	if (res == wxOK)
	{
		std::vector<std::string> toDelete;

		for (size_t i = 0; i < chkLst->GetCount(); i++)
		{
			if (chkLst->IsChecked(i))
			{
				toDelete.push_back(chkLst->GetString(i).ToStdString());
			}
		}

		for (const auto& item : toDelete)
		{
			if (fs::is_directory(item))
			{
				fs::remove_all(item);
			}
			else if (fs::is_regular_file(item) || fs::is_symlink(item))
			{
				fs::remove(item);
			}
			else
			{
				//uhhh wtf is this
			}
		}
		//Clear the checked items in the list
		for (const auto& item : toDelete)
		{
			int pos = chkLst->FindString(item);
			chkLst->Delete(pos);
		}
		m_v_pathCheck.clear();
		ListElements(m_CurrentDeletePath);
	}
	
}

void BasicFileOpModule::HandleCheckElementDeleteList(wxCommandEvent& evt)
{
	wxCheckListBox* chkLst = optDialogDeleteFile->GetControl<wxCheckListBox>("checkList");
	
	for (size_t i = 0; i < chkLst->GetCount(); i++)
	{
		wxString string = chkLst->GetString(i);

		if (chkLst->IsChecked(chkLst->FindString(string)))
		{
			for (auto& item : m_v_pathCheck)
			{
				if (item.path == string)
				{
					item.checked = true;
				}
			}
		}
		else
		{
			for (auto& item : m_v_pathCheck)
			{
				if (item.path == string)
				{
					item.checked = false;
				}
			}
		}
	}

}

void BasicFileOpModule::HandleShowDeleteDirectoryDialog(wxCommandEvent& evt)
{
	wxDirDialog* dirDia = new wxDirDialog(optDialogDeleteFile, "Search for a Directory to place the delete Files or Directorys", wxEmptyString, wxDD_DIR_MUST_EXIST);

	int result = dirDia->ShowModal();
	if (result == wxID_CANCEL)
		return;

	m_CurrentDeletePath = dirDia->GetPath();

	optDialogDeleteFile->GetControl<wxTextCtrl>("inputFilePath")->SetValue(m_CurrentDeletePath);
	ListElements(m_CurrentDeletePath);
}

void BasicFileOpModule::HandleSearchbarType(wxCommandEvent& evt)
{
	wxCheckListBox* chkLst = optDialogDeleteFile->GetControl<wxCheckListBox>("checkList");
	wxTextCtrl* searchBar = optDialogDeleteFile->GetControl<wxTextCtrl>("searchBar");
	if (searchBar->GetValue().IsEmpty())
	{
		TransferToMain();
		return;	
	}

	std::vector<wxString> searchedPaths = FilePathSearchUtilty::SearchDirPath(m_CurrentDeletePath, searchBar->GetValue());
	if (searchedPaths.empty())
		return;

	chkLst->Clear();
	for (const auto& string : searchedPaths)
	{
		int i = chkLst->Append(string);

		for (const auto& item : m_v_pathCheck)
		{
			if (item.path == chkLst->GetString(i))
			{
				
				chkLst->Check(i, item.checked);
				
			}
		}
		
	}
}

void BasicFileOpModule::ListElements(const wxString& path)
{
	wxCheckListBox* chkLst = optDialogDeleteFile->GetControl<wxCheckListBox>("checkList");
	m_CurrentDeletePath = path;
	if (!fs::exists(path.ToStdWstring()))
	{
		m_v_pathCheck.clear();
		chkLst->Clear();
		return;
	}
		
	//make sure we clear the last entries
	chkLst->Clear();
	m_v_pathCheck.clear();

	for (const auto& item : fs::directory_iterator(path.ToStdString()))
	{
		chkLst->Append(fs::path(item).wstring());
		//make a copy so we can handle element checks easier
		m_v_pathCheck.push_back(PathCheck{ item.path().wstring(), false});
	}
}

void BasicFileOpModule::TransferToMain()
{
	wxCheckListBox* chkLst = optDialogDeleteFile->GetControl<wxCheckListBox>("checkList");
	chkLst->Clear();
	for (const auto& item : m_v_pathCheck)
	{
		int i = chkLst->Append(item.path);

		chkLst->Check(i, item.checked);
	}
}
