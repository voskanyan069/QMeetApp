#ifndef __CONTROLLER_CONTROLLER_HXX__
#define __CONTROLLER_CONTROLLER_HXX__

namespace Controller
{
    class Controller;
};

class Controller::Controller
{
protected:
    Controller() = default;

public:
    Controller(const Controller&) = delete;
    Controller& operator=(const Controller&) = delete;
};

#endif // !__CONTROLLER_CONTROLLER_HXX__
