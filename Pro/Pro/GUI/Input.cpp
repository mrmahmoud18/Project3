#include "Input.h"

#include "Interface.h"
#include "Output.h"
#include "Bar.h"
#include "Button.h"
#include "Canvas.h"

#include <vector>

Input::Input(Interface* pInterface)
{
    this->pInterface = pInterface;
}

Input::~Input() {}

std::pair<int,int> Input::GetMousePosition() const
{
    sf::Vector2i dummy = sf::Mouse::getPosition(pInterface->Window);
    return std::pair<int,int>(dummy.x, dummy.y);
}

std::pair<int,int> Input::GetPointClicked() const
{
    sf::Event dummyEvent;
    while(pInterface->Window.waitEvent(dummyEvent))
    {
        switch (dummyEvent.type)
        {
        case sf::Event::Closed:
            pInterface->Window.close();
            exit(0);
        case sf::Event::MouseButtonPressed:
            return std::pair<int,int>(dummyEvent.mouseButton.x, dummyEvent.mouseButton.y);
        default:
            break;
        }
    }
    return std::pair<int,int>(0, 0);
}

std::pair<int,int> Input::GetInstantClick() const
{
    sf::Event dummyEvent;
    pInterface->Window.waitEvent(dummyEvent);
    switch (dummyEvent.type)
    {
    case sf::Event::Closed:
        pInterface->Window.close();
        exit(0);
    case sf::Event::MouseButtonPressed:
        return std::pair<int,int>(dummyEvent.mouseButton.x, dummyEvent.mouseButton.y);
    default:
        return std::pair<int,int>(-1, -1);
    }
}

std::pair<int,int> Input::GetInstantRelease() const
{
    sf::Event dummyEvent;
    pInterface->Window.waitEvent(dummyEvent);
    switch (dummyEvent.type)
    {
    case sf::Event::Closed:
        exit(0);
    case sf::Event::MouseButtonReleased:
        return std::pair<int,int>(dummyEvent.mouseButton.x, dummyEvent.mouseButton.y);
    default:
        return std::pair<int,int>(-1, -1);
    }
}

std::string Input::GetSrting() const
{
    std::string EnteredString;
    sf::Event dummyEvent;
    while(pInterface->Window.waitEvent(dummyEvent))
    {
        switch (dummyEvent.type)
        {
        case sf::Event::Closed:
            exit(0);
        case sf::Event::TextEntered:
            if (dummyEvent.text.unicode < 128 && dummyEvent.text.unicode > 31)
                EnteredString += static_cast<char>(dummyEvent.text.unicode);
            else if (dummyEvent.text.unicode == 8)
                EnteredString = EnteredString.substr(0, EnteredString.size()-1);
            else if (dummyEvent.text.unicode == 13)
                return EnteredString;
            pInterface->PrintMsg(EnteredString);
            pInterface->SyncWindow();
            break;
        case sf::Event::MouseButtonPressed:
            return EnteredString;
        default:
            break;
        }
    }
    return EnteredString;
}

