#include "PCH.hpp"
#include "modules/BasicFileOpModule.hpp"

BasicFileOpModule::BasicFileOpModule(wxWindow* window, wxPanel* panel) : BaseModule(wxString("Basic File operations"), wxVERTICAL, window)
{
	
	//SetModuleSizer(m_gridSizer);
	SetModuleSizer<wxFlexGridSizer>(2, 2, 4, 4);

	m_CreateButton = new wxButton(panel, ECREATE_BUTTON, "Create File");
	m_DeleteButton = new wxButton(panel, EDELETE_BUTTON, "Delete File");
	m_MoveButton = new wxButton(panel, EMOVE_BUTTON, "Move File");
	m_CopyButton = new wxButton(panel, ECOPY_BUTTON, "Copy File");

	AddControl(m_CreateButton);
	AddControl(m_DeleteButton);
	AddControl(m_MoveButton);
	AddControl(m_CopyButton);


}
