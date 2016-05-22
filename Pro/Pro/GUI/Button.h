#pragma once

#include "../GraphicsInfo.h"
#include "../Actions/Action.h"

#include <string>

class Output;

class Button
{
public:
    enum ButtonStatus {NORMAL, FOCUSED, PRESSED, DISABLED};
    Button(const GraphicsInfo& r_GfxInfo, const std::string& r_ImagePath, Action::ActionType r_ActionType, ButtonStatus r_Status);
    ~Button();
    void Draw(Output* pOut);
    void SetStatus(ButtonStatus r_Status);
    ButtonStatus GetStatus() const;
    Action::ActionType GetAction() const;
    const GraphicsInfo& GetGraphicsInfo() const;

private:
    GraphicsInfo m_GfxInfo;
    std::string m_ImagePath;
    Action::ActionType m_ActionType;
    ButtonStatus m_Status;
    friend class Bar;
};
