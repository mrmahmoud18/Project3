#include "Component.h"

Component::Component()
{
    SetStatus(NORMAL);
}

Component::~Component() {}

void Component::SetStatus(Status r_Status)
{
    m_Status = r_Status;
}

Component::Status Component::GetStatus()
{
    return m_Status;
}


