#include "Stop.h"

#include "../ApplicationManager.h"

Stop::Stop(ApplicationManager *pApp): Action(pApp) {}

void Stop::ReadActionParameters() {}

void Stop::Execute()
{
    ///TODO
}

void Stop::Undo() {}

void Stop::Redo() {}
