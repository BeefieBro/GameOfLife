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
    context->SetFont(wxFontInfo(16).Family(wxFONTFAMILY_TELETYPE), *wxRED);

    // Draw cells
    context->SetPen(*wxBLACK);
    for (int row = 0; row < mGridSize; row++)
    {
        for (int col = 0; col < mGridSize; col++)
        {
            double rectX = col * mCellWidth;
            double rectY = row * mCellHeight;

            if (mGameBoard[row][col])
                context->SetBrush(mSettings->GetLivingColor());
            else
                context->SetBrush(mSettings->GetDeadColor());

            context->DrawRectangle(rectX, rectY, mCellWidth, mCellHeight);

            if (mSettings->ShowNeighborCount && rNeighborCount[row][col] > 0)
            {
                wxString text = std::to_string(rNeighborCount[row][col]);
                double textWidth, textHeight;

                context->GetTextExtent(text, &textWidth, &textHeight);
                double textX = rectX + (mCellWidth / 2) - (textWidth / 2);
                double textY = rectY + (mCellHeight / 2) - (textHeight / 2);
                context->DrawText(text, textX, textY);
            }
        }
    }

    // Draw the grid lines if ShowGrid is true
    if (mSettings->ShowGrid)
    {
        wxPen gridPen(*wxLIGHT_GREY, 1); // Create a pen with light grey color and thickness of 1
        context->SetPen(gridPen);

        for (int i = 0; i <= mGridSize; i++)
        {
            // Vertical lines
            double x = i * mCellWidth;
            context->StrokeLine(x, 0, x, panelHeight);

            // Horizontal lines
            double y = i * mCellHeight;
            context->StrokeLine(0, y, panelWidth, y);
        }
    }

    // Draw the thicker grid lines every 10 lines if Show10x10Grid is true
    if (mSettings->Show10x10Grid)
    {
        wxPen thickGridPen(*wxBLACK, 2); // Create a pen with black color and thickness of 2
        context->SetPen(thickGridPen);

        int linesToDraw = mGridSize / 10;
        for (int i = 1; i <= linesToDraw; i++)
        {
            // Vertical lines
            double x = i * 10 * mCellWidth;
            context->StrokeLine(x, 0, x, panelHeight);

            // Horizontal lines
            double y = i * 10 * mCellHeight;
            context->StrokeLine(0, y, panelWidth, y);
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

void DrawingPanel::SetShowGrid(bool showGrid)
{ 
    mSettings->ShowGrid = showGrid;
}
void DrawingPanel::SetShow10x10Grid(bool show10x10Grid)
{ 
    mSettings->Show10x10Grid = show10x10Grid;
}



DrawingPanel::~DrawingPanel()
{
}
