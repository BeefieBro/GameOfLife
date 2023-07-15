#include "MainWindow.h"
#include "DrawingPanel.h"
#include <wx/toolbar.h>
#include "play.xpm"
#include "next.xpm"
#include "pause.xpm"
#include "trash.xpm"
#include <wx/defs.h>
#include "Settings.h"
#include "wx/menu.h"
#include "SettingsDialog.h"

const int ID_SETTINGS = wxID_HIGHEST + 2;

enum
{
    ID_PLAY = wxID_HIGHEST + 1,
    ID_PAUSE,
    ID_NEXT,
    ID_TRASH
};


// Define the event table for MainWindow
wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_SIZE(MainWindow::OnSizeChange)
EVT_TOOL(wxID_ANY, MainWindow::OnToolBarClicked)
EVT_TIMER(wxID_ANY, MainWindow::OnTimer)
EVT_MENU(ID_SETTINGS, MainWindow::OnSettings)
wxEND_EVENT_TABLE()


MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Game of Life", wxPoint(500, 100), wxSize(1000, 1500))
{
    Settings mSettings;
    mGridSize = mSettings.GridSize;

    mMenuBar = new wxMenuBar();
    SetMenuBar(mMenuBar);
    wxMenu* optionsMenu = new wxMenu();
    optionsMenu->Append(ID_SETTINGS, "Settings");
    mMenuBar->Append(optionsMenu, "Options");
    


    mTimer = new wxTimer(this, wxID_ANY);
    //bind timer event
    //this->Bind(wxEVT_TIMER, &MainWindow::OnTimer, this);
    

    mBoxSizer = new wxBoxSizer(wxVERTICAL);
    //this->SetSizer(mBoxSizer);

    // Create the status bar
    mStatusBar = this->CreateStatusBar();

    // Create the toolbar
    mToolBar = this->CreateToolBar();

    // Add the play icon to the toolbar
    wxBitmap playBitmap(play_xpm);
    mToolBar->AddTool(ID_PLAY, "Play", playBitmap, wxNullBitmap, wxITEM_NORMAL, "Play");

    // Add the pause icon to the toolbar
    wxBitmap pauseBitmap(pause_xpm);
    mToolBar->AddTool(ID_PAUSE, "Pause", pauseBitmap, wxNullBitmap, wxITEM_NORMAL, "Pause");

    // Add the next icon to the toolbar
    wxBitmap nextBitmap(next_xpm);
    mToolBar->AddTool(ID_NEXT, "Next", nextBitmap, wxNullBitmap, wxITEM_NORMAL, "Next");

    // Add the trash icon to the toolbar
    wxBitmap trashBitmap(trash_xpm);
    mToolBar->AddTool(ID_TRASH, "Clear", trashBitmap, wxNullBitmap, wxITEM_NORMAL, "Clear");

    // Add the event handler for toolbar events
    //mToolBar->Bind(wxEVT_TOOL, &MainWindow::OnToolBarClicked, this);

    // Realize the toolbar
    mToolBar->Realize();

    // Bind the size event handler
    //this->Bind(wxEVT_SIZE, &MainWindow::OnSizeChange, this);

    // Initialize the grid
    InitializeGrid();

    // Refresh the layout
    this->Layout();
}




void MainWindow::OnSizeChange(wxSizeEvent& event)
{

    
    wxSize windowSize = event.GetSize();

    if(drawingPanel != nullptr)
    {
        drawingPanel->SetSize(windowSize);
    }
    event.Skip();
}

Settings& MainWindow::GetSettings()
{
    return mSettings;
}

void MainWindow::InitializeGrid()
{
    mGameBoard.resize(mSettings.GridSize);
    for (int i = 0; i < mSettings.GridSize; i++)
    {
        mGameBoard[i].resize(mSettings.GridSize);
    }
    drawingPanel = new DrawingPanel(this, mGameBoard, &mSettings); // Create the drawing panel and pass the game board reference
    drawingPanel->SetGridSize(mSettings.GridSize);
    //mBoxSizer->Add(drawingPanel, 1, wxEXPAND | wxALL, 5);
    //SetSizerAndFit(mBoxSizer);
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
            if (i >= 0 && i < mSettings.GridSize && j >= 0 && j < mSettings.GridSize)
            {
                // Increment livingCount if the neighbor cell is alive
                if (mGameBoard[i][j])
                    livingCount++;
            }
        }
    }

    return livingCount;

}
void MainWindow::OnToolBarClicked(wxCommandEvent& event)
{
    int toolbarID = event.GetId();

    switch (toolbarID)
    {
    case ID_PLAY:
        mTimer->Start(mTimerInterval);
        break;
    case ID_PAUSE:
        mTimer->Stop();
        break;
    case ID_NEXT:
        // handle the next button click
        CalculateNextGeneration();
        break;
    case ID_TRASH:
        // gets rid of all alive cells, turn them all dead
        ClearGameBoard();
        break;
    default:
        break;
    }
}
void MainWindow::CalculateNextGeneration()
{
    std::vector<std::vector<bool>> sandbox(mSettings.GridSize, std::vector<bool>(mSettings.GridSize));

    // Iterate through the game board and calculate the next state of each cell
    int livingCount = 0;
    for (int row = 0; row < mSettings.GridSize; row++)
    {

        for (int col = 0; col < mSettings.GridSize; col++)
        {
            int livingNeighbors = CalculateLivingNeighbors(row, col);
            bool isAlive = mGameBoard[row][col];

            if (isAlive)
            {
                // Living cells with less than 2 or more than 3 living neighbors die
                if (livingNeighbors < 2 || livingNeighbors > 3)
                {
                    sandbox[row][col] = false;
                }
                else
                {
                    sandbox[row][col] = true;
                    livingCount++;
                }
            }
            else
            {
                // Dead cells with exactly 3 living neighbors come to life
                if (livingNeighbors == 3)
                {
                    sandbox[row][col] = true;
                    livingCount++;
                }
                else
                {
                    sandbox[row][col] = false;
                }
            }
        }
    }

    mGameBoard.swap(sandbox);

    mGenerationCount++;
    mLivingCellCount = livingCount;

    UpdateStatusBar();

    drawingPanel->Refresh();
}

void MainWindow::ClearGameBoard()
{
    for (int row = 0; row < mSettings.GridSize; row++)
    {
        for (int col = 0; col < mSettings.GridSize; col++)
        {
            mGameBoard[row][col] = false;
        }
    }

    mLivingCellCount = 0;
    mGenerationCount = 0;

    UpdateStatusBar();

    drawingPanel->Refresh();
}

void MainWindow::OnTimer(wxTimerEvent& event)
{
    CalculateNextGeneration();

    drawingPanel->Refresh();
}

void MainWindow::RefreshLivingCellCount()
{
    mLivingCellCount = 0;
    // Finish the fix for the living cell count bug on status bar
    MainWindow::UpdateStatusBar();
}

void MainWindow::OnSettings(wxCommandEvent& event)
{
    SettingsDialog dialog(this);

    //open dialog
    if (dialog.ShowModal() == wxID_OK)
    {
        //if OK was clicked, perform actions

        //initialize grid
        InitializeGrid();

        drawingPanel->Refresh();
    }
}





MainWindow::~MainWindow()
{
    delete mStatusBar;
}