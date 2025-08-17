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

	//Delete File Opt Dialog
	ESHOW_DIR_DIA_DELETE,
	ECHECKLIST_DELETE,
	ECONFIRM_DELETE,
	ECANCEL_DELETE,
	EON_CHANGE_DIR_PATH
	
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
	void HandleCreateFile(wxCommandEvent& evt);

	void OnPressDelete(wxCommandEvent& evt);
	void HandleDelete(wxCommandEvent& evt);


	void ListElements(const wxString& path);


	DialogOptBuilder* optDialogCreateFile;
	DialogOptBuilder* optDialogDeleteFile;

};