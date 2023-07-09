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
    int mGenerationCount;
    int mLivingCellCount;
    wxStatusBar* mStatusBar;
    wxToolBar* mToolBar;

public:
    MainWindow();
    ~MainWindow();

    void OnSizeChange(wxSizeEvent& event);
    void InitializeGrid();
    void UpdateStatusBar();

    void OnNextGeneration(wxCommandEvent& event);
    void OnPlay(wxCommandEvent& event);
    void OnPause(wxCommandEvent& event);
    void OnClear(wxCommandEvent& event);
    int CountLivingNeighbors(int row, int col);
    void CalculateNextGeneration();
    void ClearBoard();

    wxDECLARE_EVENT_TABLE();
};
