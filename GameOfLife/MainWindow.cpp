#include "MainWindow.h"
#include "DrawingPanel.h"

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Game of Life", wxPoint(500, 100), wxSize(1000, 900))
{
	drawingPanel = new DrawingPanel(this);
	mBoxSizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(mBoxSizer);
	this->Bind(wxEVT_SIZE, &MainWindow::OnSizeChange, this);
}

void MainWindow::OnSizeChange(wxSizeEvent& event)
{
	wxSize windowSize = event.GetSize();
	drawingPanel->SetSize(windowSize);
	event.Skip();
}

MainWindow::~MainWindow()
{

}
