#include "controller/controllermgr.hxx"

Controller::ControllerMgr* Controller::ControllerMgr::m_instance = nullptr;

Controller::ControllerMgr::ControllerMgr()
{
}

Controller::ControllerMgr*
Controller::ControllerMgr::GetManager()
{
    if (nullptr == m_instance)
    {
        m_instance = new ControllerMgr();
    }
    return m_instance;
}
