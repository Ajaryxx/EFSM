#pragma once
#include "modules/BaseModule.hpp"

class WindowToolDialog;

enum EButtonsID : uint8_t
{
	ECREATE_BUTTON,
	EDELETE_BUTTON,
	ECOPY_OPTION_BUTTON,
	

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
	BasicFileOpModule(wxWindow* panel);
	~BasicFileOpModule() = default;

	
private:
	void BuildAllLayouts();
	//Build Option Dialogs
	void BuildCreateFileLayout();
	void BuildDeleteLayout();
	void BuildMoveCopyLayout();
	
	/*---------------Create Folder/File------------------*/
	void HandleCreateFile(wxCommandEvent& evt);

	/*-------------------Delete Folder/File---------------------*/
	void HandleDelete(wxCommandEvent& evt);
	void HandleCheckElementDeleteList(wxCommandEvent& evt);
	void HandleShowDeleteDirectoryDialog(wxCommandEvent& evt);
	//When typing smthing in SearchBar
	void HandleSearchbarType(wxCommandEvent& evt);
	//List all Folders/Files to the checkList
	void ListElements(const wxString& path);
	//Transfering Copy Elements to MainCheckList
	void TransferToMain();

	/*---------------------------------------------------*/

	WindowToolDialog* m_optDialogCreateFile;
	WindowToolDialog* m_optDialogDeleteFile;
	WindowToolDialog* m_optDialogMoveCopyFile;

	wxString m_CurrentDeletePath = "";

	std::vector<PathCheck> m_v_pathCheck;
};