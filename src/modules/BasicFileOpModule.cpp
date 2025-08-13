#include "PCH.hpp"
#include "modules/BasicFileOpModule.hpp"

BasicFileOpModule::BasicFileOpModule(wxWindow* window, wxPanel* panel) : BaseModule(wxString("Basic File operations"), wxVERTICAL, window)
{
	SetModuleSizer<wxFlexGridSizer>(2, 2, 4, 4);

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
	wxTextCtrl* inputFilePath = new wxTextCtrl(mainPanel, wxID_ANY);
	wxButton* showFileDia = new wxButton(mainPanel, wxID_ANY, "Show File Dialog");

	
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

	//FilePath
	filePathSizer->Add(filePathText, wxSizerFlags().CenterVertical());
	filePathSizer->Add(inputFilePath);
	filePathSizer->Add(showFileDia);

	//FileName
	fileNameSizer->Add(fileNameText);
	fileNameSizer->Add(inputFileName);

	

	//Add to mainSizer
	mainSizer->Add(filePathSizer, wxSizerFlags().CenterHorizontal().Border(wxUP, 10));
	mainSizer->Add(fileNameSizer, wxSizerFlags().CenterHorizontal().Border(wxUP, 10));

	mainPanel->SetSizerAndFit(mainSizer);
	dialog->ShowModal();

}
