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
		Switches[i]->GetOutputPin()->SetStatus((Combination[i] == '0') ? Signal::LOW : Signal::HIGH);
	}
}

void TruthTable::GetSWITCHesValues()
{
	OriginalSWITCHesData = "";
	for (unsigned int i = 0; i < Switches.size(); i++)
		OriginalSWITCHesData + ((Switches[i]->GetStatus() == Signal::HIGH) ? '1' : '0');
}

void TruthTable::GetLEDsResults()
{
	std::string temp = "";
	for (unsigned int i = 0; i < Leds.size(); i++)
		temp + ((Leds[i]->GetStatus() == Signal::HIGH) ? '1' : '0');

	Results.push_back(temp);
}

void TruthTable::CreateTable()
{
	Table.resize(Combinations.size()+1, std::vector<std::string>(Lables.size()));

	for (unsigned int i = 0; i < Lables.size(); i++)
		Table[0][i] = Lables[i];

	for (unsigned int k = 1; k < Combinations.size() + 1; k++)
	{
		for (unsigned int i = 0; i < Switches.size(); i++)
		{
			Table[k][i] = Combinations[k - 1][i];
		}
		for (unsigned int j = Switches.size(); j < Leds.size() + Switches.size(); j++)
		{
			Table[k][j] = Results[k - 1][j];
		}
	}
}

void TruthTable::PrintTruthTableInFile()
{
	std::ofstream Out;
	Out.open("Truth_Table");
	if (! Out.is_open())
		throw;

	for (unsigned int i = 0; i < Table.size(); i++)
	{
		for (unsigned int j = 0; j < Table[0].size(); j++)
		{
			Out << Table[i][j] << std::setw(5);
		}
		Out << std::endl;
	}
	Out.close();
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
	ReadActionParameters();
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
	SetSWITCHesValues(OriginalSWITCHesData);
	pManager->SimulateComponents();
	PrintTruthTableInFile();
}

void TruthTable::Undo()
{
}

void TruthTable::Redo()
{
}
