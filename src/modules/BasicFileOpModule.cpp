#include "PCH.hpp"
#include "modules/BasicFileOpModule.hpp"
#include "utilitys/WindowToolDialog.hpp"
#include "utilitys/FilePathSearchUtility.hpp"


namespace fs = std::filesystem;

BasicFileOpModule::BasicFileOpModule(wxWindow* window) : BaseModule(wxString("Basic File operations"), wxVERTICAL, window)
{	

	AddControl<wxButton>("create_BTN", "base", wxSizerFlags(), ECREATE_BUTTON, "Create");
	AddControl<wxButton>("delete_BTN", "base", wxSizerFlags(), EDELETE_BUTTON, "Delete");
	AddControl<wxButton>("copyOption_BTN", "base", wxSizerFlags().Align(wxHORIZONTAL), ECOPY_OPTION_BUTTON, "Copy Option");
	
	/*
	BuildAllLayouts();

	GetControl<wxButton>("create_BTN")->Bind(wxEVT_BUTTON, [&](wxCommandEvent) {m_optDialogCreateFile->ShowModal(); }, ECREATE_BUTTON);
	GetControl<wxButton>("create_BTN")->Bind( wxEVT_BUTTON, [&](wxCommandEvent) {m_optDialogDeleteFile->ShowModal(); }, EDELETE_BUTTON);
	GetControl<wxButton>("create_BTN")->Bind(wxEVT_BUTTON, [&](wxCommandEvent) {m_optDialogMoveCopyFile->ShowModal(); }, ECOPY_OPTION_BUTTON);
	*/
}

void BasicFileOpModule::BuildAllLayouts()
{
	BuildCreateFileLayout();
	BuildDeleteLayout();
	BuildMoveCopyLayout();
}

