#include "Interface.h"

#include "Bar.h"
#include "Button.h"
#include "Canvas.h"
#include "Input.h"
#include "Output.h"

Interface::Interface(): Window(sf::VideoMode::getDesktopMode(), "Logic Simulator")
{
    Window.setFramerateLimit(0);
    WindowWidth = Window.getSize().x;
    WindowHeight = Window.getSize().y;
    Spacing = 5;
    BorderSize = 6;
    StatusBarHeight = 22;
    GatesBarHeight = 130;
    ToolBarWidth = 60;
    GateSide = 60;
    m_Busy = false;
	Themes.push_back("RIVER/");
	Themes.push_back("TURQUOISE/");
	Themes.push_back("EMERALD/");
	Themes.push_back("AMETHYST/");
	Themes.push_back("SUNFLOWER/");
	AppTheme = -1;
	SwitchAppTheme();
	AppMode = DESIGN;
    GridSize = 10;
    PinRadius = 4;
	Zoom = 2;
	Offset.first = 0;
	Offset.second = 0;

    MainInput = new Input(this),
    MainOutput = new Output(this),
    StatusBar = new Bar(GraphicsInfo(0, WindowHeight-StatusBarHeight, WindowWidth, StatusBarHeight), Bar::HORIZONTAL, 0);
    DesignBar = new Bar(GraphicsInfo(0, 0, ToolBarWidth, WindowHeight-StatusBarHeight-BorderSize), Bar::VERTICAL, Spacing);
    SimulationBar = new Bar(GraphicsInfo(0, 0, ToolBarWidth, WindowHeight-StatusBarHeight-BorderSize), Bar::VERTICAL, Spacing);
    GatesBar = new Bar(GraphicsInfo(ToolBarWidth+BorderSize, 0, WindowWidth-ToolBarWidth-BorderSize, GatesBarHeight), Bar::HORIZONTAL, Spacing);
    NGatesBar = new Bar(GraphicsInfo(ToolBarWidth+BorderSize, GatesBarHeight, WindowWidth-ToolBarWidth-BorderSize, GatesBarHeight), Bar::HORIZONTAL, Spacing);
    SimCanvas = new Canvas(GraphicsInfo(ToolBarWidth+BorderSize, 0, WindowWidth-ToolBarWidth-BorderSize, WindowHeight-StatusBarHeight-BorderSize));
    DesignBar->AddButton("add", Action::ADD);
    DesignBar->AddButton("delete", Action::DELETE, Button::DISABLED);
    DesignBar->AddButton("copy", Action::COPY, Button::DISABLED);
    DesignBar->AddButton("cut", Action::CUT, Button::DISABLED);
    DesignBar->AddButton("paste", Action::PASTE, Button::DISABLED);
    DesignBar->AddButton("undo", Action::UNDO, Button::DISABLED);
    DesignBar->AddButton("redo", Action::REDO, Button::DISABLED);
    DesignBar->AddButton("save", Action::SAVE);
    DesignBar->AddButton("load", Action::LOAD);
    DesignBar->AddButton("simulate", Action::SWITCH_MODE);
    DesignBar->AddButton("color", Action::SWITCH_THEME);
    DesignBar->AddButton("exit", Action::EXIT);
    SimulationBar->AddButton("table", Action::CREATE_TRUTHTABLE);
    SimulationBar->AddButton("stop", Action::SWITCH_MODE, Button::NORMAL, 8);
    SimulationBar->AddButton("color", Action::SWITCH_THEME);
    SimulationBar->AddButton("exit", Action::EXIT);
    GatesBar->AddButton("BUFFER", Action::ADD_BUFF);
    NGatesBar->AddButton("NOT", Action::ADD_INV);
    GatesBar->AddButton("AND2", Action::ADD_AND_GATE_2);
    NGatesBar->AddButton("NAND2", Action::ADD_NAND_GATE_2);
    GatesBar->AddButton("OR2", Action::ADD_OR_GATE_2);
    NGatesBar->AddButton("NOR2", Action::ADD_NOR_GATE_2);
    GatesBar->AddButton("XOR2", Action::ADD_XOR_GATE_2);
    NGatesBar->AddButton("XNOR2", Action::ADD_XNOR_GATE_2);
    GatesBar->AddButton("AND3", Action::ADD_AND_GATE_3);
    NGatesBar->AddButton("NAND3", Action::ADD_NAND_GATE_3);
    GatesBar->AddButton("OR3", Action::ADD_OR_GATE_3);
    NGatesBar->AddButton("NOR3", Action::ADD_NOR_GATE_3);
    GatesBar->AddButton("XOR3", Action::ADD_XOR_GATE_3);
    NGatesBar->AddButton("XNOR3", Action::ADD_XNOR_GATE_3);
    GatesBar->AddButton("SWITCH", Action::ADD_SWITCH);
    NGatesBar->AddButton("LED", Action::ADD_LED);
    DesignBar->OptimizeSpacing();
    SimulationBar->OptimizeSpacing();
    GatesBar->OptimizeSpacing();
    NGatesBar->OptimizeSpacing();
    Window.setMouseCursorVisible(false);
    ClearCanvas();
    ResetWindow();
    SyncWindow();
}

