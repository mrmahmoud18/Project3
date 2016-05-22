#pragma once

#include "../GraphicsInfo.h"
#include "../Actions/Action.h"
#include "../Components/Component.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Bar;
class Button;
class Canvas;
class Input;
class Output;

class Interface
{
public:
    enum MouseStatus{POINTER, CLICKER, NAVIGATION, DRAG, TEXT, HIDDEN};
    Interface();
    ~Interface();
    void SetBusy(bool r_Busy);
    void SetMouseStatus(MouseStatus r_MouseStatus);
    std::vector<Button*> GetActiveButtons();
    std::vector<Button*> GetGatesButtons();
    void DrawGatesBars();
    void EnableActions(std::vector<Action::ActionType> ActionTypes);
    void DisableActions(std::vector<Action::ActionType> ActionTypes);
    void SwitchAppMode();
    void SwitchAppTheme();
    void ZoomIn();
    void ZoomOut();
    void ShiftOffsetBy(std::pair<int,int> Delta);
    void ClearCanvas();
    void ResetWindow();
    void SyncWindow();
    void DrawComponent(const GraphicsInfo& GfxInfo, std::string ImagePath, Component::Status r_Status);
	void DrawLabel(const GraphicsInfo& GfxInfo, std::string Text);
	void DrawPin(std::pair<int,int> Center, bool Connected = false);
	void DrawConnection(const std::vector< std::pair<int,int> >& Vertices, bool Selected = false);
	void PrintMsg(std::string Text);
	void SetTooltipText(std::string Text);
	std::pair<int,int> GetMousePosition(bool Absolute=false) const;
	std::pair<int,int> GetPointClicked(bool Absolute=false) const;
	std::pair<int,int> GetInstantClick(bool Absolute=false) const;
	std::pair<int,int> GetInstantRelease(bool Absolute=false) const;
	std::string GetSrting() const;
	Action::ActionType GetUserAction() const;
	bool IsDragging() const;

private:
    friend class Input;
    friend class Output;

    Input* MainInput;
    Output* MainOutput;

    Bar* StatusBar;
    Bar* DesignBar;
    Bar* SimulationBar;
    Bar* GatesBar;
    Bar* NGatesBar;
    Canvas* SimCanvas;
    Bar* GetActiveBar();

    sf::RenderWindow Window;

    int Zoom;
    std::pair<int,int> Offset;
    std::pair<int,int> BufferPoint(std::pair<int,int> Point) const;
    std::pair<int,int> ReverseBufferPoint(std::pair<int,int> Point) const;
    GraphicsInfo BufferGfxInfo(GraphicsInfo GfxInfo) const;

    enum {DESIGN, SIMULATION} AppMode;

    int AppTheme;
    std::vector<std::string> Themes;

    bool m_Busy;

	int         WindowWidth,
                WindowHeight,
                Spacing,
                BorderSize,
                SelectionBorder,
                StatusBarHeight,
                GatesBarHeight,
                ToolBarWidth,
                GateSide,
                GridSize,
                PinRadius;

    sf::Color   AlphaColor,
                BetaColor,
                BackgroundColor,
                SelectionColor,
                GridColor;

};