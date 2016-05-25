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
		SetSWITCHesValues(s);
		Combinations.push_back(s);
		pManager->SimulateComponents();
		GetLEDsResults();
		return;
	}
	CreateAllCombinations(s + "0");
	CreateAllCombinations(s + "1");
}

void TruthTable::SetSWITCHesValues(std::string Combination)
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

void TruthTable::GetSWITCHesValues()
{
	for (unsigned int i = 0; i < Switches.size(); i++)
	{
		OriginalSwitchData.push_back((Switches[i]->GetStatus() == Signal::HIGH) ? "1" : "0");
	}
}

void TruthTable::GetLEDsResults()
{
	std::string temp = "";
	for (unsigned int i = 0; i < Leds.size(); i++)
	{
		if (Leds[i]->GetInputPin()->GetStatus() == LOW)
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
	GetSWITCHesValues();
	CreateAllCombinations();
}

void TruthTable::Undo()
{
}

void TruthTable::Redo()
{
}
