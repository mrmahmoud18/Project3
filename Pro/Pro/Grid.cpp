#include "Grid.h"
#include"Components/LED.h"
#include "Components/Gate.h"
#include "Components/SWITCH.h"
#include "Components\Connection.h"

Grid::Grid(int r_x, int r_y) {
	Xsize = r_x;
	Ysize = r_y;
	Nodes.resize(Xsize, std::vector<Node>(Ysize));
	GridInitializion();
}

std::vector< std::pair<int, int> > Grid::FindPath(std::pair<int, int> Point1, std::pair<int, int> Point2)
{
	std::queue<Node> TempQueue;
	//std::vector< std::vector<bool> >Visited(Xsize, std::vector <bool>(Ysize, false));
	bool **Visited = new bool* [Xsize];
	for (int i = 0; i < Xsize; i++)
	{
		Visited[i] = new bool[Ysize];
	}
	for (int i = 0; i < Xsize; i++)
	{
		for (int j = 0; j < Ysize; j++)
		{
			Visited[i][j] = false;
		}
	}

	bool PathFounded = false;
	int TempArrayX[4] = { 0,0,1,-1 }, TempArrayY[4] = { 1,-1,0,0 };
	int Tempy, Tempx, CurrentX, CurrentY;
	TempQueue.push(Nodes[Point1.first][Point1.second]);
	Visited[Point1.first][Point1.second] = true;
	while (!TempQueue.empty() && !PathFounded)
	{
		CurrentX = TempQueue.front().m_X;
		CurrentY = TempQueue.front().m_Y;
		for (int z = 0; z < 4; z++)
		{
			Tempx = TempArrayX[z] + CurrentX;
			Tempy = TempArrayY[z] + CurrentY;
			if (IsValidPoint(Tempx, Tempy, Visited))
			{
                if (Tempx == Point2.first && Tempy == Point2.second)
                {
                    PathFounded = true;
                    Nodes[Tempx][Tempy].m_XParent = CurrentX;
                    Nodes[Tempx][Tempy].m_Yparent = CurrentY;
                    ClearQueue(TempQueue);
                    break;
                }
				if (ISValidState(Tempx, Tempy, TempQueue))
				{
					Nodes[Tempx][Tempy].m_XParent = CurrentX;
					Nodes[Tempx][Tempy].m_Yparent = CurrentY;
					Visited[Tempx][Tempy] = true;
					TempQueue.push(Nodes[Tempx][Tempy]);
				}
			}
		}
		if (!TempQueue.empty())
		{
			TempQueue.pop();
		}
	}
	if(!PathFounded)
        throw;
    return CreateThePath(Point1, Point2);
}

std::vector< std::pair<int, int> > Grid::CreateThePath(std::pair<int, int> Point1, std::pair<int, int> Point2)
{
	std::vector< std::pair<int, int> >Path;
	Path.push_back(std::make_pair(Point2.first, Point2.second));
	int CurrentX = Point2.first, CurrentY = Point2.second, Tempy, Tempx;
	Tempx = CurrentX;
	Tempy = CurrentY;
	CurrentX = Nodes[Tempx][Tempy].m_XParent;
	CurrentY = Nodes[Tempx][Tempy].m_Yparent;
	do
	{
		while ((Tempx != Point1.first || Tempy != Point1.second) && Tempx == CurrentX)
		{
			Tempx = CurrentX;
			Tempy = CurrentY;
			CurrentX = Nodes[Tempx][Tempy].m_XParent;
			CurrentY = Nodes[Tempx][Tempy].m_Yparent;
			if (Tempx != CurrentX)
			{
				Path.push_back(std::make_pair(Tempx, Tempy));
			}
		}
		while ((Tempx != Point1.first || Tempy != Point1.second) && Tempx != CurrentX)
		{
			Tempx = CurrentX;
			Tempy = CurrentY;
			CurrentX = Nodes[Tempx][Tempy].m_XParent;
			CurrentY = Nodes[Tempx][Tempy].m_Yparent;
			if (Tempx == CurrentX)
			{
				Path.push_back(std::make_pair(Tempx, Tempy));
			}
		}

	} while (Tempx != Point1.first || Tempy != Point1.second);
	if (!(Point1.first == Path.back().first && Point1.second == Path.back().second))
	{
		Path.push_back(std::make_pair(Point1.first, Point1.second));
	}
	ClearParent();
	return Path;
}

