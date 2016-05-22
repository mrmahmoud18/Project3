#pragma once
#include "Action.h"

#include<string>

class LED;
class SWITCH;

class TruthTable :public Action
{
private:
	virtual void ReadActionParameters();
	void CreateAllCombinations(std::string s = "");
	void SetSWITCHValues(std::string Combination);
	void GetLEDResults();
	std::vector<SWITCH*>Switches;
	std::vector<LED*>Leds;
	std::vector<std::string>Combinations;
	std::vector<std::string>Lables;
	std::vector<std::string>Results;
public:
	TruthTable(ApplicationManager * pApp);
	~TruthTable();
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};

