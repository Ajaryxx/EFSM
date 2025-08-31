#pragma once
#include "utilitys/LayoutBuilderUtility.hpp"

class BaseModule : public LayoutBuilderUtility
{
public:
	BaseModule(const wxString& moduleName, int orient, wxWindow* window);

	wxStaticBoxSizer* GetLayout() const;

protected:
	wxWindow* GetApplicationWindow() const;

	
private:
	wxString m_ModuleName;
	wxStaticBoxSizer* m_StaticBoxSizer;
	wxWindow* m_Window;
	wxSizer* m_Sizer;

	std::unordered_map<wxString, wxControl*> m_um_controls;

};