void BasicFileOpModule::BuildCreateFileLayout()
{
	m_optDialogCreateFile = new WindowToolDialog(GetApplicationWindow(), wxID_ANY, "Create a File or a Directory");
	
	m_optDialogCreateFile->SetBaseSizer<wxBoxSizer>(wxVERTICAL);

	m_optDialogCreateFile->AddStrechSpacer("base");

	m_optDialogCreateFile->AddSizer<wxBoxSizer>("radioBoxSizer", "base", wxSizerFlags().CentreHorizontal(), wxVERTICAL);
	m_optDialogCreateFile->AddControl<wxRadioBox>("RadioBoxCreate", "radioBoxSizer", wxSizerFlags().CenterHorizontal(), ERADIO_BOX, 
		"Choose a Option: ", wxDefaultPosition, wxDefaultSize, wxArrayString{"Folder", "File"});

	m_optDialogCreateFile->AddSizer<wxBoxSizer>("filePathSizer", "base", wxSizerFlags().CentreHorizontal().Border(wxUP, 10), wxHORIZONTAL);
	m_optDialogCreateFile->AddControl<wxStaticText>("filePathText", "filePathSizer", wxSizerFlags(), wxID_ANY, "Directory: ");
	m_optDialogCreateFile->AddControl<wxTextCtrl>("inputFilePath", "filePathSizer", wxSizerFlags(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(200, wxDefaultSize.y));
	m_optDialogCreateFile->AddControl<wxButton>("showFileDiaBtn", "filePathSizer", wxSizerFlags(), ESHOW_DIR_DIA_CREATE, "Show Directory Dialog");
	
	m_optDialogCreateFile->Bind(wxEVT_BUTTON, [&](wxCommandEvent& evt)
		{
			wxDirDialog* dirDia = new wxDirDialog(m_optDialogCreateFile, "Search for a Directory to place the new File", wxEmptyString, wxDD_DIR_MUST_EXIST);

			int result = dirDia->ShowModal();
			if (result == wxID_CANCEL)
				return;

			m_optDialogCreateFile->GetControl<wxTextCtrl>("inputFilePath")->SetValue(dirDia->GetPath());
		}, ESHOW_DIR_DIA_CREATE);


	m_optDialogCreateFile->AddSizer<wxBoxSizer>("fileNameSizer", "base", wxSizerFlags().CentreHorizontal().Border(wxUP, 10), wxHORIZONTAL);
	m_optDialogCreateFile->AddControl<wxStaticText>("fileNameText", "fileNameSizer", wxSizerFlags(), wxID_ANY, "Name: ");
	m_optDialogCreateFile->AddControl<wxTextCtrl>("inputFileName", "fileNameSizer", wxSizerFlags(), wxID_ANY);

	m_optDialogCreateFile->AddSizer<wxBoxSizer>("checkButtonsSizer", "base", wxSizerFlags().CentreHorizontal().Border(wxUP, 10), wxHORIZONTAL);
	m_optDialogCreateFile->AddControl<wxButton>("confirmButton", "checkButtonsSizer", wxSizerFlags(), ECONFIRM_CREATE, "confirm");
	m_optDialogCreateFile->AddControl<wxButton>("cancelButton", "checkButtonsSizer", wxSizerFlags(), ECANCEL_CREATE, "cancel");

	m_optDialogCreateFile->Bind(wxEVT_BUTTON, &BasicFileOpModule::HandleCreateFile, this, ECONFIRM_CREATE);

	m_optDialogCreateFile->Bind(wxEVT_BUTTON, [&](wxCommandEvent& evt)
		{
			m_optDialogCreateFile->Close();

		}, ECANCEL_CREATE);

	m_optDialogCreateFile->AddStrechSpacer("base");
	m_optDialogCreateFile->RefreshLayout();
	
}

void BasicFileOpModule::HandleCreateFile(wxCommandEvent& evt)
{

	std::string filePath = m_optDialogCreateFile->GetControl<wxTextCtrl>("inputFilePath")->GetValue();
	std::string fileName = m_optDialogCreateFile->GetControl<wxTextCtrl>("inputFileName")->GetValue();



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

		wxRadioBox* rdbx = m_optDialogCreateFile->GetControl<wxRadioBox>("RadioBoxCreate");
		if (rdbx->GetStringSelection() == "Folder")
		{
			try
			{
				fs::create_directory(newFilePath);
				wxMessageBox("Folder created succesfuly :)", "Info", wxICON_INFORMATION);
			}
			catch (const std::system_error::exception& exc)
			{
				wxMessageBox(wxString("ERROR: ") + exc.what(), "ERROR", wxICON_ERROR);
			}

		}
		else if (rdbx->GetStringSelection() == "File")
		{
			std::ofstream file;
			file.exceptions(std::ios_base::badbit | std::ios_base::failbit);
			try
			{
				file.open(newFilePath.u8string());

				file.close();

				wxMessageBox("File created succesfuly :)", "Info", wxICON_INFORMATION);
			}
			catch (const std::system_error::exception& exc)
			{
				wxMessageBox(wxString("ERROR: ") + exc.what(), "ERROR", wxICON_ERROR);
			}
		}
	}
	else
	{
		wxMessageBox("File Path does not exists or File Name can not be empty", "Warning");
	}
}