Interface::~Interface()
{
    delete MainInput;
    delete MainOutput;
    delete StatusBar;
    delete DesignBar;
    delete SimulationBar;
    delete GatesBar;
    delete NGatesBar;
    delete SimCanvas;
}

void Interface::SetBusy(bool r_Busy)
{
    m_Busy = r_Busy;
}

void Interface::SetMouseStatus(MouseStatus r_MouseStatus)
{
    MainOutput->SetMouseStatus(r_MouseStatus);
}

std::vector<Button*> Interface::GetActiveButtons()
{
    return GetActiveBar()->GetButtons();
}

std::vector<Button*> Interface::GetGatesButtons()
{
    std::vector<Button*> Buttons;
    Buttons.reserve( GatesBar->GetButtons().size() + NGatesBar->GetButtons().size() );
    Buttons.insert( Buttons.end(), GatesBar->GetButtons().begin(), GatesBar->GetButtons().end() );
    Buttons.insert( Buttons.end(), NGatesBar->GetButtons().begin(), NGatesBar->GetButtons().end() );
    return Buttons;
}

void Interface::DrawGatesBars()
{
    MainOutput->DrawGatesBars();
}

void Interface::EnableActions(std::vector<Action::ActionType> ActionTypes)
{
    const std::vector<Button*>& dummyVector = GetActiveBar()->GetButtons();
    for(unsigned int i = 0; i < ActionTypes.size(); i++)
    {
        for(unsigned int j = 0; j < dummyVector.size(); j++)
            if(dummyVector[j]->GetAction() == ActionTypes[i])
                dummyVector[j]->SetStatus(Button::NORMAL);
    }
}

void Interface::DisableActions(std::vector<Action::ActionType> ActionTypes)
{
    const std::vector<Button*>& dummyVector = GetActiveBar()->GetButtons();
    for(unsigned int i = 0; i < ActionTypes.size(); i++)
    {
        for(unsigned int j = 0; j < dummyVector.size(); j++)
            if(dummyVector[j]->GetAction() == ActionTypes[i])
                dummyVector[j]->SetStatus(Button::DISABLED);
    }
}

void Interface::SwitchAppMode()
{
    AppMode = (AppMode==DESIGN) ? SIMULATION : DESIGN;
}

void Interface::SwitchAppTheme()
{
    AppTheme = (AppTheme+1)%Themes.size();
    BackgroundColor = sf::Color::White;
    switch (AppTheme)
    {
    case 0:
        AlphaColor = sf::Color(0x29, 0x80, 0xb9);
        BetaColor = sf::Color(0x34, 0x98, 0xdb);
        SelectionColor = sf::Color(0x34, 0x98, 0xdb, 0x33);
        GridColor = sf::Color(0x34, 0x98, 0xdb, 0x26);
        break;
    case 1:
        AlphaColor = sf::Color(0x16, 0xa0, 0x85);
        BetaColor = sf::Color(0x1a, 0xbc, 0x9c);
        SelectionColor = sf::Color(0x1a, 0xbc, 0x9c, 0x33);
        GridColor = sf::Color(0x1a, 0xbc, 0x9c, 0x26);
        break;
    case 2:
        AlphaColor = sf::Color(0x27, 0xae, 0x60);
        BetaColor = sf::Color(0x2e, 0xcc, 0x71);
        SelectionColor = sf::Color(0x2e, 0xcc, 0x71, 0x33);
        GridColor = sf::Color(0x2e, 0xcc, 0x71, 0x26);
        break;
    case 3:
        AlphaColor = sf::Color(0x8e, 0x44, 0xad);
        BetaColor = sf::Color(0x9b, 0x59, 0xb6);
        SelectionColor = sf::Color(0x9b, 0x59, 0xb6, 0x33);
        GridColor = sf::Color(0x9b, 0x59, 0xb6, 0x26);
        break;
    case 4:
        AlphaColor = sf::Color(0xf3, 0x9c, 0x12);
        BetaColor = sf::Color(0xf1, 0xc4, 0x0f);
        SelectionColor = sf::Color(0xf1, 0xc4, 0x0f, 0x33);
        GridColor = sf::Color(0xf1, 0xc4, 0x0f, 0x26);
        break;
    default:
        break;
    }
}

void Interface::ZoomIn()
{
    if(Zoom < 5)
    {
        std::pair<int,int> Center = MainInput->GetMousePosition();
        Offset.first = std::max(0, int(Offset.first + (Center.first-ToolBarWidth-BorderSize+Offset.first)/double(Zoom) + 0.5));
        Offset.second = std::max(0, int(Offset.second + (Center.second+Offset.second)/double(Zoom) + 0.5));
        Zoom++;
        GridSize = GridSize/(Zoom-1)*Zoom;
        PinRadius = PinRadius/(Zoom-1)*Zoom;
    }
}

