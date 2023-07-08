#include "MainWindow.h"
#include "DrawingPanel.h"

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Game of Life", wxPoint(500, 100), wxSize(1000, 900))
{
    mBoxSizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(mBoxSizer);
    this->Bind(wxEVT_SIZE, &MainWindow::OnSizeChange, this);
    InitializeGrid();
}

void MainWindow::OnSizeChange(wxSizeEvent& event)
{
    wxSize windowSize = event.GetSize();
    drawingPanel->SetSize(windowSize);
    event.Skip();
}

void MainWindow::InitializeGrid()
{
    mGameBoard.resize(mGridSize);
    for (int i = 0; i < mGridSize; i++)
    {
        mGameBoard[i].resize(mGridSize);
    }

    drawingPanel = new DrawingPanel(this, mGameBoard); // Create the drawing panel and pass the game board reference
    drawingPanel->SetGridSize(mGridSize);

    mBoxSizer->Add(drawingPanel, 1, wxEXPAND | wxALL, 5);
    SetSizerAndFit(mBoxSizer);
}

MainWindow::~MainWindow()
{

}
