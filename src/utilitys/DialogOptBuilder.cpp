#include "PCH.hpp"
#include "utilitys/DialogOptBuilder.hpp"


DialogOptBuilder::DialogOptBuilder(wxWindow* window, wxWindowID id, const wxString& title) : wxDialog(window, id, title) 
{ 
	//we always use a panel
	mainPanel = new wxPanel(this);
}

