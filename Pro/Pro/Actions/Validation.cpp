#include "Validation.h"
#include "../ApplicationManager.h"


Validation::Validation(ApplicationManager *pApp)
	:Action(pApp)
{
}


Validation::~Validation()
{
}

void Validation::Execute()
{
	if (!pManager->IsValidToSimulate())
	{
		throw;
	} 
}

void Validation::ReadActionParameters()
{
}

void Validation::Undo()
{
}

void Validation::REDO()
{
}
