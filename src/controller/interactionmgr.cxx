#include "controller/interactionmgr.hxx"
#include "controller/meeting.hxx"

Controller::InteractionMgr* Controller::InteractionMgr::m_instance = nullptr;

Controller::InteractionMgr::InteractionMgr()
{
}

Controller::InteractionMgr*
Controller::InteractionMgr::GetManager()
{
    if (nullptr == m_instance)
    {
        m_instance = new InteractionMgr();
    }
    return m_instance;
}
