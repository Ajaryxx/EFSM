#include "App.hpp"
#include "Application.hpp"

bool App::OnInit()
{
	Application* app = new Application();
	app->Show();
	app->SetClientSize(800, 600);


	return true;
}

wxIMPLEMENT_APP(App);