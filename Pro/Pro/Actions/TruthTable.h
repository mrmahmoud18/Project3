#pragma once
#include "Action.h"

#include <fstream>
#include <iomanip>
#include<string>
#include<vector>

class LED;
class SWITCH;

class TruthTable :public Action
{
private:
	virtual void ReadActionParameters();
	void CreateAllCombinations(std::string s = "");
	void SetSWITCHesValues(std::string Combination);
	void GetSWITCHesValues();
	void GetLEDsResults();
	void CreateTable();
	void PrintTruthTableInFile();
	std::vector<SWITCH*>Switches;
	std::vector<LED*>Leds;
	std::vector<std::string>Combinations;
	std::vector<std::string>Lables;
	std::vector<std::string>Results;
	std::vector<std::vector<std::string> >Table;
	std::string OriginalSWITCHesData;
public:
	TruthTable(ApplicationManager * pApp);
	~TruthTable();
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};

