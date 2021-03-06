#pragma once

#include "Gate.h"

class NAND3 : public Gate
{
public:
	NAND3(const GraphicsInfo &r_GfxInfo, std::string r_Label = "");
	virtual void Operate();
	virtual void Draw(Interface* pInterface);
};

