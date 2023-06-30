#include "DrawingPanel.h"
#include "ex/graphics.h"
#include "ex/dcbuffer.h"


DrawingPanel::DrawingPanel(wxFrame* parent) : wxPanel(parent, wxID_ANY, wxPoint(110, 110), wxSize(400, 400))
{
	SetBackgroundStyle(wxBG_STYLE_PAINT);
	Bind(wxEVT_PAINT, &DrawingPanel::OnPaint, this);
}
void DrawingPanel::OnPaint(wxPaintEvent& event)
{
	wxAutoBufferedPaintDC dc(this);
	dc.Clear();

	wxGraphicsContext* context = wxGraphicsContext::Create(dc);
	if (!context) return;

	context->SetPen(*wxBLACK);
	context->SetBrush(*wxRED);

	context->DrawRectangle(10, 10, 20, 30);

	delete context;
}
