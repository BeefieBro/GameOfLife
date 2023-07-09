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
    CalculateNextGeneration();
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
    ClearBoard();
}

int MainWindow::CountLivingNeighbors(int row, int col)
{
    int livingNeighbors = 0;
    // Iterate over the neighboring cells
    for (int i = row - 1; i <= row + 1; i++)
    {
        for (int j = col - 1; j <= col + 1; j++)
        {
            // Check if the neighboring cell is within the game board boundaries
            if (i >= 0 && i < mGridSize && j >= 0 && j < mGridSize)
            {
                // Skip the cell itself
                if (i == row && j == col)
                    continue;

                // Check if the neighboring cell is alive
                if (mGameBoard[i][j])
                    livingNeighbors++;
            }
        }
    }

    return livingNeighbors;
}

void MainWindow::CalculateNextGeneration()
{
    // Create a sandbox to store the next generation of cells
    std::vector<std::vector<bool>> sandbox(mGridSize, std::vector<bool>(mGridSize));

    // Iterate over the game board
    for (int row = 0; row < mGridSize; row++)
    {
        for (int col = 0; col < mGridSize; col++)
        {
            // Count the living neighbors for the current cell
            int livingNeighbors = CountLivingNeighbors(row, col);

            // Apply the Game of Life rules to determine the next state of the cell
            if (mGameBoard[row][col])
            {
                if (livingNeighbors < 2 || livingNeighbors > 3)
                    sandbox[row][col] = false;
                else
                    sandbox[row][col] = true;
            }
            else
            {
                if (livingNeighbors == 3)
                    sandbox[row][col] = true;
                else
                    sandbox[row][col] = false;
            }
        }
    }

    // Move the next generation data from the sandbox to the game board
    mGameBoard.swap(sandbox);

    // Update the living cell count
    mLivingCellCount = 0;
    for (int row = 0; row < mGridSize; row++)
    {
        for (int col = 0; col < mGridSize; col++)
        {
            if (mGameBoard[row][col])
                mLivingCellCount++;
        }
    }

    // Increment the generation count
    mGenerationCount++;

    // Update the status bar and refresh the drawing panel
    UpdateStatusBar();
    drawingPanel->Refresh();
}

void MainWindow::ClearBoard()
{
    // Reset the game board to all false values
    for (int row = 0; row < mGridSize; row++)
    {
        for (int col = 0; col < mGridSize; col++)
        {
            mGameBoard[row][col] = false;
        }
    }

    // Reset the living cell count and generation count
    mLivingCellCount = 0;
    mGenerationCount = 0;

    // Update the status bar and refresh the drawing panel
    UpdateStatusBar();
    drawingPanel->Refresh();
}