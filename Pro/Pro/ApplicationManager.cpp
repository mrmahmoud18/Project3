#include "ApplicationManager.h"

#include "Components/Component.h"
#include "Components/AND2.h"
#include "Components/Connection.h"

#include "Actions/Add.h"
#include "Actions/AddComponent.h"
#include "Actions/Copy.h"
#include "Actions/Cut.h"
#include "Actions/HandleActiveBar.h"
#include "Actions/AdjustOffset.h"
#include "Actions/ZoomIn.h"
#include "Actions/ZoomOut.h"

ApplicationManager::ApplicationManager(): SimGrid(360, 360)
{
    Components.push_back(new AND2(GraphicsInfo(10,10,12,12)));
   // Components.push_back(new AND2(GraphicsInfo(30,30,12,12)));
   // SimGrid.AddComponent(std::pair<int,int>(36,36), Components[1]);
	//Pin* p = SimGrid.GetPin(std::pair<int, int>(20, 16));
	//p = SimGrid.GetPin(std::pair<int, int>(12, 17));
	//p = SimGrid.GetPin(std::pair<int, int>(12, 15));
    //Components.push_back(new Connection(SimGrid.GetPin(std::pair<int,int>(20,16)), SimGrid.GetPin(std::pair<int,int>(32,35)), SimGrid.FindPath(std::pair<int,int>(20,16),std::pair<int,int>(32,35))));
	std::vector< std::pair<int, int> >v = SimGrid.FindPath(std::make_pair(20, 16), std::make_pair(32, 35));

}


ApplicationManager::~ApplicationManager()
{
    for(unsigned int i = 0; i < Components.size(); i++)
        delete Components[i];
}

Action::ActionType ApplicationManager::GetUserAction()
{
    return MainInterface.GetUserAction();
}

void ApplicationManager::ExecuteAction(Action::ActionType Act)
{
    Action* dummyAction = NULL;
    switch (Act)
    {
    case Action::ADD:
        dummyAction = new Add(this);
        break;
    case Action::ADD_CONNECTION:
        MainInterface.PrintMsg("Add Connection");
        break;
	case Action::ADD_LABEL:
        MainInterface.PrintMsg("Add Label");
        break;
	case Action::EDIT_LABEL:
        MainInterface.PrintMsg("Edit Label");
        break;
	case Action::CREATE_TRUTHTABLE:
        MainInterface.PrintMsg("Create TruthTable");
        break;
    case Action::ACTIVE_BAR_CLICK:
        dummyAction = new HandleActiveBar(this);
        break;
	case Action::CANVAS_LEFT_CLICK:
        {
            std::vector<Action::ActionType> dummy;
            dummy.push_back(Action::COPY);
            dummy.push_back(Action::DELETE);
            MainInterface.EnableActions(dummy);
        }
        MainInterface.PrintMsg("Change Switch");
        break;
	case Action::CANVAS_RIGHT_CLICK:
        {
            std::vector<Action::ActionType> dummy;
            dummy.push_back(Action::COPY);
            dummy.push_back(Action::SWITCH_MODE);
            MainInterface.DisableActions(dummy);
        }
        break;
	case Action::DELETE:
        MainInterface.PrintMsg("Delete");
        break;
	case Action::MOVE:
        MainInterface.PrintMsg("Move");
        break;
	case Action::COPY:
        dummyAction = new Copy(this);
        break;
    case Action::CUT:
        dummyAction = new Cut(this);
        break;
	case Action::PASTE:
        MainInterface.PrintMsg("Paste");
        break;
	case Action::SAVE:
        MainInterface.PrintMsg("Save");
        break;
	case Action::LOAD:
        MainInterface.PrintMsg("Load");
        break;
	case Action::UNDO:
        MainInterface.PrintMsg("Undo");
        break;
	case Action::REDO:
        MainInterface.PrintMsg("Redo");
        break;
	case Action::SWITCH_MODE:
        MainInterface.SwitchAppMode();
        MainInterface.PrintMsg("Switching Mode");
        break;
	case Action::SWITCH_THEME:
        MainInterface.SwitchAppTheme();
        MainInterface.PrintMsg("Switching Theme");
        break;
    case Action::ADJUST_OFFSET:
        dummyAction = new AdjustOffset(this);
        break;
    case Action::ZOOM_IN:
        dummyAction = new ZoomIn(this);
        break;
    case Action::ZOOM_OUT:
        dummyAction = new ZoomOut(this);
        break;
	case Action::EXIT:
        exit(0);
        break;
	case Action::STATUS_BAR:
        MainInterface.PrintMsg("Status Bar");
        break;
	case Action::NONE:
        break;
    default:
        dummyAction = new AddComponent(this, Act);
    }
    if(dummyAction != NULL)
    {
        dummyAction->Execute();
        delete dummyAction;
    }
}

void ApplicationManager::UpdateInterface()
{
    MainInterface.SetTooltipText("");
    MainInterface.ClearCanvas();
    for(unsigned int i = 0; i < Components.size(); i++)
        Components[i]->Draw(&MainInterface);
    MainInterface.ResetWindow();
}

void ApplicationManager::SyncInterface()
{
    MainInterface.SyncWindow();
}

Grid* ApplicationManager::GetGrid()
{
    return &SimGrid;
}

Clipboard* ApplicationManager::GetClipboard()
{
    return &MainClipboard;
}

Interface* ApplicationManager::GetInterface()
{
    return &MainInterface;
}

std::vector<Component*>& ApplicationManager::GetComponents()
{
    return Components;
}
