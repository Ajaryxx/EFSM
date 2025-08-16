#pragma once
#include "modules/BaseModule.hpp"

enum EButtonsID : uint8_t
{
	ECREATE_BUTTON,
	EDELETE_BUTTON,
	EMOVE_BUTTON,
	ECOPY_BUTTON,
};

/*This class is for this following file operations
 --> create, move, copy, delete*/
class BasicFileOpModule : public BaseModule
{
public:
	BasicFileOpModule(wxWindow* window, wxPanel* panel);
	~BasicFileOpModule() = default;
	void TestBtn(wxCommandEvent& evt);

private:

	//for file operations
	wxButton* m_CreateButton;
	wxButton* m_DeleteButton;
	wxButton* m_MoveButton;
	wxButton* m_CopyButton;

	void OnPressCreateFile(wxCommandEvent& evt);

};