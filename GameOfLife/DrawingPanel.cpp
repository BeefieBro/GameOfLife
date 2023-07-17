#include "DrawingPanel.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"
#include "MainWindow.h"

wxBEGIN_EVENT_TABLE(DrawingPanel, wxPanel)
EVT_PAINT(DrawingPanel::OnPaint)
EVT_LEFT_UP(DrawingPanel::OnMouseClick)
wxEND_EVENT_TABLE()

DrawingPanel::DrawingPanel(wxFrame* parent, std::vector<std::vector<bool>>& gameBoard,
    std::vector<std::vector<int>>& neighborCount, Settings* settings)
    : wxPanel(parent, wxID_ANY), mGameBoard(gameBoard),rNeighborCount(neighborCount),  mSettings(settings)
{
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    mCellWidth = 0;
    mCellHeight = 0;

    pMainWindow = (MainWindow*)parent;
}


void DrawingPanel::OnPaint(wxPaintEvent& event)
{
    mGridSize = mSettings->GridSize;
    wxAutoBufferedPaintDC dc(this);
    dc.Clear();
    wxGraphicsContext* context = wxGraphicsContext::Create(dc);
    if (!context)
        return;

    wxSize panelSize = GetClientSize();
    double panelWidth = panelSize.GetWidth();
    double panelHeight = panelSize.GetHeight();

    mCellWidth = panelWidth / mGridSize;
    mCellHeight = panelHeight / mGridSize;

    context->SetPen(*wxLIGHT_GREY);
    context->SetFont(wxFontInfo(16), *wxRED);


    // Draw cells
    context->SetPen(*wxBLACK);
    for (int row = 0; row < mGridSize; row++)
    {
        for (int col = 0; col < mGridSize; col++)
        {
            int rectX = col * mCellWidth;
            int rectY = row * mCellHeight;

            if (mGameBoard[row][col])
                context->SetBrush(mSettings->GetLivingColor());
            else
                context->SetBrush(mSettings->GetDeadColor());

            context->DrawRectangle(rectX, rectY, mCellWidth, mCellHeight);

            

            if (mSettings->ShowNeighborCount && rNeighborCount[row][col] > 0)
            {
               
                wxString text = std::to_string(rNeighborCount[row][col]);
                
                
                double x, y;

                context->GetTextExtent(text, &x, &y);
                context->DrawText(text, rectX +(mCellWidth/2) - (x / 2), rectY + (mCellHeight/2) - (y/2));
            }
        }
    }
    delete context;
}

void DrawingPanel::OnMouseClick(wxMouseEvent& event)
{
    mGridSize = mSettings->GridSize;
    int x = event.GetX();
    int y = event.GetY();

    int row = y / mCellHeight;
    int col = x / mCellWidth;

    // Toggle the value of the clicked cell in the game board
    if (row >= 0 && row < mGridSize && col >= 0 && col < mGridSize)
        mGameBoard[row][col] = !mGameBoard[row][col];

    pMainWindow->CalculateLivingNeighborCount();
    pMainWindow->RefreshLivingCellCount();

    
}

void DrawingPanel::SetSize(const wxSize& size)
{
    wxPanel::SetSize(size);
    UpdateCellSize();
    Refresh();
}

void DrawingPanel::SetGridSize(int size)
{
    mGridSize = mSettings->GridSize;
    UpdateCellSize();
    Refresh();
}

void DrawingPanel::UpdateCellSize()
{
    mGridSize = mSettings->GridSize;
    wxSize panelSize = GetClientSize();
    int panelWidth = panelSize.GetWidth();
    int panelHeight = panelSize.GetHeight();

    mCellWidth = panelWidth / mGridSize;
    mCellHeight = panelHeight / mGridSize;
}

void DrawingPanel::SetGameBoard(std::vector<std::vector<bool>>& gameBoard)
{
    mGameBoard = gameBoard;
}




DrawingPanel::~DrawingPanel()
{
}
