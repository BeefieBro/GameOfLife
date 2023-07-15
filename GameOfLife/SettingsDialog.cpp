#include "SettingsDialog.h"

wxBEGIN_EVENT_TABLE(SettingsDialog, wxDialog)
EVT_SPINCTRL(wxID_ANY, SettingsDialog::OnGridSizeChange)
EVT_COLOURPICKER_CHANGED(wxID_ANY, SettingsDialog::OnLivingCellColorChange)
EVT_COLOURPICKER_CHANGED(wxID_ANY, SettingsDialog::OnDeadCellColorChange)
wxEND_EVENT_TABLE()