bool Grid::IsValidPoint(int r_Tempx, int r_Tempy, bool**r_Visited /*std::vector< std::vector<bool> > &r_Visited*/)
{
	return (r_Tempx < Xsize && r_Tempx>0 && r_Tempy < Ysize  && r_Tempy>0 && !r_Visited[r_Tempx][r_Tempy]
		&& Nodes[r_Tempx][r_Tempy].m_Stat != Grid::Node::GATE && Nodes[r_Tempx][r_Tempy].m_Stat != Grid::Node::CONNECTIONFULL);
}

bool Grid::ISValidState(int r_Tempx, int r_Tempy, std::queue<Grid::Node> r_TempQueue)
{
	return ((r_Tempy == r_TempQueue.front().m_Y && Nodes[r_Tempx][r_Tempy].m_Stat != Grid::Node::HORIZONTAL)
		|| (r_Tempx == r_TempQueue.front().m_X && Nodes[r_Tempx][r_Tempy].m_Stat != Grid::Node::VERTICAL));
}

void Grid::ClearQueue(std::queue<Grid::Node>& r_TempQueue)
{
	while (!r_TempQueue.empty())
	{
		r_TempQueue.pop();
	}
}

void Grid::ClearParent()
{
	for (int i = 0; i < Xsize; i++)
	{
		for (int j = 0; j < Ysize; j++)
		{
			Nodes[i][j].m_XParent = 0;
			Nodes[i][j].m_Yparent = 0;
		}
	}
}

void Grid::GridInitializion() {
	for (int i = 0; i < Xsize; i++)
	{
		for (int j = 0; j < Ysize; j++)
		{
			Nodes[i][j].m_Stat = Node::NOTHING;
			Nodes[i][j].m_X = i;
			Nodes[i][j].m_Y = j;
			Nodes[i][j].pComp = NULL;
			Nodes[i][j].pPin = NULL;
		}
	}
}

bool Grid::IsValidCenter(std::pair<int, int> r_componentCenter)
{
    if(-6+r_componentCenter.first <0 || -6+r_componentCenter.second <0 || 6+r_componentCenter.first > Xsize || 6+r_componentCenter.second >Ysize)
    {
        return false;
    }
	for (int i = -6; i <= 6; i++)
	{
		for (int j = -6; j <= 6; j++)
		{
			if (Nodes[i + r_componentCenter.first][j + r_componentCenter.second].m_Stat != Node::NOTHING)
			{
				return false;
			}
		}
	}
	return true;
}

void Grid::AddSwitch(SWITCH * r_pSWITCH)
{
	std::pair<int, int>Center = std::make_pair(r_pSWITCH->GetGraphicsInfo().GetX(), r_pSWITCH->GetGraphicsInfo().GetY());
	for (int i = -3; i <= 3; i++)
	{
		for (int j = -2; j <= 2; j++)
		{
			Nodes[i + Center.first][j + Center.second].m_Stat = Node::GATE;
			Nodes[i + Center.first][j + Center.second].pComp = r_pSWITCH;
		}
	}
	Nodes[Center.first + 4][Center.second].m_Stat = Node::PINPOINT;
	Nodes[Center.first + 4][Center.second].pPin = r_pSWITCH ->GetOutputPin();
	for (int i = -6; i <= 6; i++)
	{
		for (int j = -6; j <= 6; j++)
		{
			if (Nodes[i + Center.first][j + Center.second].m_Stat == Node::NOTHING)
			{
				Nodes[i + Center.first][j + Center.second].m_Stat = Node::NOCONNECTION;
			}
		}
	}
}

