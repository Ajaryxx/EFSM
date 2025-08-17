#include "PCH.hpp"
#include "utilitys/DialogOptBuilder.hpp"


DialogOptBuilder::DialogOptBuilder(wxWindow* window, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size) : wxDialog(window, id, title, pos, size)
{ 
	//we always use a panel
	mainPanel = new wxPanel(this);
}

void DialogOptBuilder::AddStrechSpacer(const wxString& key)
{
	auto it = m_um_Sizers.find(key);

	if (it != m_um_Sizers.end())
	{
		it->second->AddStretchSpacer();
	}
	else
	{
		assert(false, "key does not exists");
	}
}

void DialogOptBuilder::AddSpacer(const wxString& key, int size)
{
	auto it = m_um_Sizers.find(key);
	if (it != m_um_Sizers.end())
	{
		it->second->AddSpacer(size);
	}
	else
	{
		assert(false && "key does not exists");
	}
}

void DialogOptBuilder::RefreshLayout()
{
	mainPanel->SetSizerAndFit(m_um_Sizers["base"]);
}

