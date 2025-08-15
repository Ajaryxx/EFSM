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

	////Main
	//wxDialog* dialog = new wxDialog(GetApplicationWindow(), wxID_ANY, "Create a file");
	//wxPanel* mainPanel = new wxPanel(dialog);
	//wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

	////FilePath
	//wxBoxSizer* filePathSizer = new wxBoxSizer(wxHORIZONTAL);
	//wxStaticText* filePathText = new wxStaticText(mainPanel, wxID_ANY, "Filepath: ");
	//wxTextCtrl* inputFilePath = new wxTextCtrl(mainPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(200, wxDefaultSize.y));
	//wxButton* showFileDia = new wxButton(mainPanel, wxID_ANY, "Show File Dialog");

	//filePathSizer->Add(filePathText, wxSizerFlags().CenterVertical());
	//filePathSizer->Add(inputFilePath);
	//filePathSizer->Add(showFileDia);

	////File Name
	//wxBoxSizer* fileNameSizer = new wxBoxSizer(wxHORIZONTAL);
	//wxStaticText* fileNameText = new wxStaticText(mainPanel, wxID_ANY, "File Name: ");
	//wxTextCtrl* inputFileName = new wxTextCtrl(mainPanel, wxID_ANY);

	//fileNameSizer->Add(fileNameText);
	//fileNameSizer->Add(inputFileName);

	////Confirm Buttons
	//wxBoxSizer* checkButtonsSizer = new wxBoxSizer(wxHORIZONTAL);
	//wxButton* confirmButton = new wxButton(mainPanel, wxID_ANY, "confirm");
	//wxButton* cancelButton = new wxButton(mainPanel, wxID_ANY, "cancel");
	//
	//checkButtonsSizer->Add(confirmButton);
	//checkButtonsSizer->Add(cancelButton);

	////Add to mainSizer
	//
	//mainSizer->AddStretchSpacer();
	//mainSizer->Add(filePathSizer, wxSizerFlags().CentreHorizontal().Border(wxUP, 10));
	//mainSizer->Add(fileNameSizer, wxSizerFlags().CentreHorizontal().Border(wxUP, 10));
	//mainSizer->Add(checkButtonsSizer, wxSizerFlags().CentreHorizontal().Border(wxUP, 10));
	//mainSizer->AddStretchSpacer();


	//mainPanel->SetSizerAndFit(mainSizer);
	

}
