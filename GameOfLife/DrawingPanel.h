#pragma once

#include "wx/wx.h"
#include <vector>

class DrawingPanel : public wxPanel
{
private:
    std::vector<std::vector<bool>>& mGameBoard;
    int mGridSize;
    int mCellWidth;
    int mCellHeight;


public:
    DrawingPanel(wxFrame* parent, std::vector<std::vector<bool>>& gameBoard);
    ~DrawingPanel();
    void OnPaint(wxPaintEvent& event);
    void UpdateCellSize();
    void SetSize(const wxSize& size);
    void SetGridSize(int size);
    void OnMouseClick(wxMouseEvent& event);

    void SetGameBoard(std::vector<std::vector<bool>>& gameBoard);

    wxDECLARE_EVENT_TABLE();
};
