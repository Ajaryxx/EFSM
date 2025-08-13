#pragma once


class BaseModule
{
public:
	BaseModule(const wxString moduleName, int orient, wxWindow* window);

	wxStaticBoxSizer* GetStaticBoxSizer() const;


protected:
	void AddControl(wxControl* control, const wxSizerFlags& sizerFlags);

	
private:
	wxString m_ModuleName;

	wxStaticBoxSizer* m_StaticBoxSizer;
};