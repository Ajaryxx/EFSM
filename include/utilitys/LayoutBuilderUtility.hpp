#pragma once


class LayoutBuilderUtility
{
public:
	LayoutBuilderUtility() : mainPanel(nullptr), m_ParentWindow(nullptr) {}
	~LayoutBuilderUtility() = default;

	//Please call this function only once
	void InitLayoutParent(wxWindow* parent, wxWindowID id);

	//Set base sizer for panel. Please call this function only once(the key name is set to "base")
	template<typename T, typename... Args>
	void SetBaseSizer(Args&&... args);

	//add a sizer and attach it to a sizer
	template<typename T, typename... Args>
	void AddSizer(const wxString& key, const wxString& attach, const wxSizerFlags& flags, Args&&... args);

	/*add a control and attach it to a sizer
	NOTE: IGNORE PARENT PARAMETER*/
	template<typename T, typename... Args>
	void AddControl(const wxString& key, const wxString& attach, const wxSizerFlags& flags, Args&&... args);

	template<typename T>
	T* GetControl(const wxString& key) const;
	template<typename T>
	T* GetSizer(const wxString& key) const;

	//template<typename T, typename VAL>
	//void SetValue(const wxString& key, const VAL& value);

	//template<typename T, typename RET>
	//RET GetValue(const wxString& key) const;

	void AddStrechSpacer(const wxString& key);
	void AddSpacer(const wxString& attach, int size);

	//its not neccesery to call this function
	void RefreshLayout();

	wxWindow* GetParentWindow() const;
	void SetParentWindow(wxWindow* window);
private:

	wxPanel* mainPanel;
	std::unordered_map<wxString, wxSizer*> m_um_Sizers;
	std::unordered_map<wxString, wxControl*> m_um_Controls;

	wxWindow* m_ParentWindow;
};

template<typename T, typename ...Args>
inline void LayoutBuilderUtility::SetBaseSizer(Args&& ...args)
{
	static_assert(std::is_base_of<wxSizer, T>::value, "T must be a wxSizer");

	if (m_um_Sizers.find("base") != m_um_Sizers.end())
		return;
	m_um_Sizers["base"] = new T(std::forward<Args>(args)...);

	mainPanel->SetSizerAndFit(m_um_Sizers["base"]);
}

template<typename T, typename ...Args>
inline void LayoutBuilderUtility::AddSizer(const wxString& key, const wxString& sizerKey, const wxSizerFlags& flags, Args && ...args)
{
	static_assert(std::is_base_of<wxSizer, T>::value, "T must be a wxSizer");

	//does the key already exists
	if (m_um_Sizers.find(key) != m_um_Sizers.end())
	{
		assert(false && "key already exists");
	}

	m_um_Sizers[key] = new T(std::forward<Args>(args)...);

	auto it = m_um_Sizers.find(sizerKey);

	//check sizer to attach to it exits
	if (it != m_um_Sizers.end())
	{
		it->second->Add(m_um_Sizers[key], flags);
	}
	else
	{
		assert(false && "key does not exists");
	}
}

template<typename T, typename ...Args>
inline void LayoutBuilderUtility::AddControl(const wxString& key, const wxString& sizerKey, const wxSizerFlags& flags, Args && ...args)
{
	static_assert(std::is_base_of<wxControl, T>::value, "T must be a wxControl");

	if (m_um_Controls.find(key) != m_um_Controls.end())
	{
		assert(false && "key already exists");
	}
	//panel is always the parent
	m_um_Controls[key] = new T(mainPanel, std::forward<Args>(args)...);

	auto it = m_um_Sizers.find(sizerKey);

	//check sizer to attach to it exits
	if (it != m_um_Sizers.end())
	{
		it->second->Add(m_um_Controls[key], flags);
	}
	else
	{
		assert(false && "key does not exists");
	}
}

template<typename T>
inline T* LayoutBuilderUtility::GetControl(const wxString& key) const
{
	auto it = m_um_Controls.find(key);
	if (it != m_um_Controls.end())
	{
		if (auto control = dynamic_cast<T*>(it->second))
		{
			return control;
		}
	}
	else
	{
		assert(false && "Key does not exists");
	}
}

template<typename T>
inline T* LayoutBuilderUtility::GetSizer(const wxString& key) const
{
	auto it = m_um_Sizers.find(key);
	if (it != m_um_Sizers.end())
	{
		if (auto control = dynamic_cast<T*>(it->second))
		{
			return control;
		}
	}
	else
	{
		assert(false && "Key does not exists");
	}
	return nullptr;
}

//template<typename T, typename VAL>
//inline void DialogOptBuilder::SetValue(const wxString& key, const VAL& value)
//{
//	static_assert(std::is_base_of<wxControl, T>::value, "T must be a wxControl");
//
//	auto it = m_um_Controls.find(key);
//	if (it != m_um_Controls.end())
//	{
//		if (auto control = dynamic_cast<T*>(it->second))
//		{
//			control->SetValue(value);
//		}
//		else
//		{
//			assert(false && "T is not a wxControl or it has no SetValue as member");
//		}
//	}
//	else
//	{
//		assert(false && "Key does not exists");
//	}
//}
//
//template<typename T, typename RET>
//inline RET DialogOptBuilder::GetValue(const wxString& key) const
//{
//	static_assert(std::is_base_of<wxControl, T>::value, "T must be a wxControl");
//
//	auto it = m_um_Controls.find(key);
//	if (it != m_um_Controls.end())
//	{
//		if (auto control = dynamic_cast<T*>(it->second))
//		{
//			return control->GetValue();
//		}
//		else
//		{
//			assert(false && "T is not a wxControl or it has no GetValue as member");
//		}
//	}
//	else
//	{
//		assert(false && "Key does not exists");
//	}
//
//	return RET();
//}