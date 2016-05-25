#include "TruthTable.h"
#include "../ApplicationManager.h"
#include "TruthTable.h"
#include "../Components/SWITCH.h"
#include "../Components/LED.h"


void TruthTable::ReadActionParameters()
{
	Switches = pManager->GetSWITCHs();
	Leds = pManager->GetLEDs();
}

void TruthTable::CreateAllCombinations(std::string s)
{
	if (s.length() == Switches.size())
	{
		SetSWITCHValues(s);
		Combinations.push_back(s);
		pManager->SimulateComponents();
		GetLEDResults();
		return;
	}
	CreateAllCombinations(s + "0");
	CreateAllCombinations(s + "1");
}

void TruthTable::SetSWITCHValues(std::string Combination)
{
	for (unsigned int i = 0; i < Switches.size(); i++)
	{
		if (Combination[i]=='0')
		{
			Switches[i]->GetOutputPin()->SetStatus(LOW);
		}
		else
		{
			Switches[i]->GetOutputPin()->SetStatus(HIGH);
		}
	}
}

void TruthTable::GetLEDResults()
{
	std::string temp = "";
	for (unsigned int i = 0; i < Leds.size(); i++)
	{
		if (Leds[i]->GetInputPin()->GetStatus() == Pin::LOW)
		{
			temp += "0";
		}
		else
		{
			temp += "1";
		}
	}
	Results.push_back(temp);
}

void TruthTable::CreateTable()
{
}


TruthTable::TruthTable(ApplicationManager * pApp)
	:Action(pApp)
{
}

TruthTable::~TruthTable()
{
}

void TruthTable::Execute()
{
	for (unsigned int i = 0; i < Switches.size(); i++)
	{
		//Lables.push_back( Switches[i]->)
		// TODO GET the lables
	}
	for (unsigned int i = 0; i < Leds.size(); i++)
	{
		//TODO get the lables of the leds
	}
	CreateAllCombinations();
}

void TruthTable::Undo()
{
}

void TruthTable::Redo()
{
}