void BasicFileOpModule::BuildDeleteLayout()
{
	m_optDialogDeleteFile = new WindowToolDialog(GetApplicationWindow(), wxID_ANY, "Delete Files or directorys", wxDefaultPosition, wxSize(450, 400));
	
	m_optDialogDeleteFile->SetBaseSizer<wxBoxSizer>(wxVERTICAL);

	m_optDialogDeleteFile->AddStrechSpacer("base");

	//filePath input box stuff
	m_optDialogDeleteFile->AddSizer<wxBoxSizer>("filePathSizer", "base", wxSizerFlags().CentreHorizontal().Border(wxUP, 10), wxHORIZONTAL);
	m_optDialogDeleteFile->AddControl<wxStaticText>("filePathText", "filePathSizer", wxSizerFlags(), wxID_ANY, "Directory: ");
	m_optDialogDeleteFile->AddControl<wxTextCtrl>("inputFilePath", "filePathSizer", wxSizerFlags(), EDIR_PATH_INPUT, wxEmptyString, wxDefaultPosition, wxSize(200, wxDefaultSize.y));
	m_optDialogDeleteFile->AddControl<wxButton>("showFileDiaBtn", "filePathSizer", wxSizerFlags(), ESHOW_DIR_DIA_DELETE, "Show Directory Dialog");

	//searchbar input box stuff
	m_optDialogDeleteFile->AddSizer<wxBoxSizer>("searchBarSizer", "base", wxSizerFlags().Border(wxUP | wxLEFT, 10), wxHORIZONTAL);
	m_optDialogDeleteFile->AddControl<wxStaticText>("searchBarText", "searchBarSizer", wxSizerFlags(), wxID_ANY, "Search for a File or Directory: ");
	m_optDialogDeleteFile->AddControl<wxTextCtrl>("searchBar", "searchBarSizer", wxSizerFlags(), ESEARCH_INPUT, wxEmptyString, wxDefaultPosition, wxSize(150, wxDefaultSize.y));

	//check List
	m_optDialogDeleteFile->AddControl<wxCheckListBox>("checkList", "base", wxSizerFlags().CenterHorizontal().Border(wxUP, 10), ECHECKLIST_DELETE, wxDefaultPosition, wxSize(400, 200));
	
	//check btns
	m_optDialogDeleteFile->AddSizer<wxBoxSizer>("checkButtonsSizer", "base", wxSizerFlags().CentreHorizontal().Border(wxUP, 10), wxHORIZONTAL);
	m_optDialogDeleteFile->AddControl<wxButton>("confirmButton", "checkButtonsSizer", wxSizerFlags(), ECONFIRM_DELETE, "confirm");
	m_optDialogDeleteFile->AddControl<wxButton>("cancelButton", "checkButtonsSizer", wxSizerFlags(), ECANCEL_DELETE, "cancel");

	//Events
	//Show Directory Dialog
	m_optDialogDeleteFile->Bind(wxEVT_BUTTON, &BasicFileOpModule::HandleShowDeleteDirectoryDialog, this, ESHOW_DIR_DIA_DELETE);
	//When pressing confirm btn
	m_optDialogDeleteFile->Bind(wxEVT_BUTTON, &BasicFileOpModule::HandleDelete, this, ECONFIRM_DELETE);
	//If typed smthing in DirectoryPath TextCtrl
	m_optDialogDeleteFile->Bind(wxEVT_TEXT, [&](wxCommandEvent& evt) { ListElements(m_optDialogDeleteFile->GetControl<wxTextCtrl>("inputFilePath")->GetValue()); }, EDIR_PATH_INPUT);
	//If typed smthing in searchBar
	m_optDialogDeleteFile->Bind(wxEVT_TEXT, &BasicFileOpModule::HandleSearchbarType, this, ESEARCH_INPUT);
	//If checked a element in CheckBox
	m_optDialogDeleteFile->Bind(wxEVT_CHECKLISTBOX, &BasicFileOpModule::HandleCheckElementDeleteList, this, ECHECKLIST_DELETE);
	m_optDialogDeleteFile->Bind(wxEVT_BUTTON, [&](wxCommandEvent& evt){ m_optDialogDeleteFile->Close(); }, ECANCEL_DELETE);

	m_optDialogDeleteFile->AddStrechSpacer("base");
	m_optDialogDeleteFile->RefreshLayout();
}

void BasicFileOpModule::BuildMoveCopyLayout()
{
	m_optDialogMoveCopyFile = new WindowToolDialog(GetApplicationWindow(), wxID_ANY, "Copy/Move File operation");
}