void Grid::AddLed(LED * r_pLED)
{
	std::pair<int, int>Center = std::make_pair(r_pLED->GetGraphicsInfo().GetX(), r_pLED->GetGraphicsInfo().GetY());
	for (int i = -3; i <= 3; i++)
	{
		for (int j = -2; j <= 2; j++)
		{
			Nodes[i + Center.first][j + Center.second].m_Stat = Node::GATE;
			Nodes[i + Center.first][j + Center.second].pComp = r_pLED;
		}
	}
	Nodes[Center.first - 4][Center.second].m_Stat = Node::PINPOINT;
	Nodes[Center.first - 4][Center.second].pPin = r_pLED->GetInputPin();
	for (int i = -6; i <= 6; i++)
	{
		for (int j = -6; j <= 6; j++)
		{
			if (Nodes[i + Center.first][j + Center.second].m_Stat == Node::NOTHING)
			{
				Nodes[i + Center.first][j + Center.second].m_Stat = Node::NOCONNECTION;
			}
		}
	}
}

void Grid::AddGate(Gate * r_pGate)
{
	std::pair<int, int>Center = std::make_pair(r_pGate->GetGraphicsInfo().GetX(), r_pGate->GetGraphicsInfo().GetY());
	for (int i = -3; i <= 3; i++)
	{
		for (int j = -2; j <= 2; j++)
		{
			Nodes[i + Center.first][j + Center.second].m_Stat = Node::GATE;
			Nodes[i + Center.first][j + Center.second].pComp = r_pGate;
		}
	}

	Nodes[Center.first + 4][Center.second].m_Stat = Node::PINPOINT;
	Nodes[Center.first - 4][Center.second].m_Stat = Node::PINPOINT;
	Nodes[Center.first - 4][Center.second + 1].m_Stat = Node::PINPOINT;
	Nodes[Center.first - 4][Center.second - 1].m_Stat = Node::PINPOINT;

	Nodes[Center.first + 4][Center.second].pPin = r_pGate->GetOutputPin();
	Nodes[Center.first + 4][Center.second].pComp = r_pGate;
	std::vector<InputPin>& temp = dynamic_cast<Gate*>(r_pGate)->GetInputPins();
	std::vector<InputPin>::iterator min = temp.begin();
	std::vector<InputPin>::iterator it = temp.begin();
	for (unsigned int i = 1; i < temp.size(); i++)
	{
		while (it != temp.end())
		{
			if (min->GetCenter().first > it->GetCenter().first)
			{
				min = it;
			}
			it++;
		}
		std::swap(min, temp.begin()+i);
		min = it = temp.begin() + i;
	}

	if (temp.size() == 2)
	{
		Nodes[Center.first - 4][Center.second - 1].pPin = &(temp[0]);
		Nodes[Center.first - 4][Center.second - 1].pComp = r_pGate;
		Nodes[Center.first - 4][Center.second + 1].pPin = &(temp[1]);
		Nodes[Center.first - 4][Center.second + 1].pComp = r_pGate;
	}
	else
	{
		Nodes[Center.first - 4][Center.second - 1].pPin = &(temp[0]);
		Nodes[Center.first - 4][Center.second - 1].pComp = r_pGate;
		Nodes[Center.first - 4][Center.second].pPin = &(temp[1]);
		Nodes[Center.first - 4][Center.second].pComp = r_pGate;
		Nodes[Center.first - 4][Center.second + 1].pPin = &(temp[2]);
		Nodes[Center.first - 4][Center.second + 1].pComp = r_pGate;
	}
	for (int i = -6; i <= 6; i++)
	{
		for (int j = -6; j <= 6; j++)
		{
			if (Nodes[i + Center.first][j + Center.second].m_Stat == Node::NOTHING)
			{
				Nodes[i + Center.first][j + Center.second].m_Stat = Node::NOCONNECTION;
			}
		}
	}
}

