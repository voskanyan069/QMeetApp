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
namespace Net
{
    class Client;
}
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
    void CreateMeeting(const MeetingInfo& info);
    bool IsExists(const MeetingInfo& info);
    void GetCachedMeetings(std::vector<MeetingInfo>& cachedMeetings);
    void SwitchToMeetingCtrl(const std::vector<QWidget*>& widgetsToClose);
    void AddNewCameraWidget();
    void AddCachedMeetingInfo(const MeetingInfo& info);

private:
    CameraWidget* findCameraByID(int id);

private:
    int m_cameraCounter;
    Net::Client* m_client;
    MeetingWindow* m_meetingWindow;
    std::map<int, CameraWidget*> m_cameraMap;
};

#endif // !__CONTROLLER_MEETING_CTRL_HXX__
