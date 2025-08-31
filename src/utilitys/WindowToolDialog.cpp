#include "PCH.hpp"
#include "utilitys/WindowToolDialog.hpp"


WindowToolDialog::WindowToolDialog(wxWindow* window, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxDialog(window, id, title, pos, size)
{ 
	InitLayoutParent(this, id);
}

