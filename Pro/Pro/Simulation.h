#pragma once

#include<vector>
#include<numeric>
#include <sstream>

class Component;
class LED;
class SWITCH;
class Pin;

class Simulation
{
public:
	Simulation();
	~Simulation();
	static bool IsValidToSimulate(std::vector<Component*> ComponentList);
	static void Simulate(std::vector<Component*> ComponentList);
	static void ClearStatus(std::vector<Component*> ComponentList);
	//static void TruthTable(std::vector<Component*> ComponentList);
	static void Simulation::CreatePossibilites(int NumberOfSwitches, std::vector<Component*> ComponentList, std::string Possibilities = "");
	static std::vector<Pin::Status> StringToStatus(std::string s);
	static std::vector<SWITCH*> GetSWITCHList();
	static std::vector<LED*> GetLEDList();
	static void SetSWITCHStatus(std::vector<SWITCH*> &v ,std::vector<Pin::Status>Values);
	static std::vector<Pin::Status> GetLEDStatus(std::vector<LED*> v);
	static std::vector<int>StatusToNumber(std::vector<Pin::Status> v);
	static std::vector<std::vector<int> >TruthTableData;
	static std::vector<std::string>AllCompinations;
	static void TruthTable(std::vector<Component*> ComponentList);
};

