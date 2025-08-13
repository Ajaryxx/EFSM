#pragma once

class BaseModule;

class Application : public wxFrame
{
public:
	Application();
	~Application();

	
	void AddModule(std::shared_ptr<BaseModule> module);
private:

	wxPanel* m_MainPanel;
	wxFlexGridSizer* m_FlexGridSizer;

	std::vector<std::shared_ptr<BaseModule>> m_v_modules;
};
