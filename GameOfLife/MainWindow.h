#pragma once
#include "wx/wx.h"
#include "DrawingPanel.h"

class MainWindow : public wxFrame
{

private:
    DrawingPanel* drawingPanel = nullptr;
    wxBoxSizer* mBoxSizer;
    std::vector<std::vector<bool>> mGameBoard;
    int mGridSize = 15;
    int mGenerationCount = 0; // Number of generations
    int mLivingCellCount = 0; // Number of living cells
    wxStatusBar* mStatusBar; // Status bar
    wxToolBar* mToolBar;
    wxTimer* mTimer;
    int mTimerInterval = 50;

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


    // Define the event table for MainWindow
    wxDECLARE_EVENT_TABLE();
};
