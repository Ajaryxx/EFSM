#include "PCH.hpp"
#include "utilitys/DialogOptBuilder.hpp"


DialogOptBuilder::DialogOptBuilder(wxWindow* window, wxWindowID id, const wxString& title) : wxDialog(window, id, title) 
{ 
	//we always use a panel
	mainPanel = new wxPanel(this);
}

void DialogOptBuilder::AddStrechSpacer(const wxString& key)
{
	if (m_um_Sizers.find(key) != m_um_Sizers.end())
	{
		m_um_Sizers.find(key)->second->AddStretchSpacer();
	}
	else
	{
		assert(false, "key does not exists");
	}
}

void DialogOptBuilder::RefreshLayout()
{
	mainPanel->SetSizerAndFit(m_um_Sizers.find("base")->second);
}

