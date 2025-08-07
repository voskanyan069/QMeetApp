#ifndef __CONTROLLER_MEETING_HXX__
#define __CONTROLLER_MEETING_HXX__

#include "controller/controller.hxx"

#include <vector>
#include <map>

class QWidget;
class CameraWidget;
class MeetingWindow;
namespace Controller
{
    class Meeting;
};

class Controller::Meeting : public Controller::Controller
{
    friend class InteractionMgr;

private:
    Meeting();

public:
    ~Meeting();
    Meeting(const Meeting&) = delete;
    Meeting& operator=(const Meeting&) = delete;

public:
    void SwitchToMeeting(const std::vector<QWidget*>& widgetsToClose);
    void AddNewCameraWidget();

private:
    CameraWidget* findCameraByID(int id);

private:
    int m_cameraCounter;
    std::map<int, CameraWidget*> m_cameraMap;
    MeetingWindow* m_meetingWindow;
};

#endif // !__CONTROLLER_MEETING_HXX__