void Interface::ZoomOut()
{
    if(Zoom > 2)
    {
        std::pair<int,int> Center = std::pair<int,int> (SimCanvas->GetGraphicsInfo().GetX()+SimCanvas->GetGraphicsInfo().GetWidth()/2.0+0.5, SimCanvas->GetGraphicsInfo().GetY()+SimCanvas->GetGraphicsInfo().GetHeight()/2.0+0.5);
        Offset.first = std::max(0, int(Offset.first - (Center.first-ToolBarWidth-BorderSize+Offset.first)/double(Zoom) + 0.5));
        Offset.second = std::max(0, int(Offset.second - (Center.second+Offset.second)/double(Zoom) + 0.5));
        Zoom--;
        GridSize = GridSize/(Zoom+1)*Zoom;
        PinRadius = PinRadius/(Zoom+1)*Zoom;
    }
}

void Interface::ShiftOffsetBy(std::pair<int,int> Delta)
{
    Offset.first = std::max(0, Offset.first+Delta.first);
    Offset.second = std::max(0, Offset.second+Delta.second);
}

void Interface::ClearCanvas()
{
    SimCanvas->Draw(MainOutput);
}

void Interface::ResetWindow()
{
    MainOutput->DrawBorders();
    MainOutput->UpdateActiveBar();
    StatusBar->Draw(MainOutput);
}

void Interface::SyncWindow()
{
    MainOutput->HandleMouse();
    MainOutput->SyncWindow();
}

void Interface::DrawComponent(const GraphicsInfo& GfxInfo, std::string ImagePath, Component::Status r_Status)
{
    MainOutput->DrawComponent(BufferGfxInfo(GfxInfo), std::string("")+ char(Zoom + '0') +"/"+ImagePath,r_Status);
}

void Interface::DrawLabel(const GraphicsInfo& GfxInfo, std::string Text)
{
    MainOutput->DrawLabel(BufferGfxInfo(GfxInfo), Text);
}

void Interface::DrawPin(std::pair<int,int> Center, bool Connected)
{
    MainOutput->DrawPin(BufferPoint(Center), Connected, std::string("Components/")+char(Zoom + '0')+std::string("/PIN/"));
}

void Interface::DrawConnection(const std::vector< std::pair<int,int> >& Vertices, bool Selected)
{
    std::vector< std::pair<int,int> > BufferedVertices;
    for(unsigned int i = 0; i < Vertices.size(); i++)
        BufferedVertices.push_back(BufferPoint(Vertices[i]));
    MainOutput->DrawConnection(BufferedVertices, Selected);
}

void Interface::PrintMsg(std::string Text)
{
    StatusBar->Draw(MainOutput);
    MainOutput->PrintMsg(Text);
}

void Interface::SetTooltipText(std::string Text)
{
    MainOutput->SetTooltipText(Text);
}

std::pair<int,int> Interface::GetMousePosition(bool Absolute) const
{
    if(Absolute)
        return MainInput->GetMousePosition();
    return ReverseBufferPoint(MainInput->GetMousePosition());
}

std::pair<int,int> Interface::GetPointClicked(bool Absolute) const
{
    if(Absolute)
        return MainInput->GetPointClicked();
    return ReverseBufferPoint(MainInput->GetPointClicked());
}

std::pair<int,int> Interface::GetInstantClick(bool Absolute) const
{
    std::pair<int,int> dummy = MainInput->GetInstantClick();
    if(Absolute || (dummy.first == -1 && dummy.second == -1))
        return dummy;
    return ReverseBufferPoint(dummy);
}

std::pair<int,int> Interface::GetInstantRelease(bool Absolute) const
{
    std::pair<int,int> dummy = MainInput->GetInstantRelease();
    if(Absolute || (dummy.first == -1 && dummy.second == -1))
        return dummy;
    return ReverseBufferPoint(dummy);
}

std::string Interface::GetSrting() const
{
    return MainInput->GetSrting();
}

Action::ActionType Interface::GetUserAction() const
{
    return MainInput->GetUserAction();
}

bool Interface::IsDragging() const
{
    return MainInput->IsDragging();
}

Bar* Interface::GetActiveBar()
{
    return (AppMode==DESIGN) ? DesignBar : SimulationBar;
}


std::pair<int,int> Interface::BufferPoint(std::pair<int,int> Point) const
{
    return std::pair<int,int> (ToolBarWidth+BorderSize+Point.first*Zoom*5-Offset.first, Point.second*Zoom*5-Offset.second);
}

std::pair<int,int> Interface::ReverseBufferPoint(std::pair<int,int> Point) const
{
    return std::pair<int,int> (double(Point.first-ToolBarWidth-BorderSize+Offset.first)/Zoom/5+0.5, double(Point.second+Offset.second)/Zoom/5+0.5);
}

GraphicsInfo Interface::BufferGfxInfo(GraphicsInfo GfxInfo) const
{
    return GraphicsInfo(BufferPoint(std::pair<int,int>(GfxInfo.GetX(), GfxInfo.GetY())), std::pair<int,int>(GfxInfo.GetWidth()*Zoom*5, GfxInfo.GetHeight()*Zoom*5));
}
