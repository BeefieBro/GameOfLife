#include "DrawingPanel.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"


DrawingPanel::DrawingPanel(wxFrame* parent) : wxPanel(parent, wxID_ANY, wxPoint(110, 110), wxSize(100, 100))
{
	SetBackgroundStyle(wxBG_STYLE_PAINT);
	Bind(wxEVT_PAINT, &DrawingPanel::OnPaint, this);

	mGridSize = 15;
	mCellSize = 10;
}
void DrawingPanel::OnPaint(wxPaintEvent& event)
{
	wxAutoBufferedPaintDC dc(this);
	dc.Clear();

	wxGraphicsContext* context = wxGraphicsContext::Create(dc);
	if (!context) return;

	context->SetPen(*wxBLACK);
	context->SetBrush(*wxWHITE);

	// mRow is current row. mColumn is current column.
	// mRow & mColumn are coordinants of each rectangle
	for (int mRow = 0; mRow < mGridSize; mRow++)
	{
		for (int mColumn = 0; mColumn < mGridSize; mColumn++)
		{
			int mRectX = mColumn * mCellSize;
			int mRectY = mRow * mCellSize;

			context->DrawRectangle(mRectX, mRectY, mCellSize, mCellSize);
		}
	}

	delete context;
}
DrawingPanel::~DrawingPanel()
{

}

