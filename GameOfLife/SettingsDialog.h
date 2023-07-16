#pragma once
#include "wx/wx.h"
#include "wx/spinctrl.h"
#include "wx/clrpicker.h"
#include "Settings.h"

class SettingsDialog : public wxDialog
{
private:
    wxBoxSizer* mMainSizer;
    wxSpinCtrl* mGridSizeCtrl;
    wxColourPickerCtrl* mLivingCellColorCtrl;
    wxColourPickerCtrl* mDeadCellColorCtrl;
    Settings& settings; // Reference to the existing Settings object

public:
    SettingsDialog(wxWindow* parent, Settings& settings);

    // Event handlers
    void OnGridSizeChange(wxSpinEvent& event);
    void OnLivingCellColorChange(wxColourPickerEvent& event);
    void OnDeadCellColorChange(wxColourPickerEvent& event);
    void OnOKButton(wxCommandEvent& event);
    void OnCancelButton(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
};
