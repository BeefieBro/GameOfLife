#pragma once
#include "wx/wx.h"

class DrawingPanel : public wxPanel
{
private:
	void OnPaint(wxPaintEvent& event);

	void UpdateCellSize();
	int mGridSize;
	int mCellWidth;
	int mCellHeight;
public:
	DrawingPanel(wxFrame* parent);
	~DrawingPanel();
};
 
