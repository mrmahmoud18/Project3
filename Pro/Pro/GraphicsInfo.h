#pragma once

#include <utility>

class GraphicsInfo
{
private:
	int X, Y, Width, Height;
public:
    GraphicsInfo(int X, int Y, int Width, int Height);
    GraphicsInfo(std::pair<int,int> Point, std::pair<int,int> Size);
    int GetX() const;
    int GetY() const;
    int GetWidth() const;
    int GetHeight() const;
    void SetX(int X);
    void SetY(int Y);
    void SetWidth(int Width);
    void SetHeight(int Height);
    void ShiftUp(int Offset);
    void ShiftDown(int Offset);
    void ShiftLeft(int Offset);
    void ShiftRight(int Offset);
    bool Contains(int x, int y) const;
    bool Contains(std::pair<int,int> Point) const;
};
