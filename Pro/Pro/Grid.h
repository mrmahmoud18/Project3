#pragma once

#include<vector>
#include<queue>
#include<algorithm>

class Component;
class Pin;
class InputPin;
class SWITCH;
class LED;
class Gate;
class Connection;

class Grid
{
public:
    Grid(int r_X, int r_Y);
    std::vector< std::pair<int,int> > FindPath(std::pair<int,int> Point1, std::pair<int,int> Point2);
    bool IsValidCenter(std::pair<int,int> Center);
	void AddSwitch(SWITCH * r_pSWITCH);
	void AddLed(LED * r_pLED);
	void AddGate(Gate * r_pGate);
	void AddConnection(Connection * r_pConnection);
	void RemoveSWITCH(SWITCH * r_pSWITCH);
	void RemoveLED(LED * r_pLED);
	void RemoveGate(Gate *r_pGate);
    void RemoveConnection(Connection * r_pConnection);
	Component* GetComponent(std::pair<int, int> r_Point);
	Pin* GetPin(std::pair<int, int> r_Point);

private:
	int Xsize, Ysize;
    struct Node
    {
        int m_X, m_Y , m_XParent ,m_Yparent;
        enum {NOCONNECTION, CONNECTIONFULL, VERTICAL ,HORIZONTAL ,GATE ,PINPOINT ,NOTHING} m_Stat;
		Component* pComp;
		Pin* pPin;
    };
    std::vector< std::vector<Node> > Nodes;

	std::vector< std::pair<int, int> > CreateThePath(std::pair<int, int> Point1, std::pair<int, int> Point2);
	bool IsValidPoint(int r_TempX, int r_TempY, bool**r_Visited);
	bool ISValidState(int r_Tempx, int r_TempY, std::queue< Grid::Node>r_TempQueue);
	void ClearQueue(std::queue < Grid::Node >& r_TempQueue);
	void ClearParent();
	void GridInitializion();
};

/*

-------------
-CCCCCCCCCCC-
-CCCCCCCCCCC-
-CCCCCCCCCCC-
-CCGGGGGGGCC-
-C*GGGGGGGCC-
-C*GGGGGGG*C-
-C*GGGGGGGCC-
-CCGGGGGGGCC-
-CCCCCCCCCCC-
-CCCCCCCCCCC-
-CCCCCCCCCCC-
-------------

*/
