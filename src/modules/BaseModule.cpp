#include "PCH.hpp"
#include "modules/BaseModule.hpp"


BaseModule::BaseModule(const wxString& moduleName, int orient, wxWindow* window)
{
	this->m_ModuleName = moduleName;
	this->m_StaticBoxSizer = new wxStaticBoxSizer(orient, window, m_ModuleName);
	this->m_Window = window;
	this->m_Sizer = nullptr;
}

wxWindow* BaseModule::GetApplicationWindow() const
{
	return m_Window;
}
wxStaticBoxSizer* BaseModule::GetLayout() const
{
	assert(m_Sizer && "Please set a sizer for this Module");
	return m_StaticBoxSizer;
}