void BasicFileOpModule::HandleDelete(wxCommandEvent& evt)
{
	wxCheckListBox* chkLst = m_optDialogDeleteFile->GetControl<wxCheckListBox>("checkList");
	bool AnyChecked = false;

	m_optDialogDeleteFile->GetControl<wxTextCtrl>("searchBar")->SetValue("");
	

	for (size_t i = 0; i < chkLst->GetCount(); i++)
	{
		if (chkLst->IsChecked(i))
		{
			AnyChecked = true;
		}
	}
	
	if (!AnyChecked)
		return;

	int res = wxMessageBox("ARE YOU SURE YOU WANT TO DELETE THOSE FILES/DIRECTORYS? THIS CANNOT BE UNDONE!", "WARNING!", wxOK | wxCANCEL);

	if (res == wxOK)
	{
		std::vector<std::wstring> toDelete;

		for (size_t i = 0; i < chkLst->GetCount(); i++)
		{
			if (chkLst->IsChecked(i))
			{
				toDelete.push_back(chkLst->GetString(i).ToStdWstring());
			}
		}

		for (const auto& item : toDelete)
		{
			try
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
			catch (const std::system_error::exception& exc)
			{
				wxMessageBox(wxString("Couldnt delete: ") + item + wxString(" because: ") + exc.what(), "ERROR", wxICON_ERROR);
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
	wxCheckListBox* chkLst = m_optDialogDeleteFile->GetControl<wxCheckListBox>("checkList");

	for (size_t i = 0; i < chkLst->GetCount(); i++)
	{
		wxString string = chkLst->GetString(i);
		int index = chkLst->FindString(string);
		if (chkLst->IsChecked(index))
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
	wxDirDialog* dirDia = new wxDirDialog(m_optDialogDeleteFile, "Search for a Directory to place the delete Files or Directorys", wxEmptyString, wxDD_DIR_MUST_EXIST);

	int result = dirDia->ShowModal();
	if (result == wxID_CANCEL)
		return;

	m_CurrentDeletePath = dirDia->GetPath();

	m_optDialogDeleteFile->GetControl<wxTextCtrl>("inputFilePath")->SetValue(m_CurrentDeletePath);
	ListElements(m_CurrentDeletePath);
}

void BasicFileOpModule::HandleSearchbarType(wxCommandEvent& evt)
{
	wxCheckListBox* chkLst = m_optDialogDeleteFile->GetControl<wxCheckListBox>("checkList");
	wxTextCtrl* searchBar = m_optDialogDeleteFile->GetControl<wxTextCtrl>("searchBar");

	if (searchBar->GetValue().IsEmpty())
	{
		TransferToMain();
		return;	
	}
	chkLst->Clear();

	std::vector<wxString> elements;
	for (const auto& item : m_v_pathCheck)
	{
		elements.push_back(item.path);
	}

	std::vector<wxString> searchedPaths = FilePathSearchUtilty::SearchDirPath(elements, searchBar->GetValue());
	if (searchedPaths.empty())
		return;

	
	for (const auto& string : searchedPaths)
	{
		int i = chkLst->Append(string);

		for (const auto& item : m_v_pathCheck)
		{
			if (item.path == chkLst->GetString(i))
			{
				chkLst->Check(i, item.checked);
				break;
			}
		}
	}
}

void BasicFileOpModule::ListElements(const wxString& path)
{
	wxCheckListBox* chkLst = m_optDialogDeleteFile->GetControl<wxCheckListBox>("checkList");
	m_CurrentDeletePath = path;
	
	//make sure we clear the last entries
	m_v_pathCheck.clear();
	chkLst->Clear();

	if (!fs::exists(path.ToStdWstring()))	
		return;

	for (const auto& item : fs::directory_iterator(path.ToStdWstring()))
	{
		chkLst->Append(fs::path(item).wstring());
		//make a copy so we can handle element checks easier
		m_v_pathCheck.push_back(PathCheck{ item.path().wstring(), false});
	}
}

void BasicFileOpModule::TransferToMain()
{
	wxCheckListBox* chkLst = m_optDialogDeleteFile->GetControl<wxCheckListBox>("checkList");
	chkLst->Clear();
	for (const auto& item : m_v_pathCheck)
	{
		int i = chkLst->Append(item.path);

		chkLst->Check(i, item.checked);
	}
}
