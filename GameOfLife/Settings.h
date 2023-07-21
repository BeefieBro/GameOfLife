#pragma once
#include "wx/wx.h"
#include <fstream>

struct Settings
{
    unsigned int GridSize = 12;

    int Interval = 50;

    bool ShowNeighborCount = false;

    bool IsToroidal = false;

    unsigned int AliveRed = 128;
    unsigned int AliveGreen = 128;
    unsigned int AliveBlue = 128;
    unsigned int AliveAlpha = 128;

    unsigned int DeadRed = 255;
    unsigned int DeadGreen = 255;
    unsigned int DeadBlue = 255;
    unsigned int DeadAlpha = 255;

    void LoadData()
    {
        std::ifstream file("settings.bin", std::ios::binary | std::ios::in);
        file.read((char*)this, sizeof(Settings));
        file.close();
    }

    void SaveData()
    {
        std::ofstream file("settings.bin", std::ios::out | std::ios::binary);
        file.write((char*)this, sizeof(Settings));
        file.close();
    }


    wxColor GetLivingColor()
    {
        wxColor color(AliveRed, AliveGreen, AliveBlue, AliveAlpha);
        return color;
    }

    wxColor GetDeadColor()
    {
        wxColor color(DeadRed, DeadGreen, DeadBlue, DeadAlpha);
        return color;
    }

    void SetLivingColor(wxColor color)
    {
        AliveRed = color.GetRed();
        AliveGreen = color.GetGreen();
        AliveBlue = color.GetBlue();
        AliveAlpha = color.GetAlpha();
    }
    void SetDeadColor(wxColor color)
    {
        DeadRed = color.GetRed();
        DeadGreen = color.GetGreen();
        DeadBlue = color.GetBlue();
        DeadAlpha = color.GetAlpha();
    }
    void ResetToDefault()
    {
        // Set each setting value to its default state
        GridSize = 15; // Change this to the default grid size
        AliveRed = 128; // Change this to the default living cell color (red component)
        AliveGreen = 128; // Change this to the default living cell color (green component)
        AliveBlue = 128; // Change this to the default living cell color (blue component)
        AliveAlpha = 128; // Change this to the default living cell color (alpha component)
        DeadRed = 255; // Change this to the default dead cell color (red component)
        DeadGreen = 255; // Change this to the default dead cell color (green component)
        DeadBlue = 255; // Change this to the default dead cell color (blue component)
        DeadAlpha = 255; // Change this to the default dead cell color (alpha component)

        // Save the settings to the file so the old settings are gone
        SaveData();
    }
};