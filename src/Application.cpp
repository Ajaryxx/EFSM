#include "PCH.hpp"
#include "Application.hpp"
#include "modules/BaseModule.hpp"

Application::Application() : wxFrame(nullptr, wxID_ANY, "EFSM")
{
	m_MainPanel = new wxPanel(this);
	m_FlexGridSizer = new wxFlexGridSizer(5, 5, 10, 10);


	m_MainPanel->SetSizerAndFit(m_FlexGridSizer);
	m_FlexGridSizer->SetSizeHints(this);
}

Application::~Application()
{

}

void Application::AddModule(std::shared_ptr<BaseModule> module)
{
	m_v_modules.push_back(module);
	m_FlexGridSizer->Add(module->GetStaticBoxSizer());
}
