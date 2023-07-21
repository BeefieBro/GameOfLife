#pragma once

#include "wx/wx.h"
#include <vector>
#include "Settings.h"

class MainWindow;

class DrawingPanel : public wxPanel
{
private:
    Settings* mSettings;

    std::vector<std::vector<bool>>& mGameBoard;
    std::vector<std::vector<int>>& rNeighborCount;

    double mGridSize;
    double mCellWidth;
    double mCellHeight;
    MainWindow* pMainWindow;


public:
    DrawingPanel(wxFrame* parent, std::vector<std::vector<bool>>& gameBoard, std::vector<std::vector<int>>& neighborCount, Settings* settings);
    ~DrawingPanel();

    void OnPaint(wxPaintEvent& event);
    void UpdateCellSize();
    void SetSize(const wxSize& size);
    void SetGridSize(int size);
    void OnMouseClick(wxMouseEvent& event);

    void SetGameBoard(std::vector<std::vector<bool>>& gameBoard);
    void SetShowGrid(bool showGrid);
    void SetShow10x10Grid(bool show10x10Grid); 


    


    wxDECLARE_EVENT_TABLE();
};