Action::ActionType Input::GetUserAction() const
{
    sf::Event dummyEvent;
    while(pInterface->Window.pollEvent(dummyEvent))
    {
        switch (dummyEvent.type)
        {
        case sf::Event::Closed:
            pInterface->Window.close();
            return Action::EXIT;
        case sf::Event::MouseButtonPressed:
            if(dummyEvent.mouseButton.button == sf::Mouse::Left)
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                    return Action::ADJUST_OFFSET;
                if(pInterface->StatusBar->GetGraphicsInfo().Contains(dummyEvent.mouseButton.x, dummyEvent.mouseButton.y))
                    return Action::STATUS_BAR;
                if(pInterface->SimCanvas->GetGraphicsInfo().Contains(dummyEvent.mouseButton.x, dummyEvent.mouseButton.y))
                    return Action::CANVAS_LEFT_CLICK;
                return Action::ACTIVE_BAR_CLICK;
            }
            if(dummyEvent.mouseButton.button == sf::Mouse::Right)
                return Action::CANVAS_RIGHT_CLICK;
            break;
        case sf::Event::MouseMoved:
            /*if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                    {
                        std::pair<int,int> NewMousePosition = GetMousePosition();
                        pInterface->AdjustOffset(std::pair<int,int>(MousePosition.first-NewMousePosition.first, MousePosition.second-NewMousePosition.second));
                        return NONE;
                    }
                else
                    return MOVE;
            }*/
            break;
        case sf::Event::MouseWheelScrolled:
            if(dummyEvent.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
            {
                if(dummyEvent.mouseWheelScroll.delta > 0)         return Action::ZOOM_IN;
                else if(dummyEvent.mouseWheelScroll.delta < 0)    return Action::ZOOM_OUT;
            }
            break;
        case sf::Event::KeyPressed:
            if(dummyEvent.key.code == sf::Keyboard::Add)
                return Action::ZOOM_IN;
            else if(dummyEvent.key.code == sf::Keyboard::Subtract)
                return Action::ZOOM_OUT;
        default:
            break;
        }
    }
    return Action::NONE;
}
/*
Action::ActionType Input::HandleButton(Button* pButton, sf::Event dummyEvent) const
{
    if(pButton->GetStatus() == Button::DISABLED)
        return Action::NONE;
    pButton->SetStatus(Button::FOCUSED);
    pButton->Draw(pInterface->MainOutput);
    pInterface->MainOutput->SyncWindow();
    while(pInterface->Window.waitEvent(dummyEvent))
        switch (dummyEvent.type)
        {
        case sf::Event::Closed:
            pInterface->Window.close();
            return Action::EXIT;
        case sf::Event::MouseButtonReleased:
            if(pButton->GetGraphicsInfo().Contains(dummyEvent.mouseButton.x, dummyEvent.mouseButton.y))
                {
                    if(pButton->GetAction() != Action::ADD)
                    {
                        pButton->SetStatus(Button::NORMAL);
                        pButton->Draw(pInterface->MainOutput);
                        pInterface->MainOutput->SyncWindow();
                        return pButton->GetAction();
                    }
                    pButton->SetStatus(Button::PRESSED);
                    pInterface->MainOutput->UpdateActiveBar();
                    pInterface->MainOutput->SyncWindow();
                    Action::ActionType dummyAction = HandleADD();
                    pButton->SetStatus(Button::NORMAL);
                    pInterface->MainOutput->UpdateActiveBar();
                    pInterface->MainOutput->SyncWindow();
                    return dummyAction;
                }
            else
                {
                    pButton->SetStatus(Button::NORMAL);
                    pButton->Draw(pInterface->MainOutput);
                    pInterface->MainOutput->SyncWindow();
                    return Action::NONE;
                }
            break;
        default:
            pButton->Draw(pInterface->MainOutput);
            pInterface->MainOutput->SyncWindow();
            break;
        }
    return Action::NONE;
}

Action::ActionType Input::HandleADD() const
{
    pInterface->MainOutput->DrawGatesBars();
    pInterface->MainOutput->SyncWindow();
    sf::Event dummyEvent;
    while(pInterface->Window.waitEvent(dummyEvent))
    {
        switch (dummyEvent.type)
        {
        case sf::Event::Closed:
            pInterface->Window.close();
            return Action::EXIT;
        case sf::Event::MouseButtonPressed:
            {
                const std::vector<Button*>& dummyVector = pInterface->GatesBar->GetButtons();
                for(unsigned int i = 0; i < dummyVector.size(); i++)
                    if(dummyVector[i] != NULL)
                        if(dummyVector[i]->GetGraphicsInfo().Contains(dummyEvent.mouseButton.x, dummyEvent.mouseButton.y))
                            return dummyVector[i]->GetAction();
            }
            {
                const std::vector<Button*>& dummyVector = pInterface->NGatesBar->GetButtons();
                for(unsigned int i = 0; i < dummyVector.size(); i++)
                    if(dummyVector[i] != NULL)
                        if(dummyVector[i]->GetGraphicsInfo().Contains(dummyEvent.mouseButton.x, dummyEvent.mouseButton.y))
                            return dummyVector[i]->GetAction();
            }
        case sf::Event::KeyPressed:
            return Action::NONE;
        default:
            pInterface->MainOutput->DrawGatesBars();
            pInterface->MainOutput->SyncWindow();
            break;
        }
    }
    return Action::NONE;
}
*/
bool Input::IsDragging() const
{
    return sf::Mouse::isButtonPressed(sf::Mouse::Left);
}
