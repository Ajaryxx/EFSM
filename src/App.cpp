#include "App.hpp"
#include "Application.hpp"

bool App::OnInit()
{
	Application* app = new Application();
	app->SetBackgroundColour(wxColour::wxColour(255, 255, 255));
	app->SetClientSize(800, 600);

	app->Show();
	return true;
}

wxIMPLEMENT_APP(App);