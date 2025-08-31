#include "PCH.hpp"
#include "utilitys/LayoutBuilderUtility.hpp"


void LayoutBuilderUtility::InitLayoutParent(wxWindow* parent, wxWindowID id)
{
	mainPanel = new wxPanel(parent, id);
	m_ParentWindow = parent;
}

void LayoutBuilderUtility::AddStrechSpacer(const wxString& key)
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

void LayoutBuilderUtility::AddSpacer(const wxString& attach, int size)
{
	auto it = m_um_Sizers.find(attach);
	if (it != m_um_Sizers.end())
	{
		it->second->AddSpacer(size);
	}
	else
	{
		assert(false && "key does not exists");
	}
}

void LayoutBuilderUtility::RefreshLayout()
{
	mainPanel->SetSizerAndFit(m_um_Sizers["base"]);
}
wxWindow* LayoutBuilderUtility::GetParentWindow() const
{
	return m_ParentWindow;
}
void LayoutBuilderUtility::SetParentWindow(wxWindow* window)
{
	this->m_ParentWindow = window;
	RefreshLayout();
}