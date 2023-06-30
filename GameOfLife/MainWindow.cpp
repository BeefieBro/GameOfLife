#include "MainWindow.h"



MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Game of Life", wxPoint(500 , 100), wxSize(1000, 900))
{
	drawingPanel = new DrawingPanel(this);
}

MainWindow::~MainWindow()
{

}
