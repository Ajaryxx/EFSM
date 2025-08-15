#pragma once

class DialogOptBuilder : public wxDialog
{
public:
	DialogOptBuilder(wxWindow* window, wxWindowID id, const wxString& title);
	~DialogOptBuilder() = default;

	//Set base sizer for panel. Please call this function only once(the key name is set to "base")
	template<typename T, typename... Args>
	void SetBaseSizer(Args&&... args);

	//add a sizer and attach it to a sizer
	template<typename T, typename... Args>
	void AddSizer(const wxString& key, const wxString& attach, const wxSizerFlags& flags = wxSizerFlags(), Args&&... args);

	/*add a control and attach it to a sizer
	NOTE: IGNORE PARENT PARAMETER*/
	template<typename T, typename... Args>
	void AddControl(const wxString& key, const wxString& attach, const wxSizerFlags& flags = wxSizerFlags(), Args&&... args);

	void AddStrechSpacer(const wxString& key);

	void RefreshLayout();
private:

	wxPanel* mainPanel;
	std::unordered_map<wxString, wxSizer*> m_um_Sizers;
	std::unordered_map<wxString, wxControl*> m_um_Controls;
};

template<typename T, typename ...Args>
inline void DialogOptBuilder::SetBaseSizer(Args&& ...args)
{
	static_assert(std::is_base_of<wxSizer, T>::value, "T must be a wxSizer");

	if (m_um_Sizers.find("base") != m_um_Sizers.end())
		return;
	m_um_Sizers["base"] = new T(std::forward<Args>(args)...);

	mainPanel->SetSizerAndFit(m_um_Sizers["base"]);
}

template<typename T, typename ...Args>
inline void DialogOptBuilder::AddSizer(const wxString& key, const wxString& sizerKey, const wxSizerFlags& flags, Args && ...args)
{
	static_assert(std::is_base_of<wxSizer, T>::value, "T must be a wxSizer");

	//does the key already exists
	if (m_um_Sizers.find(key) != m_um_Sizers.end())
	{
		assert(false && "key already exists");
	}

	m_um_Sizers[key] = new T(std::forward<Args>(args)...);

	//check sizer to attach to it exits
	if (m_um_Sizers.find(sizerKey) != m_um_Sizers.end())
	{
		m_um_Sizers.find(sizerKey)->second->Add(m_um_Sizers[key], flags);
	}
	else
	{
		assert(false && "cannot find sizer with key");
	}
	
}

template<typename T, typename ...Args>
inline void DialogOptBuilder::AddControl(const wxString& key, const wxString& sizerKey, const wxSizerFlags& flags, Args && ...args)
{
	static_assert(std::is_base_of<wxControl, T>::value, "T must be a wxControl");

	if (m_um_Controls.find(key) != m_um_Controls.end())
	{
		assert(false && "key already exists");
	}
	//panel is always the parent
	m_um_Controls[key] = new T(mainPanel, std::forward<Args>(args)...);

	//check sizer to attach to it exits
	if (m_um_Sizers.find(sizerKey) != m_um_Sizers.end())
	{
		m_um_Sizers.find(sizerKey)->second->Add(m_um_Controls[key], flags);
	}
	else
	{
		assert(false && "cannot find sizer with key");
	}
}
