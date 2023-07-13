#pragma once
#include "wx/wx.h"
#include "wx/spinctrl.h"
#include "wx/clrpicker.h"




class SettingsDialog :
    public wxDialog
{
private:
    wxBoxSizer* mMainSizer;

    wxSpinCtrl* mGridSizeCtrl;
    wxColourPickerCtrl* mLivingCellColorCtrl;
    wxColourPickerCtrl* mDeadCellColorCtrl;

    void OnGridSizeChange(wxSpinEvent& event);
    void OnLivingCellColorChange(wxColourPickerEvent& event);
    void OnDeadCellColorChange(wxColourPickerEvent& event);


    wxDECLARE_EVENT_TABLE();


public:
    SettingsDialog(wxWindow* parent);





};
//event tables

wxBEGIN_EVENT_TABLE(SettingsDialog, wxDialog)
EVT_SPINCTRL(wxID_ANY, SettingsDialog::OnGridSizeChange)
EVT_COLOURPICKER_CHANGED(wxID_ANY, SettingsDialog::OnLivingCellColorChange)
EVT_COLOURPICKER_CHANGED(wxID_ANY, SettingsDialog::OnDeadCellColorChange)
wxEND_EVENT_TABLE()



SettingsDialog::SettingsDialog(wxWindow* parent)
    : wxDialog(parent, wxID_ANY, "Settings")
{
    mMainSizer = new wxBoxSizer(wxVERTICAL);



    wxBoxSizer* gridSizeSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* livingCellColorSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* deadCellColorSizer = new wxBoxSizer(wxHORIZONTAL);

    // Create labels
    wxStaticText* gridSizeLabel = new wxStaticText(this, wxID_ANY, "Grid Size:");
    wxStaticText* livingCellColorLabel = new wxStaticText(this, wxID_ANY, "Living Cell Color:");
    wxStaticText* deadCellColorLabel = new wxStaticText(this, wxID_ANY, "Dead Cell Color:");

    // Create controls
    mGridSizeCtrl = new wxSpinCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 100);
    mLivingCellColorCtrl = new wxColourPickerCtrl(this, wxID_ANY);
    mDeadCellColorCtrl = new wxColourPickerCtrl(this, wxID_ANY);

    // Add labels and controls to the child box sizers
    gridSizeSizer->Add(gridSizeLabel, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL));
    gridSizeSizer->Add(mGridSizeCtrl, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL));

    livingCellColorSizer->Add(livingCellColorLabel, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL));
    livingCellColorSizer->Add(mLivingCellColorCtrl, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL));

    deadCellColorSizer->Add(deadCellColorLabel, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL));
    deadCellColorSizer->Add(mDeadCellColorCtrl, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL));

    // Add the child box sizers to the main sizer
    mMainSizer->Add(gridSizeSizer, wxSizerFlags().Expand().Border(wxALL, 5));
    mMainSizer->Add(livingCellColorSizer, wxSizerFlags().Expand().Border(wxALL, 5));
    mMainSizer->Add(deadCellColorSizer, wxSizerFlags().Expand().Border(wxALL, 5));

    SetSizer(mMainSizer);

    // Bind event handlers to the controls
    mGridSizeCtrl->Bind(wxEVT_SPINCTRL, &SettingsDialog::OnGridSizeChange, this);
    mLivingCellColorCtrl->Bind(wxEVT_COLOURPICKER_CHANGED, &SettingsDialog::OnLivingCellColorChange, this);
    mDeadCellColorCtrl->Bind(wxEVT_COLOURPICKER_CHANGED, &SettingsDialog::OnDeadCellColorChange, this);


}

void SettingsDialog::OnGridSizeChange(wxSpinEvent& event)
{
    int gridSize = mGridSizeCtrl->GetValue();
}
void SettingsDialog::OnLivingCellColorChange(wxColourPickerEvent& event)
{
    wxColour livingCellColor = mLivingCellColorCtrl->GetColour();
}
void SettingsDialog::OnDeadCellColorChange(wxColourPickerEvent& event)
{
    wxColor deadCellColor = mDeadCellColorCtrl->GetColour();
}