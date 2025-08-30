#ifndef __CONTROLLER_MEETING_CTRL_HXX__
#define __CONTROLLER_MEETING_CTRL_HXX__

#include "controller/controller.hxx"

#include <string>
#include <vector>
#include <map>

class QWidget;
class CameraWidget;
class MeetingWindow;
class MeetingInfo;
namespace Controller
{
    class ControllerMgr;
    class MeetingCtrl;
};

class Controller::MeetingCtrl : public Controller::Controller
{
    friend class ControllerMgr;

private:
    MeetingCtrl();

public:
    ~MeetingCtrl();
    MeetingCtrl(const MeetingCtrl&) = delete;
    MeetingCtrl& operator=(const MeetingCtrl&) = delete;

public:
    void AddMeetingInfoToRTDB(const MeetingInfo& info);
    void GetCachedMeetings(std::vector<MeetingInfo>& cachedMeetings);
    void SwitchToMeetingCtrl(const std::vector<QWidget*>& widgetsToClose);
    void AddNewCameraWidget();

private:
    CameraWidget* findCameraByID(int id);

private:
    int m_cameraCounter;
    std::map<int, CameraWidget*> m_cameraMap;
    MeetingWindow* m_meetingWindow;
};

#endif // !__CONTROLLER_MEETING_CTRL_HXX__
