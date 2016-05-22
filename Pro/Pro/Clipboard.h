#pragma once

#include <vector>

class Component;

class Clipboard
{
    public:
        void Push(std::vector<Component*> ToBeSaved);
        std::vector<Component*> Pop();

    private:
        std::vector< std::vector<Component*> > Saved;
};
