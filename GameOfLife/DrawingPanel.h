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
    double mGridSize;
    double mCellWidth;
    double mCellHeight;
    MainWindow* pMainWindow;


public:
    DrawingPanel(wxFrame* parent, std::vector<std::vector<bool>>& gameBoard, Settings* settings);
    ~DrawingPanel();

    void OnPaint(wxPaintEvent& event);
    void UpdateCellSize();
    void SetSize(const wxSize& size);
    void SetGridSize(int size);
    void OnMouseClick(wxMouseEvent& event);

    void SetGameBoard(std::vector<std::vector<bool>>& gameBoard);

    void SetGridSize(unsigned int gridSize);
    unsigned int GetGridSize() const;

    wxDECLARE_EVENT_TABLE();
};

