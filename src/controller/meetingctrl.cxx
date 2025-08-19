#include "controller/meetingctrl.hxx"
#include "ui/meetingwindow.hxx"
#include "ui/camerawidget.hxx"

#include <QWidget>

Controller::MeetingCtrl::MeetingCtrl()
    : Controller()
    , m_cameraCounter(0)
    , m_cameraMap()
    , m_meetingWindow(nullptr)
{
}

Controller::MeetingCtrl::~MeetingCtrl()
{
    delete m_meetingWindow;
}

void Controller::MeetingCtrl::SwitchToMeetingCtrl(
        const std::vector<QWidget*>& widgetsToClose)
{
    for ( QWidget* pWidget : widgetsToClose )
    {
        pWidget->close();
    }
    m_meetingWindow = new MeetingWindow();
    m_meetingWindow->show();
}

void Controller::MeetingCtrl::AddNewCameraWidget()
{
    if ( nullptr == m_meetingWindow )
    {
        return;
    }
    int camId = m_cameraCounter++;
    CameraWidget* camera = m_meetingWindow->addCameraWidget(camId);
    m_cameraMap[camId] = camera;
}

CameraWidget* Controller::MeetingCtrl::findCameraByID(int id)
{
    auto itCamera = m_cameraMap.find(id);
    if ( m_cameraMap.end() == itCamera )
    {
        return nullptr;
    }
    return itCamera->second;
}
