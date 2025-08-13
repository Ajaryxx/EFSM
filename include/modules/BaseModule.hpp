#pragma once

class BaseModule
{
public:
	BaseModule(const wxString& moduleName, int orient, wxWindow* window);

	wxStaticBoxSizer* GetStaticBoxSizer() const;


protected:
	wxWindow* GetApplicationWindow() const;

	//Please call this func only once
	template<typename T, typename... Args>
	void SetModuleSizer(Args&&... args);
	
	void AddControl(wxControl* control, const wxSizerFlags& sizerFlags = wxSizerFlags());

private:


	wxString m_ModuleName;
	wxStaticBoxSizer* m_StaticBoxSizer;
	wxWindow* m_Window;
	wxSizer* m_Sizer;
};

template<typename T, typename ...Args>
inline void BaseModule::SetModuleSizer(Args&& ...args)
{
	if (m_Sizer)
		return;
	static_assert(std::is_base_of<wxSizer, T>::value, "T must derrive from wxSizer");
	m_Sizer = new T(std::forward<Args>(args)...);
	m_StaticBoxSizer->Add(m_Sizer);
}
