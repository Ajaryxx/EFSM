#include "PCH.hpp"
#include "modules/BasicFileOpModule.hpp"
#include "utilitys/DialogOptBuilder.hpp"


namespace fs = std::filesystem;

BasicFileOpModule::BasicFileOpModule(wxWindow* window, wxPanel* panel) : BaseModule(wxString("Basic File operations"), wxVERTICAL, window)
{

	SetModuleSizer<wxGridSizer>(2, 2, 4, 4);

	m_CreateButton = new wxButton(panel, ECREATE_BUTTON, "Create File");
	m_DeleteButton = new wxButton(panel, EDELETE_BUTTON, "Delete File");
	m_MoveButton = new wxButton(panel, EMOVE_BUTTON, "Move File");
	m_CopyButton = new wxButton(panel, ECOPY_BUTTON, "Copy File");

	AddControl(m_CreateButton);
	AddControl(m_DeleteButton);
	AddControl(m_MoveButton);
	AddControl(m_CopyButton);

	m_CreateButton->Bind(wxEVT_BUTTON, &BasicFileOpModule::OnPressCreateFile, this);
}

void BasicFileOpModule::TestBtn(wxCommandEvent& evt)
{

}

void BasicFileOpModule::OnPressCreateFile(wxCommandEvent& evt)
{

	DialogOptBuilder* optDialog = new DialogOptBuilder(GetApplicationWindow(), wxID_ANY, "Create a file");
	
	optDialog->SetBaseSizer<wxBoxSizer>(wxVERTICAL);

	optDialog->AddStrechSpacer("base");

	optDialog->AddSizer<wxBoxSizer>("filePathSizer", "base", wxSizerFlags().CentreHorizontal().Border(wxUP, 10), wxHORIZONTAL);
	optDialog->AddControl<wxStaticText>("filePathText", "filePathSizer", wxSizerFlags(), wxID_ANY, "Filepath: ");
	optDialog->AddControl<wxTextCtrl>("inputFilePath", "filePathSizer", wxSizerFlags(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(200, wxDefaultSize.y));
	optDialog->AddControl<wxButton>("showFileDiaBtn", "filePathSizer", wxSizerFlags(), wxID_ANY, "Show File Dialog");

	optDialog->AddSizer<wxBoxSizer>("fileNameSizer", "base", wxSizerFlags().CentreHorizontal().Border(wxUP, 10), wxHORIZONTAL);
	optDialog->AddControl<wxStaticText>("fileNameText", "fileNameSizer", wxSizerFlags(), wxID_ANY, "File Name: ");
	optDialog->AddControl<wxTextCtrl>("inputFileName", "fileNameSizer", wxSizerFlags(), wxID_ANY);
	
	optDialog->AddSizer<wxBoxSizer>("checkButtonsSizer", "base", wxSizerFlags().CentreHorizontal().Border(wxUP, 10), wxHORIZONTAL);
	optDialog->AddControl<wxButton>("confirmButton", "checkButtonsSizer", wxSizerFlags(), wxID_ANY, "confirm");
	optDialog->AddControl<wxButton>("cancelButton", "checkButtonsSizer", wxSizerFlags(), wxID_ANY, "cancel");

	optDialog->AddStrechSpacer("base");

	optDialog->RefreshLayout();
	
	optDialog->ShowModal();

}
