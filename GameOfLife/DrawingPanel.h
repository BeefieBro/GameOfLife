#pragma once
#include "wx/wx.h"

class DrawingPanel : public wxPanel
{
private:
	void OnPaint(wxPaintEvent& event);
	int mGridSize;
	int mCellSize;

public:
	DrawingPanel(wxFrame* parent);
	~DrawingPanel();
};
 
