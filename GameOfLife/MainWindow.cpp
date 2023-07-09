#include "MainWindow.h"
#include "DrawingPanel.h"
#include "play.xpm"
#include "pause.xpm"
#include "next.xpm"
#include "trash.xpm"

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_SIZE(MainWindow::OnSizeChange)
EVT_MENU(wxID_ANY, MainWindow::OnNextGeneration)
EVT_MENU(wxID_ANY, MainWindow::OnPlay)
EVT_MENU(wxID_ANY, MainWindow::OnPause)
EVT_MENU(wxID_ANY, MainWindow::OnClear)
wxEND_EVENT_TABLE()

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Game of Life", wxPoint(500, 100), wxSize(1000, 900))
{
    mBoxSizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(mBoxSizer);

    mGenerationCount = 0;
    mLivingCellCount = 0;

    mStatusBar = CreateStatusBar();
    UpdateStatusBar();

    mToolBar = CreateToolBar();
    wxBitmap playIcon(play_xpm);
    wxBitmap pauseIcon(pause_xpm);
    wxBitmap nextIcon(next_xpm);
    wxBitmap trashIcon(trash_xpm);

    mToolBar->AddTool(10001, "Play", playIcon);
    mToolBar->AddTool(10002, "Pause", pauseIcon);
    mToolBar->AddTool(10003, "Next", nextIcon);
    mToolBar->AddTool(10004, "Clear", trashIcon);
    mToolBar->Realize();

    Bind(wxEVT_SIZE, &MainWindow::OnSizeChange, this);

    InitializeGrid();

    Layout();
}

MainWindow::~MainWindow()
{
}

void MainWindow::OnSizeChange(wxSizeEvent& event)
{
    if (drawingPanel)
    {
        wxSize windowSize = event.GetSize();
        drawingPanel->SetSize(windowSize);
    }
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

void MainWindow::OnPlay(wxCommandEvent& event)
{
    // Implement play button logic here
}

void MainWindow::OnPause(wxCommandEvent& event)
{
    // Implement pause button logic here
}

void MainWindow::OnClear(wxCommandEvent& event)
{
    // Implement clear button logic here
}
