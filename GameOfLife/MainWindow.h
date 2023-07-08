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

public:
    MainWindow();
    ~MainWindow();

    void OnSizeChange(wxSizeEvent& event);
    void InitializeGrid();
    void UpdateStatusBar();

    void OnNextGeneration(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
};
