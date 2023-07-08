#include "MainWindow.h"
#include "DrawingPanel.h"

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_SIZE(MainWindow::OnSizeChange)
EVT_MENU(wxID_ANY, MainWindow::OnNextGeneration)
wxEND_EVENT_TABLE()

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Game of Life", wxPoint(500, 100), wxSize(1000, 900))
{
    mBoxSizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(mBoxSizer);

    mGenerationCount = 0;
    mLivingCellCount = 0;

    mStatusBar = CreateStatusBar();
    UpdateStatusBar();

    Bind(wxEVT_SIZE, &MainWindow::OnSizeChange, this);

    InitializeGrid();

    Layout();
}

MainWindow::~MainWindow()
{
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

    drawingPanel = new DrawingPanel(this, mGameBoard);
    drawingPanel->SetGridSize(mGridSize);

    mBoxSizer->Add(drawingPanel, 1, wxEXPAND | wxALL, 5);
    SetSizerAndFit(mBoxSizer);
}

void MainWindow::UpdateStatusBar()
{
    wxString statusText = wxString::Format("Generation: %d   Living Cells: %d", mGenerationCount, mLivingCellCount);
    mStatusBar->SetStatusText(statusText);
}

void MainWindow::OnNextGeneration(wxCommandEvent& event)
{
    // Perform generation update logic here

    mGenerationCount++;

    UpdateStatusBar();
}
