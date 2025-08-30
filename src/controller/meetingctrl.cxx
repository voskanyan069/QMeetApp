#include "controller/meetingctrl.hxx"
#include "ui/meetingwindow.hxx"
#include "ui/camerawidget.hxx"
#include "types/meetinginfo.hxx"
#include "types/exception.hxx"
#include "db/rtdb.hxx"

#include <QWidget>
#include <nlohmann/json.hpp>

#include <iostream>

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

void Controller::MeetingCtrl::AddMeetingInfoToRTDB(const MeetingInfo& info)
{
    DB::RTDB* pRTDB = DB::RTDB::GetInstance();
    nlohmann::json jsonData;
    pRTDB->GetJson(jsonData);
    try
    {
        nlohmann::json meetingBlock = nlohmann::json::object({
                {"name", info.GetName()},
                {"password", info.GetRealPassword()},
                });
        jsonData["meetings"].push_back(meetingBlock);
    }
    catch (const nlohmann::json::exception& e)
    {
        throw Exception(e.what());
    }
    std::cout << "DumpToFile: " << jsonData << std::endl;
    pRTDB->DumpToFile(jsonData);
}

void Controller::MeetingCtrl::GetCachedMeetings(
        std::vector<MeetingInfo>& cachedMeetings)
{
    DB::RTDB* pRTDB = DB::RTDB::GetInstance();
    nlohmann::json jsonData;
    pRTDB->GetJson(jsonData);
    try
    {
        for ( auto& meeting : jsonData["meetings"] )
        {
            std::string name = meeting["name"];
            std::string pass = meeting["password"];
            MeetingInfo info(name, pass);
            cachedMeetings.push_back(info);
        }
    }
    catch (const nlohmann::json::exception& e)
    {
        throw Exception(e.what());
    }
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
