#include "Component.h"

Component::Component()
{
    SetStatus(NORMAL);
}

Component::~Component() {}

void Component::SetStatus(ComponentStatus r_Status)
{
    m_Status = r_Status;
}

ComponentStatus Component::GetStatus() const
{
    return m_Status;
}
