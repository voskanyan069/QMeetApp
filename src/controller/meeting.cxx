#include "controller/meeting.hxx"
#include "ui/meetingwindow.hxx"
#include "ui/camerawidget.hxx"

#include <QWidget>

Controller::Meeting::Meeting()
    : Controller()
    , m_cameraCounter(0)
    , m_cameraMap()
    , m_meetingWindow(nullptr)
{
}

Controller::Meeting::~Meeting()
{
    delete m_meetingWindow;
}

void Controller::Meeting::SwitchToMeeting(
        const std::vector<QWidget*>& widgetsToClose)
{
    for ( QWidget* pWidget : widgetsToClose )
    {
        pWidget->close();
    }
    m_meetingWindow = new MeetingWindow();
    m_meetingWindow->show();
}

void Controller::Meeting::AddNewCameraWidget()
{
    if ( nullptr == m_meetingWindow )
    {
        return;
    }
    int camId = m_cameraCounter++;
    CameraWidget* camera = m_meetingWindow->addCameraWidget(camId);
    m_cameraMap[camId] = camera;
}

CameraWidget* Controller::Meeting::findCameraByID(int id)
{
    auto itCamera = m_cameraMap.find(id);
    if ( m_cameraMap.end() == itCamera )
    {
        return nullptr;
    }
    return itCamera->second;
}
