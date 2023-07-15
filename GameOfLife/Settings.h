#pragma once
#include "wx/wx.h"
#include <fstream>

struct Settings
{
	unsigned int GridSize = 15;

	int Interval = 50;



	unsigned int Red = 128;
	unsigned int Green = 128;
	unsigned int Blue = 128;
	unsigned int Alpha = 255;
	unsigned int AliveRed = 128;
	unsigned int AliveGreen = 128;
	unsigned int AliveBlue = 128;
	unsigned int AliveAlpha = 128;
	unsigned int DeadRed = 255;
	unsigned int DeadGreen = 255;
	unsigned int DeadBlue = 255;
	unsigned int DeadAlpha = 255;

	wxColor SetLivingColor()
	{
		wxColor color(AliveRed, AliveGreen, AliveBlue, AliveAlpha);
		return color;
	}
	wxColor SetDeadColor()
	{
		wxColor color(DeadRed, DeadGreen, DeadBlue, DeadAlpha);
		return color;
	}
	void SetColor(wxColor color)
	{
		Red = color.GetRed();
		Green = color.GetGreen();
		Blue = color.GetBlue();
		Alpha = color.GetAlpha();
	}

	wxColor GetColor()
	{
		wxColor color(Red, Green, Blue, Alpha);
		return color;
	}

	void LoadData()
	{
		std::ifstream file("settings.bin", std::ios::binary | std::ios::in);
		file.read(reinterpret_cast<char*>(this), sizeof(Settings));
		file.close();
	}

	void SaveData()
	{
		std::ofstream file("settings.bin", std::ios::binary | std::ios::out);
		file.write(reinterpret_cast<const char*>(this), sizeof(Settings));
		file.close();






};