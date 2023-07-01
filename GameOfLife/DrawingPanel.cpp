#include "DrawingPanel.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"


DrawingPanel::DrawingPanel(wxFrame* parent) : wxPanel(parent, wxID_ANY)
{
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    Bind(wxEVT_PAINT, &DrawingPanel::OnPaint, this);

    mGridSize = 15;
}

void DrawingPanel::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);
    wxGraphicsContext* context = wxGraphicsContext::Create(dc);
    if (!context)
        return;

    context->SetPen(*wxBLACK);
    context->SetBrush(*wxWHITE);

    wxSize panelSize = GetSize();
    int panelWidth = panelSize.GetWidth();
    int panelHeight = panelSize.GetHeight();

    mCellWidth = panelWidth / mGridSize;
    mCellHeight = panelHeight / mGridSize;

    for (int row = 0; row < mGridSize; row++)
    {
        for (int col = 0; col < mGridSize; col++)
        {
            int rectX = col * mCellWidth;
            int rectY = row * mCellHeight;

            context->DrawRectangle(rectX, rectY, mCellWidth, mCellHeight);
        }
    }

    delete context;
}

void DrawingPanel::UpdateCellSize()
{
	wxSize mPanelSize = GetSize();

	int mPanelWidth = mPanelSize.GetWidth();
	int mPanelHeight = mPanelSize.GetHeight();

	mCellWidth = mPanelWidth / mGridSize;
	mCellHeight = mPanelHeight / mGridSize;
}



DrawingPanel::~DrawingPanel()
{

}

