#pragma once
#include "wx/wx.h"
#include "wx/spinctrl.h"
#include "wx/clrpicker.h"
#include <wx/checkbox.h>
#include "Settings.h"

class SettingsDialog : public wxDialog
{
private:

    unsigned int mUpdatedGridSize;


    wxBoxSizer* mMainSizer;
    wxSpinCtrl* mGridSizeCtrl;
    wxColourPickerCtrl* mLivingCellColorCtrl;
    wxColourPickerCtrl* mDeadCellColorCtrl;
    Settings& settings; // Reference to the existing Settings object

public:
    SettingsDialog(wxWindow* parent, Settings& settings);


    void OnOKButton(wxCommandEvent& event);
    void OnCancelButton(wxCommandEvent& event);
    unsigned int GetUpdatedGridSize() const;
    void OnDefaultSettingsButton(wxCommandEvent& event);
    void OnFinite(wxCommandEvent& event);
    void OnTorodial(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
};
