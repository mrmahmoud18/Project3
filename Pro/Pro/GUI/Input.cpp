#include "Input.h"

#include "Interface.h"
#include "Bar.h"
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

ActionType Input::GetUserAction() const
{
    sf::Event dummyEvent;
    while(pInterface->Window.pollEvent(dummyEvent))
    {
        switch (dummyEvent.type)
        {
        case sf::Event::Closed:
            pInterface->Window.close();
            return EXIT;
        case sf::Event::MouseButtonPressed:
            if(dummyEvent.mouseButton.button == sf::Mouse::Left)
            {
                if(pInterface->StatusBar->GetGraphicsInfo().Contains(dummyEvent.mouseButton.x, dummyEvent.mouseButton.y))
                    return STATUS_BAR;
                if(pInterface->SimCanvas->GetGraphicsInfo().Contains(dummyEvent.mouseButton.x, dummyEvent.mouseButton.y))
                    return CANVAS_LEFT_CLICK;
                return ACTIVE_BAR_CLICK;
            }
            if(dummyEvent.mouseButton.button == sf::Mouse::Right)
                return CANVAS_RIGHT_CLICK;
            break;
        case sf::Event::MouseWheelScrolled:
            if(dummyEvent.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
            {
                if(dummyEvent.mouseWheelScroll.delta > 0)         return ZOOM_IN;
                else if(dummyEvent.mouseWheelScroll.delta < 0)    return ZOOM_OUT;
            }
            break;
        case sf::Event::KeyPressed:
            if(dummyEvent.key.code == sf::Keyboard::Add)
                return ZOOM_IN;
            else if(dummyEvent.key.code == sf::Keyboard::Subtract)
                return ZOOM_OUT;
        default:
            break;
        }
    }
    return NONE;
}

bool Input::IsDoubleClick() const
{
    sf::Event dummyEvent;
    sf::Clock dummyClock;
    while(dummyClock.getElapsedTime().asMilliseconds() < 500)
    {
        dummyEvent.type = sf::Event::Count;
        pInterface->Window.pollEvent(dummyEvent);
        switch(dummyEvent.type)
        {
        case sf::Event::Closed:
            exit(0);
        case sf::Event::MouseButtonPressed:
            return true;
        case sf::Event::MouseMoved:
            if(dummyEvent.mouseMove.x + dummyEvent.mouseMove.y > 5)
                return false;
            break;
        default:
            break;
        }
    }
    return false;
}

bool Input::IsDragging() const
{
    sf::Event dummyEvent;
    dummyEvent.type = sf::Event::Count;
    pInterface->Window.waitEvent(dummyEvent);
    switch (dummyEvent.type)
    {
    case sf::Event::Closed:
        exit(0);
    case sf::Event::MouseMoved:
        return sf::Mouse::isButtonPressed(sf::Mouse::Left);
    case sf::Event::MouseButtonReleased:
        return false;
    default:
        break;
    }
    return sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

bool Input::IsCtrlOn() const
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl);
}
