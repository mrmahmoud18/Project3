#pragma once

#include "Gate.h"

class BUFFER: public Gate
{
public:
	BUFFER(const GraphicsInfo &r_GfxInfo, std::string r_Label = "");
	virtual void Operate();
	virtual void Draw(Interface* pInterface);
};
