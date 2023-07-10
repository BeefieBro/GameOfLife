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

    // Create the status bar
    mStatusBar = this->CreateStatusBar();

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

int MainWindow::CalculateLivingNeighbors(int row, int col)
{
    int livingCount = 0;

    // Check the eight adjacent cells
    for (int i = row - 1; i <= row + 1; i++)
    {
        for (int j = col - 1; j <= col + 1; j++)
        {
            // Skip the current cell
            if (i == row && j == col)
                continue;

            // Check if the neighbor cell exists within the bounds of the game board
            if (i >= 0 && i < mGridSize && j >= 0 && j < mGridSize)
            {
                // Increment livingCount if the neighbor cell is alive
                if (mGameBoard[i][j])
                    livingCount++;
            }
        }
    }

    return livingCount;
}


MainWindow::~MainWindow()
{
    delete mStatusBar;
}