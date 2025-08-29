#pragma once
#include "modules/BaseModule.hpp"


class DialogOptBuilder;

enum EButtonsID : uint8_t
{
	ECREATE_BUTTON,
	EDELETE_BUTTON,
	EMOVE_BUTTON,
	ECOPY_BUTTON,

	//Create File Opt Dialog
	ESHOW_DIR_DIA_CREATE,
	ECONFIRM_CREATE,
	ECANCEL_CREATE,
	ERADIO_BOX,

	//Delete File Opt Dialog
	ESHOW_DIR_DIA_DELETE,
	ECHECKLIST_DELETE,
	ECONFIRM_DELETE,
	ECANCEL_DELETE,
	EON_CHANGE_DIR_PATH,
	EDIR_PATH_INPUT,
	ESEARCH_INPUT
	
};

struct PathCheck
{
	wxString path;
	bool checked;
};

/*This class is for this following file operations
 --> create, move, copy, delete*/
class BasicFileOpModule : public BaseModule
{
public:
	BasicFileOpModule(wxWindow* window, wxPanel* panel);
	~BasicFileOpModule() = default;
	

	
private:
	void BuildAllLayouts();
	void BuildCreateFileLayout();
	void BuildDeleteLayout();

	void OnPressCreateFile(wxCommandEvent& evt);
	void OnPressDelete(wxCommandEvent& evt);

	//Create folder/file
	void HandleCreateFile(wxCommandEvent& evt);

	//delete folder/file
	void HandleDelete(wxCommandEvent& evt);
	void HandleCheckElementDeleteList(wxCommandEvent& evt);
	void HandleShowDeleteDirectoryDialog(wxCommandEvent& evt);
	//When typing smthing in SearchBar
	void HandleSearchbarType(wxCommandEvent& evt);
	//List all Folders/Files to the checkList
	void ListElements(const wxString& path);
	//Transfering Copy Elements to MainCheckList
	void TransferToMain();

	DialogOptBuilder* optDialogCreateFile;
	DialogOptBuilder* optDialogDeleteFile;

	wxString m_CurrentDeletePath = "";

	std::vector<PathCheck> m_v_pathCheck;

};