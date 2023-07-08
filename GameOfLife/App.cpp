#include "App.h"

wxIMPLEMENT_APP(App);

App::App() {

}

App::~App() {

}

bool App::OnInit()
{
    MainWindow* mainWindow = new MainWindow();
    mainWindow->SetSize(wxSize(300, 400)); // Set the initial size of the window
    mainWindow->Show();

    return true;
}
