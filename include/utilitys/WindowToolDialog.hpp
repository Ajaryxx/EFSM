#pragma once
#include "utilitys/LayoutBuilderUtility.hpp"

class WindowToolDialog : public wxDialog, public LayoutBuilderUtility
{
public:
	WindowToolDialog(wxWindow* window, wxWindowID id, const wxString& title, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);
	~WindowToolDialog() = default;

	
private:

};