void Grid::AddConnection(Connection * r_pConnection)
{
	std::vector< std::pair<int, int> >Path = r_pConnection->GetPath();
	int TempY, TempX, Count = 1;
	TempX = Path.front().first;
	TempY = Path.front().second;
	do
	{
		while ((TempX != Path.back().first || TempY != Path.back().second) && TempX == Path[Count].first)
		{
			if (Nodes[TempX][TempY].m_Stat == Grid::Node::NOTHING || Nodes[TempX][TempY].m_Stat == Grid::Node::NOCONNECTION)
			{
				Nodes[TempX][TempY].m_Stat = Grid::Node::VERTICAL;
			}
			if (Nodes[TempX][TempY].m_Stat == Grid::Node::HORIZONTAL)
			{
				Nodes[TempX][TempY].m_Stat = Grid::Node::CONNECTIONFULL;
			}
			if (Nodes[TempX][TempY].pComp == NULL)
			{
				Nodes[TempX][TempY].pComp = r_pConnection;
			}
			else
			{
				Nodes[TempX][TempY].pComp = NULL;
			}

			TempY++;
			if (TempY == Path[Count].second)
			{
				Count++;
			}
		}
		while ((TempX != Path.back().first || TempY != Path.back().second) && TempX != Path[Count].second)
		{
			if (Nodes[TempX][TempY].m_Stat == Grid::Node::NOTHING || Nodes[TempX][TempY].m_Stat == Grid::Node::NOCONNECTION)
			{
				Nodes[TempX][TempY].m_Stat = Grid::Node::HORIZONTAL;
			}
			if (Nodes[TempX][TempY].m_Stat == Grid::Node::VERTICAL)
			{
				Nodes[TempX][TempY].m_Stat = Grid::Node::CONNECTIONFULL;
			}
			if (Nodes[TempX][TempY].pComp == NULL)
			{
				Nodes[TempX][TempY].pComp = r_pConnection;
			}
			else
			{
				Nodes[TempX][TempY].pComp = NULL;
			}
			TempX++;
			if (TempX == Path[Count].first)
			{
				Count++;
			}
		}

	} while (TempX != Path.back().first || TempY != Path.back().second);
}

void Grid::RemoveSWITCH(SWITCH * r_pSWITCH)
{
	std::pair<int, int> Center = std::make_pair(r_pSWITCH->GetGraphicsInfo().GetX(), r_pSWITCH->GetGraphicsInfo().GetY());
	if (r_pSWITCH->GetOutputPin() != Nodes[Center.first + 4][Center.second].pPin)
	{
		throw;
	}
	for (int i = -6; i <= 6; i++)
	{
		for (int j = -6; j <= 6; j++)
		{
			if (Nodes[i + Center.second][j + Center.first].m_Stat == Node::GATE || Nodes[i + Center.second][j + Center.first].m_Stat == Node::NOCONNECTION || Nodes[i + Center.second][j + Center.first].m_Stat == Node::PINPOINT)
			{
				Nodes[i + Center.second][j + Center.first].m_Stat = Node::NOTHING;
				Nodes[i + Center.second][j + Center.first].pComp = NULL;
				Nodes[i + Center.second][j + Center.first].pPin = NULL;
			}
		}
	}
}

void Grid::RemoveLED(LED * r_pLED)
{
	std::pair<int, int>Center = std::make_pair(r_pLED->GetGraphicsInfo().GetX(), r_pLED->GetGraphicsInfo().GetY());
	if (r_pLED->GetInputPin() != Nodes[Center.first][Center.second].pPin)
	{
		throw;
	}
	for (int i = -6; i <= 6; i++)
	{
		for (int j = -6; j <= 6; j++)
		{
			if (Nodes[i + Center.second][j + Center.first].m_Stat == Node::GATE || Nodes[i + Center.second][j + Center.first].m_Stat == Node::NOCONNECTION || Nodes[i + Center.second][j + Center.first].m_Stat == Node::PINPOINT)
			{
				Nodes[i + Center.second][j + Center.first].m_Stat = Node::NOTHING;
				Nodes[i + Center.second][j + Center.first].pComp = NULL;
				Nodes[i + Center.second][j + Center.first].pPin = NULL;
			}
		}
	}
}

