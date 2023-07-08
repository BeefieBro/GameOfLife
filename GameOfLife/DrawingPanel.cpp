#include "DrawingPanel.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h" 

DrawingPanel::DrawingPanel(wxFrame* parent, std::vector<std::vector<bool>>& gameBoard)
    : wxPanel(parent, wxID_ANY), mGameBoard(gameBoard)
{
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    Bind(wxEVT_PAINT, &DrawingPanel::OnPaint, this);
    Bind(wxEVT_LEFT_UP, &DrawingPanel::OnMouseClick, this); // Bind the left-up mouse event
    mGridSize = 15;
    mCellWidth = 0;
    mCellHeight = 0;
}

void DrawingPanel::OnPaint(wxPaintEvent& event)
{
    wxAutoBufferedPaintDC dc(this);
    wxGraphicsContext* context = wxGraphicsContext::Create(dc);
    if (!context)
        return;

    context->SetPen(*wxBLACK);

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

            if (mGameBoard[row][col])
                context->SetBrush(*wxLIGHT_GREY);
            else
                context->SetBrush(*wxWHITE);

            context->DrawRectangle(rectX, rectY, mCellWidth, mCellHeight);
        }
    }

    delete context;
}

void DrawingPanel::UpdateCellSize()
{
    wxSize panelSize = GetSize();
    int panelWidth = panelSize.GetWidth();
    int panelHeight = panelSize.GetHeight();

    mCellWidth = panelWidth / mGridSize;
    mCellHeight = panelHeight / mGridSize;
}

void DrawingPanel::SetSize(const wxSize& size)
{
    wxPanel::SetSize(size);
    UpdateCellSize();
    Refresh();
}

void DrawingPanel::SetGridSize(int size)
{
    mGridSize = size;
    UpdateCellSize();
    Refresh();
}

void DrawingPanel::OnMouseUp(wxMouseEvent& event)
{
    // No implementation needed for this method
}

void DrawingPanel::OnMouseClick(wxMouseEvent& event)
{
    int x = event.GetX();
    int y = event.GetY();

    int row = y / mCellHeight;
    int col = x / mCellWidth;

    if (row >= 0 && row < mGridSize && col >= 0 && col < mGridSize)
        mGameBoard[row][col] = !mGameBoard[row][col];

    Refresh();
}

void DrawingPanel::SetGameBoard(std::vector<std::vector<bool>>& gameBoard)
{
    mGameBoard = gameBoard;
}

DrawingPanel::~DrawingPanel()
{

}
