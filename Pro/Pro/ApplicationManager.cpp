#include "ApplicationManager.h"

#include "Components/Component.h"
#include "Components/AND2.h"
#include "Components/Connection.h"

#include "Actions/Add.h"
#include "Actions/AddComponent.h"
#include "Actions/AddConnection.h"
#include "Actions/Delete.h"
#include "Actions/Drag.h"
#include "Actions/Copy.h"
#include "Actions/Cut.h"
#include "Actions/Paste.h"
#include "Actions/HandleLeftClick.h"
#include "Actions/HandleActiveBar.h"
#include "Actions/AdjustOffset.h"
#include "Actions/ZoomIn.h"
#include "Actions/ZoomOut.h"

ApplicationManager::ApplicationManager(): SimGrid(360, 360)
{
/*
    Components.push_back(new AND2(GraphicsInfo(10,10,12,12)));
    SimGrid.AddComponent(std::pair<int,int>(16,16), Components[0]);
    Components.push_back(new AND2(GraphicsInfo(30,30,12,12)));
    SimGrid.AddComponent(std::pair<int,int>(36,36), Components[1]);
    std::vector< std::pair<int,int> > s = SimGrid.FindPath(std::pair<int,int>(20,16),std::pair<int,int>(32,35));
    std::vector< std::pair<int,int> > s;
    s.push_back(std::pair<int,int>(20,16));
    s.push_back(std::pair<int,int>(32,16));
    s.push_back(std::pair<int,int>(32,35));
    Components.push_back(new Connection(SimGrid.GetPin(std::pair<int,int>(20,16)), SimGrid.GetPin(std::pair<int,int>(32,35)), s));
*/
}

ApplicationManager::~ApplicationManager()
{
    for(unsigned int i = 0; i < Components.size(); i++)
        delete Components[i];
}

ActionType ApplicationManager::GetUserAction()
{
    return MainInterface.GetUserAction();
}

void ApplicationManager::ExecuteAction(ActionType Act)
{
    Action* dummyAction = NULL;
    switch (Act)
    {
    case ADD:
        dummyAction = new Add(this);
        break;
    case ADD_CONNECTION:
        dummyAction = new AddConnection(this);
        break;
	case ADD_LABEL:
        MainInterface.PrintMsg("Add Label");
        break;
	case EDIT_LABEL:
        MainInterface.PrintMsg("Edit Label");
        break;
	case CREATE_TRUTHTABLE:
        MainInterface.PrintMsg("Create TruthTable");
        break;
    case ACTIVE_BAR_CLICK:
        dummyAction = new HandleActiveBar(this);
        break;
	case CANVAS_LEFT_CLICK:
        dummyAction = new HandleLeftClick(this);
        break;
	case CANVAS_RIGHT_CLICK:
        break;
    case MULTI_SELECT:
        break;
	case DELETE:
        dummyAction = new Delete(this);
        break;
	case DRAG:
        dummyAction = new Drag(this);
        break;
	case COPY:
        dummyAction = new Copy(this);
        break;
    case CUT:
        dummyAction = new Cut(this);
        break;
	case PASTE:
        dummyAction = new Paste(this);
        break;
	case SAVE:
        MainInterface.PrintMsg("Save");
        break;
	case LOAD:
        MainInterface.PrintMsg("Load");
        break;
	case UNDO:
        MainInterface.PrintMsg("Undo");
        break;
	case REDO:
        MainInterface.PrintMsg("Redo");
        break;
	case SWITCH_MODE:
        MainInterface.SwitchAppMode();
        MainInterface.PrintMsg("Switching Mode");
        break;
	case SWITCH_THEME:
        MainInterface.SwitchAppTheme();
        MainInterface.PrintMsg("Switching Theme");
        break;
    case ADJUST_OFFSET:
        dummyAction = new AdjustOffset(this);
        break;
    case ZOOM_IN:
        dummyAction = new ZoomIn(this);
        break;
    case ZOOM_OUT:
        dummyAction = new ZoomOut(this);
        break;
	case EXIT:
        exit(0);
        break;
	case STATUS_BAR:
        break;
	case NONE:
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
    MainInterface.PrintMsg("Ready!");
}

void ApplicationManager::SyncInterface()
{
    MainInterface.SyncWindow();
}

Interface* ApplicationManager::GetInterface()
{
    return &MainInterface;
}

bool ApplicationManager::IsClipboardEmpty() const
{
    return Clipboard.size() == 0;
}

void ApplicationManager::PushIntoClipboard(Component* ToBeSaved)
{
    Clipboard.push_back(ToBeSaved);
}

const std::vector<Component*>& ApplicationManager::GetClipboard()
{
    return Clipboard;
}

void ApplicationManager::FlushClipboard()
{
    Clipboard.clear();
}

std::vector< std::pair<int,int> > ApplicationManager::FindPathThroughGrid(std::pair<int,int> Point1, std::pair<int,int> Point2)
{
    return SimGrid.FindPath(Point1, Point2);
}

bool ApplicationManager::IsValidCenter(std::pair<int,int> Center) const
{
    return SimGrid.IsValidCenter(Center);
}

Component* ApplicationManager::GetComponentAt(std::pair<int, int> Point)
{
    return SimGrid.GetComponentAt(Point);
}

Pin* ApplicationManager::GetPinAt(std::pair<int, int> Point)
{
    return SimGrid.GetPinAt(Point);
}

std::set<Component*> ApplicationManager::GetSelectedComponents()
{
    std::set<Component*> Selected;
    for(unsigned int i = 0; i < Components.size(); i++)
    {
        Selected.insert(Components[i]);
        std::set<Component*> AssociatedComponents = Components[i]->GetAssociatedComponents();
        Selected.insert(AssociatedComponents.begin(), AssociatedComponents.end());
    }
    return Selected;
}

void ApplicationManager::AddComponents(const std::vector<Component*>& ToBeAdded)
{
    for(unsigned int i = 0; i < ToBeAdded.size(); i++)
    {
        ToBeAdded[i]->GetIn(&SimGrid);
        Components.push_back(ToBeAdded[i]);
    }
}

void ApplicationManager::RemoveComponents(const std::vector<Component*>& ToBeRemoved)
{
    for(unsigned int i = 0; i < ToBeRemoved.size(); i++)
    {
        ToBeRemoved[i]->GetOut(&SimGrid);
        std::vector<Component*>::iterator dummyIt = std::find(Components.begin(), Components.end(), ToBeRemoved[i]);
        if(dummyIt == Components.end())
            throw;
        Components.erase(dummyIt);
    }
}
