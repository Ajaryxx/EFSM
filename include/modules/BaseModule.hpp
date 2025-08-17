#pragma once

class BaseModule
{
public:
	BaseModule(const wxString& moduleName, int orient, wxWindow* window);

	wxStaticBoxSizer* GetStaticBoxSizer() const;


protected:
	wxWindow* GetApplicationWindow() const;

	//Please call this func only once, You can only set one sizer modules
	template<typename T, typename... Args>
	void SetModuleSizer(Args&&... args);
	
	template<typename T, typename... ARGS>
	void AddControl(const wxString& key, const wxSizerFlags& sizerFlags, ARGS&&... args);

	template <typename EventTag, typename Class, typename EventArg, typename EventHandler>
		void BindEvent(const wxString& key, 
			const EventTag& eventType,
			void (Class::* method)(EventArg&),
			EventHandler* handler,
			int winid = wxID_ANY,
			int lastId = wxID_ANY,
			wxObject* userData = nullptr);
private:
	wxString m_ModuleName;
	wxStaticBoxSizer* m_StaticBoxSizer;
	wxWindow* m_Window;
	wxSizer* m_Sizer;

	std::unordered_map<wxString, wxControl*> m_um_controls;

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

template<typename T, typename... ARGS>
inline void BaseModule::AddControl(const wxString& key, const wxSizerFlags& sizerFlags, ARGS&&... args)
{
	static_assert(std::is_base_of<wxControl, T>::value, "T must be a wxControl");

	auto it = m_um_controls.find(key);

	if (it != m_um_controls.end())
	{
		assert(false && "Key already exists");
	}
	else
	{
		m_um_controls[key] = new T(std::forward<ARGS>(args)...);
		m_Sizer->Add(m_um_controls[key], sizerFlags);
	}
}

template<typename EventTag, typename Class, typename EventArg, typename EventHandler>
inline void BaseModule::BindEvent(const wxString& key, const EventTag& eventType, void(Class::* method)(EventArg&), EventHandler* handler, int winid, int lastId, wxObject* userData)
{
	auto it = m_um_controls.find(key);

	if (it == m_um_controls.end())
	{
		assert(false && "Key doesnt exists");
	}
	else
	{
		it->second->Bind(eventType, method, handler, winid, lastId, userData);
	}
}
