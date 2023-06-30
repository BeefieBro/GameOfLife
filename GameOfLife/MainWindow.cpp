#include "MainWindow.h"



MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Game of Life", wxPoint(100, 100), wxSize(200, 200))
{
	drawingPanel = new DrawingPanel(this);
}