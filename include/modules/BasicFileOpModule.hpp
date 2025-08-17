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
	ECHECKLIST_DELETE
	
};

/*This class is for this following file operations
 --> create, move, copy, delete*/
class BasicFileOpModule : public BaseModule
{
public:
	BasicFileOpModule(wxWindow* window, wxPanel* panel);
	~BasicFileOpModule() = default;
	void HandleCreateFile(wxCommandEvent& evt);

	void BuildAllLayouts();
	void BuildCreateFileLayout();
	void BuildDeleteLayout();
private:

	void OnPressCreateFile(wxCommandEvent& evt);
	void OnPressDelteteFile(wxCommandEvent& evt);

	DialogOptBuilder* optDialogCreateFile;
	DialogOptBuilder* optDialogDeleteFile;

};