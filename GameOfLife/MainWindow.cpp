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
#include <cstdlib>
#include "wx/filedlg.h"
#include <fstream>


enum
{
    ID_PLAY = wxID_HIGHEST + 2,
    ID_PAUSE,
    ID_NEXT,
    ID_TRASH,
    ID_SETTINGS,
    ID_SHOWNEIGHBORCOUNT,
    ID_RANDOMIZE,
    ID_FINITE,
    ID_TORODIAL,
    ID_UNIVERSE_TYPE,
    ID_SHOW_GRID,
    ID_SHOW_10x10_GRID,
    ID_SHOW_HUD,
    ID_IMPORT
};


// Define the event table for MainWindow
wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_SIZE(MainWindow::OnSizeChange)
EVT_TOOL(wxID_ANY, MainWindow::OnToolBarClicked)
EVT_TIMER(wxID_ANY, MainWindow::OnTimer)
EVT_MENU(ID_SETTINGS, MainWindow::OnSettings)
EVT_MENU(ID_SHOWNEIGHBORCOUNT, MainWindow::OnShowNeighborCount)
EVT_MENU(ID_RANDOMIZE, MainWindow::RandomizeBoard)
EVT_MENU(wxID_SAVE, MainWindow::OnSaveBoard)
EVT_MENU(wxID_OPEN, MainWindow::OnOpenBoard)
EVT_MENU(ID_UNIVERSE_TYPE, MainWindow::OnUniverseType)
wxEND_EVENT_TABLE()


MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Game of Life", wxPoint(500, 100), wxSize(1000, 900))
{

    
    
   // Add Load Settings
    mSettings.LoadData();
    mSettings.generationCount = 0;

    mMenuBar = new wxMenuBar();
    SetMenuBar(mMenuBar);

    wxMenu* fileMenu = new wxMenu();
    wxMenu* optionsMenu = new wxMenu();
    wxMenu* viewMenu = new wxMenu();

    //doing universe stuff

    wxMenuItem* universeType = new wxMenuItem(viewMenu, ID_UNIVERSE_TYPE, "Universe Type", "", wxITEM_NORMAL);
    wxMenuItem* finite = new wxMenuItem(viewMenu, ID_FINITE, "Finite", "",wxITEM_CHECK);
    wxMenuItem* torodial = new wxMenuItem(viewMenu, ID_TORODIAL, "Torodial", "", wxITEM_CHECK);

    wxMenuItem* mImport = new wxMenuItem(fileMenu, ID_IMPORT, "Import", "", wxITEM_NORMAL);

    //finite->SetCheckable(true);
    //torodial->SetCheckable(true);

    viewMenu->AppendCheckItem(ID_SHOW_HUD, "Show HUD");
    viewMenu->Bind(wxEVT_MENU, &MainWindow::OnShowHUD, this, ID_SHOW_HUD);

    // Set the initial check state based on the setting value
    viewMenu->Check(ID_SHOW_HUD, mSettings.ShowHUD);

    viewMenu->Bind(wxEVT_MENU, &MainWindow::OnShowGrid, this, ID_SHOW_GRID);
    viewMenu->Bind(wxEVT_MENU, &MainWindow::OnShow10x10Grid, this, ID_SHOW_10x10_GRID);




    mSettings.ShowGrid = true;
    mSettings.Show10x10Grid = true;

    wxMenuItem* showGridItem = new wxMenuItem(viewMenu, ID_SHOW_GRID, "Show Grid", "", wxITEM_CHECK);

    viewMenu->Append(showGridItem);
    //showGridItem->Check(mSettings.ShowGrid);
    


    

    // Add the show 10x10 grid option to the View menu
    wxMenuItem* show10x10GridItem = new wxMenuItem(viewMenu, ID_SHOW_10x10_GRID, "Show 10x10 Grid", "", wxITEM_CHECK);
    viewMenu->Append(show10x10GridItem);

    // Bind event handlers for the new options
    viewMenu->Bind(wxEVT_MENU, &MainWindow::OnShowGrid, this, ID_SHOW_GRID);
    viewMenu->Bind(wxEVT_MENU, &MainWindow::OnShow10x10Grid, this, ID_SHOW_10x10_GRID);

    

    wxMenu* universeSubMenu = new wxMenu();
    universeSubMenu->AppendRadioItem(ID_FINITE, "Finite");
    universeSubMenu->AppendRadioItem(ID_TORODIAL, "Toroidal");

    universeType->SetSubMenu(universeSubMenu);
    viewMenu->Append(universeType);

    viewMenu->Bind(wxEVT_MENU, &MainWindow::OnFinite, this, ID_FINITE);
    viewMenu->Bind(wxEVT_MENU, &MainWindow::OnTorodial, this, ID_TORODIAL);
    

    fileMenu->Append(wxID_SAVE);
    fileMenu->Append(wxID_OPEN);
    fileMenu->Append(ID_IMPORT, "Import");
    //fileMenu->Append(mImport);

    //finite->Check(!mSettings.IsToroidal);
    //torodial->Check(mSettings.IsToroidal);
    
    optionsMenu->Append(ID_SETTINGS, "Settings");
    optionsMenu->Append(ID_SHOWNEIGHBORCOUNT, "Show neighbor Count", "", true);
    optionsMenu->Append(ID_RANDOMIZE, "Randomize Board", "Fills in the board with around 40% live cells");

    //bind event handler
    optionsMenu->Bind(wxEVT_MENU, &MainWindow::OnSettings, this, ID_SETTINGS);
    optionsMenu->Bind(wxEVT_MENU, &MainWindow::OnShowNeighborCount, this, ID_SHOWNEIGHBORCOUNT);
    optionsMenu->Bind(wxEVT_MENU, &MainWindow::RandomizeBoard, this, ID_RANDOMIZE);

    fileMenu->Bind(wxEVT_MENU, &MainWindow::OnSaveBoard, this, wxID_SAVE);
    fileMenu->Bind(wxEVT_MENU, &MainWindow::OnOpenBoard, this, wxID_OPEN);
    fileMenu->Bind(wxEVT_MENU, &MainWindow::OnImport, this, ID_IMPORT);


    mMenuBar->Append(fileMenu, "File");
    mMenuBar->Append(optionsMenu, "Options");
    mMenuBar->Append(viewMenu, "View");

    
    
    

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
    mSettings.SaveData();
    return mSettings;
}

