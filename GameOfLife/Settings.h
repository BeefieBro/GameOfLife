#pragma once
#include "wx/wx.h"
#include <fstream>

struct Settings
{
    unsigned int GridSize = 12;

    int Interval = 50;

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
};