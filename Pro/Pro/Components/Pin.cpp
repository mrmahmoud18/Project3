#include "Pin.h"

Pin::Pin(std::pair<int,int> r_Center): m_Center(r_Center)
{
	SetStatus(FLOATING);
}

Pin::~Pin() {}

void Pin::SetCenter(std::pair<int,int> r_Center)
{
    m_Center = r_Center;
}

std::pair<int,int> Pin::GetCenter()
{
    return m_Center;
}

void Pin::SetStatus(Status r_Status)
{
    m_Status = r_Status;
}

Pin::Status Pin::GetStatus()
{
    return m_Status;
}
