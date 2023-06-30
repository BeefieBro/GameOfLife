#include "DrawingPanel.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"


DrawingPanel::DrawingPanel(wxFrame* parent) : wxPanel(parent, wxID_ANY, wxPoint(110, 110), wxSize(100, 100))
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




	delete context;
}
DrawingPanel::~DrawingPanel()
{

}

