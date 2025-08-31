#include "PCH.hpp"
#include "Application.hpp"
#include "modules/BaseModule.hpp"
#include "modules/BasicFileOpModule.hpp"

Application::Application() : wxFrame(nullptr, wxID_ANY, "EFSM")
{
	m_MainPanel = new wxPanel(this);
	m_FlexGridSizer = new wxFlexGridSizer(5, 5, 10, 10);
	AddModule(std::make_shared<BasicFileOpModule>(this, m_MainPanel));


	m_MainPanel->SetSizerAndFit(m_FlexGridSizer);
	m_FlexGridSizer->SetSizeHints(this);
	
}

Application::~Application()
{

}

void Application::AddModule(std::shared_ptr<BaseModule> module)
{
	m_v_modules.push_back(module);
	m_FlexGridSizer->Add(module->GetLayout());
}
