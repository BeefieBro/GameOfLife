#include "App.h"

#include "MainWindow.h"
#include "Settings.h"

wxIMPLEMENT_APP(App);


App::App()
{
}

App::~App()
{
}

bool App::OnInit()
{
    Settings settings;
    settings.Settings::LoadData();

    MainWindow* mainWindow = new MainWindow();
    mainWindow->Show();

    return true;
}
