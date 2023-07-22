#include "SettingsDialog.h"
#include "Settings.h"

enum
{
    ID_DEFAULTSETTINGS = wxID_HIGHEST + 1,
    ID_FINITE,
    ID_TORODIAL,
    ID_TIMERINTERVAL
};

wxBEGIN_EVENT_TABLE(SettingsDialog, wxDialog)
EVT_BUTTON(wxID_OK, SettingsDialog::OnOKButton)
EVT_BUTTON(wxID_CANCEL, SettingsDialog::OnCancelButton)
EVT_BUTTON(ID_DEFAULTSETTINGS, SettingsDialog::OnDefaultSettingsButton)
wxEND_EVENT_TABLE()

SettingsDialog::SettingsDialog(wxWindow* parent, Settings& settings)
    : wxDialog(parent, wxID_ANY, "Settings"), settings(settings)
{
    mUpdatedGridSize = settings.GridSize;



    mMainSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* gridSizeSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* livingCellColorSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* deadCellColorSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* timerIntervalSizer = new wxBoxSizer(wxHORIZONTAL);
    

    // Create labels
    wxStaticText* gridSizeLabel = new wxStaticText(this, wxID_ANY, "Grid Size:");
    wxStaticText* livingCellColorLabel = new wxStaticText(this, wxID_ANY, "Living Cell Color:");
    wxStaticText* deadCellColorLabel = new wxStaticText(this, wxID_ANY, "Dead Cell Color:");
    wxStaticText* timerIntervalLabel = new wxStaticText(this, wxID_ANY, "Timer Interval");

    // Create controls
    mGridSizeCtrl = new wxSpinCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 100);
    mLivingCellColorCtrl = new wxColourPickerCtrl(this, wxID_ANY);
    mDeadCellColorCtrl = new wxColourPickerCtrl(this, wxID_ANY);
    mTimerIntervalCtrl = new wxSpinCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 50, 10000);

    // Create buttons
    wxButton* okButton = new wxButton(this, wxID_OK, "OK");
    wxButton* cancelButton = new wxButton(this, wxID_CANCEL, "Cancel");
    wxButton* defaultSettingsButton = new wxButton(this, ID_DEFAULTSETTINGS, "Default Settings");

    

    // Add labels and controls to the child box sizers
    

    gridSizeSizer->Add(gridSizeLabel, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL));
    gridSizeSizer->Add(mGridSizeCtrl, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL));

    timerIntervalSizer->Add(timerIntervalLabel, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL));
    timerIntervalSizer->Add(mTimerIntervalCtrl, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL));

    livingCellColorSizer->Add(livingCellColorLabel, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL));
    livingCellColorSizer->Add(mLivingCellColorCtrl, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL));

    deadCellColorSizer->Add(deadCellColorLabel, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL));
    deadCellColorSizer->Add(mDeadCellColorCtrl, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL));

    // Add buttons to the button sizer
    buttonSizer->Add(okButton, wxSizerFlags().Border(wxALL, 5));
    buttonSizer->Add(cancelButton, wxSizerFlags().Border(wxALL, 5));
    buttonSizer->Add(defaultSettingsButton, wxSizerFlags().Border(wxALL, 5));

    // Add the child box sizers to the main sizer
    mMainSizer->Add(gridSizeSizer, wxSizerFlags().Expand().Border(wxALL, 5));
    mMainSizer->Add(timerIntervalSizer, wxSizerFlags().Expand().Border(wxALL, 5));
    mMainSizer->Add(livingCellColorSizer, wxSizerFlags().Expand().Border(wxALL, 5));
    mMainSizer->Add(deadCellColorSizer, wxSizerFlags().Expand().Border(wxALL, 5));
    mMainSizer->Add(buttonSizer, wxSizerFlags().Align(wxALIGN_CENTER).Border(wxALL, 5));

    SetSizer(mMainSizer);

    // Set initial values from the settings
    mGridSizeCtrl->SetValue(settings.GridSize);
    mTimerIntervalCtrl->SetValue(settings.Interval);
    mLivingCellColorCtrl->SetColour(settings.GetLivingColor());
    mDeadCellColorCtrl->SetColour(settings.GetDeadColor());
}

void SettingsDialog::OnOKButton(wxCommandEvent& event)
{
    settings.GridSize = mGridSizeCtrl->GetValue();  // Save the updated GridSize value
    settings.Interval = mTimerIntervalCtrl->GetValue();
    settings.SetLivingColor(mLivingCellColorCtrl->GetColour());
    settings.SetDeadColor(mDeadCellColorCtrl->GetColour());
    settings.SaveData();  // Save the settings to a file
    EndModal(wxID_OK);  // Close the dialog with OK status
}

void SettingsDialog::OnCancelButton(wxCommandEvent& event)
{
    // Close the dialog without saving the settings
    EndModal(wxID_CANCEL);
}
unsigned int SettingsDialog::GetUpdatedGridSize() const
{
    return mUpdatedGridSize;
}

void SettingsDialog::OnDefaultSettingsButton(wxCommandEvent& event)
{
    settings.ResetToDefault(); // Call the ResetToDefault method
    mGridSizeCtrl->SetValue(settings.GridSize); // Update the GridSize control with the default value
    mLivingCellColorCtrl->SetColour(settings.GetLivingColor()); // Update the LivingCellColor control with the default value
    mDeadCellColorCtrl->SetColour(settings.GetDeadColor()); // Update the DeadCellColor control with the default value
    event.Skip();
}
void SettingsDialog::OnFinite(wxCommandEvent& event)
{

}
void SettingsDialog::OnTorodial(wxCommandEvent& event)
{

}