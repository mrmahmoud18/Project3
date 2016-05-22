#include "Grid.h"

Grid::Grid(int r_X, int r_Y)
{
    Xsize = r_X;
    Ysize = r_Y;
}

std::vector< std::pair<int,int> > Grid::FindPath(std::pair<int,int> Point1, std::pair<int,int> Point2)
{
    ///TODO
    return std::vector< std::pair<int,int> >(0);
}

bool Grid::IsValidCenter(std::pair<int,int> Center) const
{
    ///TODO
    return true;
}

void Grid::AddGate(Gate* pGate)
{
    ///TODO
}

void Grid::AddSWITCH(SWITCH* pSWITCH)
{
    ///TODO
}

void Grid::AddLED(LED* pLED)
{
    ///TODO
}

void Grid::AddConnection(Connection* pConnection)
{
    ///TODO
}

void Grid::RemoveGate(Gate* pGate)
{
    ///TODO
}

void Grid::RemoveSWITCH(SWITCH* pSWITCH)
{
    ///TODO
}

void Grid::RemoveLED(LED* pLED)
{
    ///TODO
}

void Grid::RemoveConnection(Connection* pConnection)
{
    ///TODO
}

Component* Grid::GetComponentAt(std::pair<int, int> Point)
{
    ///TODO
    return 0;
}

Pin* Grid::GetPinAt(std::pair<int, int> Point)
{
    ///TODO
    return 0;
}
