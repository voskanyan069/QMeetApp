#ifndef __CONTROLLER_INTERACTION_MGR_HXX__
#define __CONTROLLER_INTERACTION_MGR_HXX__

#include "controller/controller.hxx"

#include <concepts>

template <typename T>
concept ControllerType = std::derived_from<T, Controller::Controller>;

namespace Controller
{
    class ControllerMgr;
};

class Controller::ControllerMgr
{
private:
    ControllerMgr();

public:
    ControllerMgr(const ControllerMgr&) = delete;
    ControllerMgr& operator=(const ControllerMgr&) = delete;

public:
    static ControllerMgr* GetManager();

public:
    template <ControllerType CT>
    CT* GetController()
    {
        static CT* pNewController = new CT();
        return pNewController;
    }

private:
    static ControllerMgr* m_instance;
};

#endif // !__CONTROLLER_MODULESCONTROLLER_HXX__
