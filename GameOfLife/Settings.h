#pragma once
#include "wx/wx.h"

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
};