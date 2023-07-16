#include "SettingsDialog.h"

wxBEGIN_EVENT_TABLE(SettingsDialog, wxDialog)
EVT_SPINCTRL(wxID_ANY, SettingsDialog::OnGridSizeChange)
EVT_COLOURPICKER_CHANGED(wxID_ANY, SettingsDialog::OnLivingCellColorChange)
EVT_COLOURPICKER_CHANGED(wxID_ANY, SettingsDialog::OnDeadCellColorChange)
EVT_BUTTON(wxID_OK, SettingsDialog::OnOKButton)
EVT_BUTTON(wxID_CANCEL, SettingsDialog::OnCancelButton)
wxEND_EVENT_TABLE()

SettingsDialog::SettingsDialog(wxWindow* parent, Settings& settings)
    : wxDialog(parent, wxID_ANY, "Settings"), settings(settings)
{
    mMainSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* gridSizeSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* livingCellColorSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* deadCellColorSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);

    // Create labels
    wxStaticText* gridSizeLabel = new wxStaticText(this, wxID_ANY, "Grid Size:");
    wxStaticText* livingCellColorLabel = new wxStaticText(this, wxID_ANY, "Living Cell Color:");
    wxStaticText* deadCellColorLabel = new wxStaticText(this, wxID_ANY, "Dead Cell Color:");

    // Create controls
    mGridSizeCtrl = new wxSpinCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 100);
    mLivingCellColorCtrl = new wxColourPickerCtrl(this, wxID_ANY);
    mDeadCellColorCtrl = new wxColourPickerCtrl(this, wxID_ANY);

    // Create buttons
    wxButton* okButton = new wxButton(this, wxID_OK, "OK");
    wxButton* cancelButton = new wxButton(this, wxID_CANCEL, "Cancel");

    // Add labels and controls to the child box sizers
    gridSizeSizer->Add(gridSizeLabel, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL));
    gridSizeSizer->Add(mGridSizeCtrl, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL));

    livingCellColorSizer->Add(livingCellColorLabel, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL));
    livingCellColorSizer->Add(mLivingCellColorCtrl, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL));

    deadCellColorSizer->Add(deadCellColorLabel, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL));
    deadCellColorSizer->Add(mDeadCellColorCtrl, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL));

    // Add buttons to the button sizer
    buttonSizer->Add(okButton, wxSizerFlags().Border(wxALL, 5));
    buttonSizer->Add(cancelButton, wxSizerFlags().Border(wxALL, 5));

    // Add the child box sizers to the main sizer
    mMainSizer->Add(gridSizeSizer, wxSizerFlags().Expand().Border(wxALL, 5));
    mMainSizer->Add(livingCellColorSizer, wxSizerFlags().Expand().Border(wxALL, 5));
    mMainSizer->Add(deadCellColorSizer, wxSizerFlags().Expand().Border(wxALL, 5));
    mMainSizer->Add(buttonSizer, wxSizerFlags().Align(wxALIGN_CENTER).Border(wxALL, 5));

    SetSizer(mMainSizer);

    // Bind event handlers to the controls
    mGridSizeCtrl->Bind(wxEVT_SPINCTRL, [&](wxSpinEvent& event) {
        OnGridSizeChange(event);
        });

    mLivingCellColorCtrl->Bind(wxEVT_COLOURPICKER_CHANGED, [&](wxColourPickerEvent& event) {
        OnLivingCellColorChange(event);
        });

    mDeadCellColorCtrl->Bind(wxEVT_COLOURPICKER_CHANGED, [&](wxColourPickerEvent& event) {
        OnDeadCellColorChange(event);
        });

    // Set initial values from the settings
    mGridSizeCtrl->SetValue(settings.GridSize);
    mLivingCellColorCtrl->SetColour(settings.SetLivingColor());
    mDeadCellColorCtrl->SetColour(settings.SetDeadColor());
}

void SettingsDialog::OnGridSizeChange(wxSpinEvent& event)
{
    settings.GridSize = event.GetPosition();
}

void SettingsDialog::OnLivingCellColorChange(wxColourPickerEvent& event)
{
    settings.SetColor(event.GetColour());
}

void SettingsDialog::OnDeadCellColorChange(wxColourPickerEvent& event)
{
    // Handle dead cell color change event
}

void SettingsDialog::OnOKButton(wxCommandEvent& event)
{
    // Save the settings and close the dialog
    settings.SaveData();
    Close();
}

void SettingsDialog::OnCancelButton(wxCommandEvent& event)
{
    // Close the dialog without saving the settings
    Close();
}
