#pragma once

class BaseModule;

class Application : public wxFrame
{
public:
	Application();
	~Application();

	
	void AddModule(BaseModule* module);
private:

	wxPanel* m_MainPanel;
	wxFlexGridSizer* m_FlexGridSizer;

	std::vector<BaseModule*> m_v_modules;
};
