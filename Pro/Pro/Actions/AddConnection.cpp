#include "AddConnection.h"

#include "../ApplicationManager.h"
#include "InputPin.h"
#include "OutputPin.h"

AddConnection::AddConnection(ApplicationManager *pApp): Action(pApp) {}

void AddConnection::ReadActionParameters()
{
    /*
    m_InputPin = pManager->GetPinAt(pManager->GetInterface()->GetMousePosition());
    m_OutputPin = NULL;
    if(InputPin == NULL)
        throw;
    OutputPin* dummy = dynamic_cast<OutputPin*> (m_InputPin);
    if(dummy == NULL)
    {
        m_OutputPin = m_InputPin;
        m_InputPin = NULL;
    }
    */
}

void AddConnection::Execute()
{
    /*
    ReadActionParameters();
    std::pair<int,int> Point;
    do
	{
		Point = pManager->GetInterface()->GetInstantClick();
		pManager->UpdateInterface();
        pManager->SyncInterface();
	} while (Point.first == -1 && Point.second == -1);
	m_OutputPin = pManager->GetPinAt(Point);
	pManager->FindPathThroughGrid(m_InputPin, m_OutputPin);
	*/
}

void AddConnection::Undo() {}

void AddConnection::Redo() {}