void Grid::RemoveGate(Gate * r_pGate)
{
	std::pair<int, int>Center = std::make_pair(r_pGate->GetGraphicsInfo().GetX(), r_pGate->GetGraphicsInfo().GetY());
	std::vector<InputPin>& temp = r_pGate->GetInputPins();
	if (r_pGate->GetOutputPin() != Nodes[Center.first][Center.second].pPin)
	{
		throw;
	}

	if (temp.size() == 2)
	{
		if (Nodes[Center.first - 4][Center.second - 1].pPin != &(temp[0]) || Nodes[Center.first - 4][Center.second + 1].pPin != &(temp[1]))
		{
			throw;
		}
	}
	else
	{
		if (Nodes[Center.first - 4][Center.second - 1].pPin != &(temp[0]) || Nodes[Center.first - 4][Center.second].pPin != &(temp[1]) || Nodes[Center.first - 4][Center.second + 1].pPin != &(temp[2]))
		{
			throw;
		}
	}

	for (int i = -6; i <= 6; i++)
	{
		for (int j = -6; j <= 6; j++)
		{
			if (Nodes[i + Center.second][j + Center.first].m_Stat == Node::GATE || Nodes[i + Center.second][j + Center.first].m_Stat == Node::NOCONNECTION || Nodes[i + Center.second][j + Center.first].m_Stat == Node::PINPOINT)
			{
				Nodes[i + Center.second][j + Center.first].m_Stat = Node::NOTHING;
				Nodes[i + Center.second][j + Center.first].pComp = NULL;
				Nodes[i + Center.second][j + Center.first].pPin = NULL;
			}
		}
	}
}


void Grid::RemoveConnection(Connection * r_pConnection)
{
	std::vector<std::pair<int, int> >Path = r_pConnection->GetPath();
	if (Nodes[Path.front().first][Path.front().second].pPin != r_pConnection->GetInputPin() || Nodes[Path.back().first][Path.back().second].pPin != r_pConnection->GetOutPin())
	{
		throw;
	}
	int TempY, TempX, Count = 1;
	TempX = Path.front().first;
	TempY = Path.front().second;
	do
	{
		while ((TempX != Path.back().first || TempY != Path.back().second) && TempX == Path[Count].first)
		{
			if (Nodes[TempX][TempY].m_Stat == Grid::Node::CONNECTIONFULL )
			{
				Nodes[TempX][TempY].m_Stat = Grid::Node::HORIZONTAL;
			}
			if (Nodes[TempX][TempY].m_Stat == Grid::Node::VERTICAL)
			{
				Nodes[TempX][TempY].m_Stat = Grid::Node::NOCONNECTION;
			}
			if (Nodes[TempX][TempY].pComp !=NULL)
			{
				Nodes[TempX][TempY].pComp = NULL;
			}
			else
			{
				if (Nodes[TempX + 1][TempY].pComp == NULL || Nodes[TempX - 1][TempY].pComp == NULL)
				{
					Nodes[TempX][TempY].pComp = Nodes[TempX][TempY + 1].pComp;
				}
				else
				{
					Nodes[TempX][TempY].pComp = Nodes[TempX + 1][TempY].pComp;
				}
			}

			TempY++;
			if (TempY == Path[Count].second)
			{
				Count++;
			}
		}
		while ((TempX != Path.back().first || TempY != Path.back().second) && TempX != Path[Count].first)
		{
			if (Nodes[TempX][TempY].m_Stat == Grid::Node::CONNECTIONFULL )
			{
				Nodes[TempX][TempY].m_Stat = Grid::Node::VERTICAL;
			}
			if (Nodes[TempX][TempY].m_Stat == Grid::Node::HORIZONTAL)
			{
				Nodes[TempX][TempY].m_Stat = Grid::Node::NOCONNECTION;
			}
			if (Nodes[TempX][TempY].pComp != NULL)
			{
				Nodes[TempX][TempY].pComp = NULL;
			}
			else
			{
				if (Nodes[TempX + 1][TempY].pComp == NULL || Nodes[TempX - 1][TempY].pComp == NULL)
				{
					Nodes[TempX][TempY].pComp = Nodes[TempX][TempY + 1].pComp;
				}
				else
				{
					Nodes[TempX][TempY].pComp = Nodes[TempX + 1][TempY].pComp;
				}
			}
			TempX++;
			if (TempX == Path[Count].first)
			{
				Count++;
			}
		}

	} while (TempX != Path.back().first || TempY != Path.back().second);
}

Component * Grid::GetComponent(std::pair<int, int> r_Point)
{
	return Nodes[r_Point.first][r_Point.second].pComp;
}

Pin * Grid::GetPin(std::pair<int, int> r_Point)
{
	return Nodes[r_Point.first][r_Point.second].pPin;
}


