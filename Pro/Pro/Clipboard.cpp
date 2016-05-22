#include "Clipboard.h"

void Clipboard::Push(std::vector<Component*> ToBeSaved)
{
    Saved.push_back(ToBeSaved);
}

std::vector<Component*> Clipboard::Pop()
{
    std::vector<Component*> dummy = Saved.back();
    Saved.pop_back();
    return dummy;
}