void MainWindow::InitializeGrid()
{
    mGridSize = mSettings.GridSize;
    mGameBoard.resize(mSettings.GridSize);
    neighborCount.resize(mSettings.GridSize);
    for (int i = 0; i < mSettings.GridSize; i++)
    {
        mGameBoard[i].resize(mSettings.GridSize);
        neighborCount[i].resize(mSettings.GridSize);
    }

    if(drawingPanel == nullptr)
    {
        drawingPanel = new DrawingPanel(this, mGameBoard, neighborCount, &mSettings); // Create the drawing panel and pass the game board reference
    }
    mSettings.SaveData();
    drawingPanel->SetGridSize(mSettings.GridSize);
    
}
void MainWindow::UpdateStatusBar()
{
    wxString statusText = wxString::Format("Generation: %d   Living Cells: %d", mSettings.generationCount, mSettings.livingcellcount);
    mSettings.SaveData();
    mStatusBar->SetStatusText(statusText, 0);
}

int MainWindow::CalculateLivingNeighbors(int row, int col)
{
    int livingCount = 0;
    int gridSize = mSettings.GridSize;

    // Check the eight adjacent cells
    for (int i = row - 1; i <= row + 1; i++)
    {
        for (int j = col - 1; j <= col + 1; j++)
        {
            // Skip the current cell
            if (i == row && j == col)
                continue;

            int wrappedRow, wrappedCol;
            if (mSettings.IsToroidal) // Toroidal universe
            {
                wrappedRow = (i + gridSize) % gridSize;
                wrappedCol = (j + gridSize) % gridSize;
            }
            else // Finite universe
            {
                // Check if the neighbor cell is within the bounds of the game board
                if (i >= 0 && i < gridSize && j >= 0 && j < gridSize)
                {
                    wrappedRow = i;
                    wrappedCol = j;
                }
                else
                {
                    // Neighbor cell is outside the bounds of the game board, skip it
                    continue;
                }
            }

            // Increment livingCount if the neighbor cell is alive
            if (mGameBoard[wrappedRow][wrappedCol])
                livingCount++;
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
        mTimer->Start(mSettings.Interval);
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

    mSettings.generationCount++;
    mSettings.livingcellcount = livingCount;
    UpdateStatusBar();
        MainWindow::CalculateLivingNeighborCount();
    
    drawingPanel->Refresh();
}

void MainWindow::ClearGameBoard()
{
    if(mSettings.GridSize != 0)
    {
        for (int row = 0; row < mSettings.GridSize; row++)
        {
            for (int col = 0; col < mSettings.GridSize; col++)
            {
                mGameBoard[row][col] = false;
            }
        }

        mSettings.livingcellcount = 0;
        mSettings.generationCount = 0;
    }
    UpdateStatusBar();
    mSettings.SaveData();
    drawingPanel->Refresh();
}

void MainWindow::OnTimer(wxTimerEvent& event)
{

    CalculateNextGeneration();

    drawingPanel->Refresh();
}

void MainWindow::RefreshLivingCellCount()
{
    mSettings.livingcellcount = 0;
    // Finish the fix for the living cell count bug on status bar
    
    for (int row = 0; row < mSettings.GridSize; row++)
    {
        for (int col = 0; col < mSettings.GridSize; col++)
        {
            if (mGameBoard[row][col])
                mSettings.livingcellcount++;
        }
    }


    mSettings.SaveData();
    MainWindow::UpdateStatusBar(); 
    Refresh();
}

void MainWindow::OnSettings(wxCommandEvent& event)
{
    SettingsDialog settingsDialog(this, mSettings);
    if (settingsDialog.ShowModal() == wxID_OK)
    {
        //Call the grid size setter in your settings object and pass in settingsDialog.GetUpdatedGridSize()
        InitializeGrid();
        Refresh();
    }
}
void MainWindow::CalculateLivingNeighborCount()
{
    
        for (int row = 0; row < mSettings.GridSize; row++)
        {

            for (int col = 0; col < mSettings.GridSize; col++)
            {
                int livingNeighbors = CalculateLivingNeighbors(row, col);

                neighborCount[row][col] = livingNeighbors;


            }
        }
}
void MainWindow::RandomizeBoard(wxCommandEvent& event)
{
    srand((unsigned)time(NULL));
    MainWindow::ClearGameBoard();

    for (int row = 0; row < mSettings.GridSize; row++)
    {
        for (int col = 0; col < mSettings.GridSize; col++)
        {
            int random = rand() % 100;

            if(random <= 40)
            {
                mGameBoard[row][col] = true;
            }
        }
    }
}

void MainWindow::OnShowNeighborCount(wxCommandEvent& event)
{
    mSettings.ShowNeighborCount = !mSettings.ShowNeighborCount;
}

void MainWindow::OnSaveBoard(wxCommandEvent& event)
{
    wxFileDialog fileDialog(this, "Save game of life file", wxEmptyString, wxEmptyString, "Game of Life Files (*.cells) | *.cells", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    
    if (fileDialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }
    std::ofstream fileStream;
    fileStream.open((std::string)fileDialog.GetPath());
    if (fileStream.is_open())
    {
        for (int row = 0; row < mSettings.GridSize; row++)
        {

            for (int col = 0; col < mSettings.GridSize; col++)
            {
                if (mGameBoard[row][col])
                {
                    fileStream << '*';
                }
                else
                {
                    fileStream << '.';
                }
                

            }
            fileStream << '\n';
        }


        fileStream.close();
    }

}
void MainWindow::OnOpenBoard(wxCommandEvent& event)
{
    wxFileDialog fileDialog(this, "Open game of life file", wxEmptyString, wxEmptyString, "Game of Life Files (*.cells) | *.cells", wxFD_OPEN);

    if (fileDialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }
    

    
    mGameBoard.clear();
    mGameBoard.resize(0);
    //MainWindow::ClearGameBoard();

    std::string buffer;
    std::ifstream fileStream;
    int index = 0;
    fileStream.open((std::string)fileDialog.GetPath());
    if (fileStream.is_open())
    {
        while (!fileStream.eof())
        {
            std::getline(fileStream, buffer);
            if (buffer.size() == 0) { break; }
            if (mGameBoard.size() == 0)
            {
                mGameBoard.resize(buffer.size());
                mSettings.GridSize = buffer.size();
                Refresh();

            }
            mGameBoard[index].resize(buffer.size());
            for (int i = 0; i < buffer.size(); i++)
            {
                if (buffer[i] == '*')
                {
                    mGameBoard[index][i] = true;
                }
                else
                {
                    mGameBoard[index][i] = false;
                }

            }
            index++;
            
        }

        fileStream.close();
    }

    event.Skip();
}

void MainWindow::OnFinite(wxCommandEvent& event)
{
    mSettings.IsToroidal = false; // Set the universe to Finite
    mMenuBar->Check(ID_FINITE, true);
    mMenuBar->Check(ID_TORODIAL, false);
    
    drawingPanel->Refresh();
}
void MainWindow::OnTorodial(wxCommandEvent& event)
{
    mSettings.IsToroidal = true; // Set the universe to Toroidal
    mMenuBar->Check(ID_TORODIAL, true);
    mMenuBar->Check(ID_FINITE, false);
    
    drawingPanel->Refresh();
}

void MainWindow::OnUniverseType(wxCommandEvent& event)
{
    // Get the selected universe type
    int selectedType = event.GetId();

    if (selectedType == ID_FINITE)
    {
        mSettings.IsToroidal = false; // Set the universe to Finite
    }
    else if (selectedType == ID_TORODIAL)
    {
        mSettings.IsToroidal = true; // Set the universe to Toroidal
    }

    // Update the check state of the menu items
    wxMenu* viewMenu = mMenuBar->GetMenu(3); // Replace "2" with the actual position of your "View" menu in the menu bar
    viewMenu->Check(ID_FINITE, !mSettings.IsToroidal);
    viewMenu->Check(ID_TORODIAL, mSettings.IsToroidal);

    
    drawingPanel->Refresh();
}
void MainWindow::OnShowGrid(wxCommandEvent& event)
{
    mSettings.ShowGrid = !mSettings.ShowGrid;
    
    drawingPanel->Refresh();
}


void MainWindow::OnShow10x10Grid(wxCommandEvent& event)
{
    mSettings.Show10x10Grid = !mSettings.Show10x10Grid;
    drawingPanel->Refresh();
}
void MainWindow::OnShowHUD(wxCommandEvent& event)
{
    bool showHUD = event.IsChecked();
    mSettings.ShowHUD = showHUD;

    drawingPanel->Refresh();
}
void MainWindow::OnImport(wxCommandEvent& event)
{
    wxFileDialog fileDialog(this, "Import Game of life file", wxEmptyString, wxEmptyString, "Game of Life Files (*.cells) | *.cells", wxFD_OPEN);

    if (fileDialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }



    MainWindow::ClearGameBoard();
    

    std::string buffer;
    std::ifstream fileStream;
    int index = 0;
    fileStream.open((std::string)fileDialog.GetPath());
    if (fileStream.is_open())
    {
        while (!fileStream.eof())
        {


            if (index < mSettings.GridSize)
            {

                std::getline(fileStream, buffer);

                if (buffer.size() == 0) { break; }

                for (int i = 0; i < buffer.size(); i++)
                {


                    if (i < mSettings.GridSize)
                    {

                        if (buffer[i] == '*')
                        {
                            mGameBoard[index][i] = true;
                        }
                        else
                        {
                            mGameBoard[index][i] = false;
                        }

                    }




                }

            }
            else
            {
                break;
            }

            index++;


        }

        fileStream.close();
    }

    event.Skip();
}

MainWindow::~MainWindow()
{
    delete mStatusBar;
}