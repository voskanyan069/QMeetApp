#ifndef __CONTROLLER_INTERACTION_MGR_HXX__
#define __CONTROLLER_INTERACTION_MGR_HXX__

#include "controller/controller.hxx"

#include <concepts>

template <typename T>
concept ControllerType = std::derived_from<T, Controller::Controller>;

namespace Controller
{
    class InteractionMgr;
};

class Controller::InteractionMgr
{
private:
    InteractionMgr();

public:
    InteractionMgr(const InteractionMgr&) = delete;
    InteractionMgr& operator=(const InteractionMgr&) = delete;

public:
    static InteractionMgr* GetManager();

public:
    template <ControllerType CT>
    CT* GetController()
    {
        static CT* pNewController = new CT();
        return pNewController;
    }

private:
    static InteractionMgr* m_instance;
};

#endif // !__CONTROLLER_MODULESCONTROLLER_HXX__
