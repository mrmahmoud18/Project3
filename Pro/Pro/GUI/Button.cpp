#include "Button.h"

#include "Output.h"

Button::Button(const GraphicsInfo& r_GfxInfo, const std::string& r_ImagePath, Action::ActionType r_ActionType, ButtonStatus r_Status): m_GfxInfo(r_GfxInfo)
{
    m_ImagePath = r_ImagePath;
    m_ActionType = r_ActionType;
    m_Status = r_Status;
}

Button::~Button(){}

void Button::Draw(Output* pOut)
{
    pOut->DrawButton(m_GfxInfo, m_ImagePath, m_Status);
}

void Button::SetStatus(ButtonStatus r_Status)
{
    m_Status = r_Status;
}

Button::ButtonStatus Button::GetStatus() const
{
    return m_Status;
}

Action::ActionType Button::GetAction() const
{
    return m_ActionType;
}

const GraphicsInfo& Button::GetGraphicsInfo() const
{
    return m_GfxInfo;
}
