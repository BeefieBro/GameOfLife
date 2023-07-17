#pragma once
#include "wx/wx.h"
#include "DrawingPanel.h"
#include "Settings.h"

class MainWindow : public wxFrame
{

private:
    DrawingPanel* drawingPanel = nullptr;
    wxBoxSizer* mBoxSizer;
    int mGridSize;
    std::vector<std::vector<bool>> mGameBoard;
    std::vector<std::vector<int>> neighborCount;
    int mGenerationCount = 0; // Number of generations
    int mLivingCellCount = 0; // Number of living cells
    wxStatusBar* mStatusBar; // Status bar
    wxToolBar* mToolBar;
    wxTimer* mTimer;

    int mTimerInterval = 50;

    //create an instance of settings
    Settings mSettings;
    wxMenuBar* mMenuBar;

public:
    MainWindow();
    ~MainWindow();

    void OnSizeChange(wxSizeEvent& event);
    void InitializeGrid();
    void UpdateStatusBar(); // Update the status bar with generation and living cell counts
    int CalculateLivingNeighbors(int row, int col);
    void OnToolBarClicked(wxCommandEvent& event);
    void CalculateNextGeneration();
    void ClearGameBoard();
    void OnTimer(wxTimerEvent& event);
    void RefreshLivingCellCount();

    Settings& GetSettings();

    void OnSettings(wxCommandEvent& event);

    void CalculateLivingNeighborCount();

    // Define the event table for MainWindow
    wxDECLARE_EVENT_TABLE();
};
