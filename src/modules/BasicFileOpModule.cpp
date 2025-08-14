#include "PCH.hpp"
#include "modules/BasicFileOpModule.hpp"
#include "utilitys/DialogOptBuilder.hpp"


namespace fs = std::filesystem;

BasicFileOpModule::BasicFileOpModule(wxWindow* window, wxPanel* panel) : BaseModule(wxString("Basic File operations"), wxVERTICAL, window)
{
	SetModuleSizer<wxFlexGridSizer>(2, 2, 4, 4);

	DialogOptBuilder* test = new DialogOptBuilder(GetApplicationWindow(), wxID_ANY, "Test");
	test->SetBaseSizer<wxBoxSizer>(wxVERTICAL);
	test->AddSizer<wxBoxSizer>("test", "base", wxVERTICAL);

	wxBoxSizer* sizer = test->GetSizer<wxBoxSizer>("test");
	sizer->SetDimension(wxPoint(5, 5), wxSize(50, 50));
	test->AddSizer<wxBoxSizer>("test123", "base", wxVERTICAL);
	test->GetSizer<wxBoxSizer>("test123")->SetDimension(wxPoint(22, 22), wxSize(22, 22));
	test->AddSizer<wxBoxSizer>("test1321323", "base", wxVERTICAL);
	test->ShowModal();

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
	//Main
	wxDialog* dialog = new wxDialog(GetApplicationWindow(), wxID_ANY, "Create a file");
	wxPanel* mainPanel = new wxPanel(dialog);
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

	//FilePath
	wxBoxSizer* filePathSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* filePathText = new wxStaticText(mainPanel, wxID_ANY, "Filepath: ");
	wxTextCtrl* inputFilePath = new wxTextCtrl(mainPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(200, wxDefaultSize.y));
	wxButton* showFileDia = new wxButton(mainPanel, wxID_ANY, "Show File Dialog");

	filePathSizer->Add(filePathText, wxSizerFlags().CenterVertical());
	filePathSizer->Add(inputFilePath);
	filePathSizer->Add(showFileDia);
	
	showFileDia->Bind(wxEVT_BUTTON, [&](wxCommandEvent& evt)
		{
			wxDirDialog* dirDialog = new wxDirDialog(dialog, "Please select a directoy");
			if (dirDialog->ShowModal() == wxID_OK)
			{
				inputFilePath->SetValue(dirDialog->GetPath());
			}
		});

	//File Name
	wxBoxSizer* fileNameSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* fileNameText = new wxStaticText(mainPanel, wxID_ANY, "File Name: ");
	wxTextCtrl* inputFileName = new wxTextCtrl(mainPanel, wxID_ANY);

	fileNameSizer->Add(fileNameText);
	fileNameSizer->Add(inputFileName);

	//Confirm Buttons
	wxBoxSizer* checkButtonsSizer = new wxBoxSizer(wxHORIZONTAL);
	wxButton* confirmButton = new wxButton(mainPanel, wxID_ANY, "confirm");
	wxButton* cancelButton = new wxButton(mainPanel, wxID_ANY, "cancel");
	
	checkButtonsSizer->Add(confirmButton);
	checkButtonsSizer->Add(cancelButton);

	//Add to mainSizer
	
	mainSizer->AddStretchSpacer();
	mainSizer->Add(filePathSizer, wxSizerFlags().CentreHorizontal().Border(wxUP, 10));
	mainSizer->Add(fileNameSizer, wxSizerFlags().CentreHorizontal().Border(wxUP, 10));
	mainSizer->Add(checkButtonsSizer, wxSizerFlags().CentreHorizontal().Border(wxUP, 10));
	mainSizer->AddStretchSpacer();


	mainPanel->SetSizerAndFit(mainSizer);
	dialog->ShowModal();

}
