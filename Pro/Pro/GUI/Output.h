#pragma once

#include "Interface.h"
#include "../GraphicsInfo.h"
#include "Button.h"
#include "../Components/Component.h"

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Interface;

class Output
{
private:
	Interface* pInterface;
	Interface::MouseStatus m_MouseStatus;
	std::string TooltipText;
	void DrawImage(const GraphicsInfo& GfxInfo, std::string ImagePath);
	void DrawRectangle(const GraphicsInfo& GfxInfo, sf::Color Color, int Thickness=0, sf::Color OutlineColor=sf::Color::Transparent);
	void DrawText(const GraphicsInfo& GfxInfo, std::string Text, std::string FontPath);
	void DrawTooltip();

public:
	Output(Interface* pInterface);
	void DrawBar(const GraphicsInfo& GfxInfo);
	void DrawButton(const GraphicsInfo& GfxInfo, std::string ImagePath, Button::ButtonStatus Status);
	void DrawCanvas(const GraphicsInfo& GfxInfo, bool ShowGrid = true);
	void DrawComponent(const GraphicsInfo& GfxInfo, std::string ImagePath, Component::Status r_Status);
	void DrawLabel(const GraphicsInfo& GfxInfo, std::string Text);
	void DrawPin(std::pair<int,int> Center, bool Connected, std::string ImagePath);
	void DrawConnection(const std::vector< std::pair<int,int> >& Vertices, bool Selected);
	void PrintMsg(std::string Text);
	void SetTooltipText(std::string Text);
	void SetMouseStatus(Interface::MouseStatus r_MouseStatus);
	void UpdateActiveBar();
	void DrawGatesBars();
	void DrawBorders();
	void HandleMouse();
	void SyncWindow();
};
