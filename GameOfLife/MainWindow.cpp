#include "MainWindow.h"
#include "DrawingPanel.h"

// Define the event table for MainWindow
wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_SIZE(MainWindow::OnSizeChange)
wxEND_EVENT_TABLE()

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Game of Life", wxPoint(500, 100), wxSize(300, 400))
{
    mBoxSizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(mBoxSizer);

    this->CreateStatusBar(); // Create the status bar

    this->Bind(wxEVT_SIZE, &MainWindow::OnSizeChange, this);
    InitializeGrid();

    this->Layout(); // Refresh the layout
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
void MainWindow::UpdateStatusBar()
{
    wxString statusText = wxString::Format("Generation: %d   Living Cells: %d", mGenerationCount, mLivingCellCount);
    mStatusBar->SetStatusText(statusText, 0);
}


MainWindow::~MainWindow()
{
    delete mStatusBar;
}