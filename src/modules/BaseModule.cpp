#include "PCH.hpp"
#include "modules/BaseModule.hpp"


BaseModule::BaseModule(const wxString moduleName, int orient, wxWindow* window)
{
	this->m_ModuleName = moduleName;
	this->m_StaticBoxSizer = new wxStaticBoxSizer(orient, window, m_ModuleName);
}

void BaseModule::AddControl(wxControl* control, const wxSizerFlags& sizerFlags)
{
	m_StaticBoxSizer->Add(control, sizerFlags);
}

wxStaticBoxSizer* BaseModule::GetStaticBoxSizer() const
{
	return m_StaticBoxSizer;
}
