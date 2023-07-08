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
    void OnMouseUp(wxMouseEvent& event);

    // Add the event handler method for mouse interaction
    void OnMouseClick(wxMouseEvent& event);

    // Add a member function to update the game board reference
    void SetGameBoard(std::vector<std::vector<bool>>& gameBoard);

    // Declare the event table
    wxDECLARE_EVENT_TABLE();
};
