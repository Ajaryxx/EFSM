#pragma once

class DialogOptBuilder : public wxDialog
{
public:
	DialogOptBuilder(wxWindow* window, wxWindowID id, const wxString& title);
	~DialogOptBuilder() = default;

	//Set base sizer for panel. Please call this function only once(the key type is set to "base"
	template<typename T, typename... Args>
	void SetBaseSizer(Args&&... args);

	//add a sizer and attach it to a sizer
	template<typename T, typename... Args>
	void AddSizer(const wxString& key, const wxString& attach, Args&&... args);

	template<typename T>
	T* GetSizer(const wxString& key);

	//add a control and attach it to a sizer
	template<typename T, typename... Args>
	void AddControl(const wxString& key, const wxString& attach, Args&&... args);
private:

	wxPanel* mainPanel;
	std::unordered_map<wxString, wxSizer*> m_um_Sizers;
};

template<typename T, typename ...Args>
inline void DialogOptBuilder::SetBaseSizer(Args&& ...args)
{
	static_assert(std::is_base_of<wxSizer, T>::value, "T must be a wxSizer");

	if (m_um_Sizers.find("base") != m_um_Sizers.end())
		return;
	m_um_Sizers["base"] = new T(std::forward<Args>(args)...);

	mainPanel->SetSizerAndFit(m_um_Sizers.begin()->second);
}

template<typename T, typename ...Args>
inline void DialogOptBuilder::AddSizer(const wxString& key, const wxString& attach, Args && ...args)
{
	static_assert(std::is_base_of<wxSizer, T>::value, "T must be a wxSizer");

	if (m_um_Sizers.find(key) != m_um_Sizers.end())
	{
		assert(false && "key already exists");
	}

	m_um_Sizers[key] = new T(std::forward<Args>(args)...);

	if (m_um_Sizers.find(attach) != m_um_Sizers.end())
	{
		m_um_Sizers.find(attach)->second->Add(m_um_Sizers[key]);
	}
	else
	{
		assert(false && "cannot find sizer with key");
	}

}

template<typename T>
inline T* DialogOptBuilder::GetSizer(const wxString& key)
{
	auto it = m_um_Sizers.find(key);

	if (it != m_um_Sizers.end())
	{
		return static_cast<T*>(it->second);
	}
	
}

template<typename T, typename ...Args>
inline void DialogOptBuilder::AddControl(const wxString& key, const wxString& attach, Args && ...args)
{
	static_assert(std::is_base_of<wxControl, T>::value, "T must be a wxControl");
}
