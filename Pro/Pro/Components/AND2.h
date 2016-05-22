#pragma once

#include "Gate.h"

class AND2: public Gate
{
public:
	AND2(const GraphicsInfo &r_GfxInfo, std::string r_Label="");
	virtual void Operate();
	virtual void Draw(Interface* pInterface);
};
