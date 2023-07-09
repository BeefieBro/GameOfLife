#include "App.h"
#include "MainWindow.h"
#include "play.xpm"
#include "pause.xpm"
#include "next.xpm"
#include "trash.xpm"

wxIMPLEMENT_APP(App);

App::App()
{
}

App::~App()
{
}

bool App::OnInit()
{
    MainWindow* mainWindow = new MainWindow();
    mainWindow->Show();

    return true;
}
