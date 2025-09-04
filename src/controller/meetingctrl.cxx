#include "controller/meetingctrl.hxx"
#include "controller/clientctrl.hxx"
#include "controller/controllermgr.hxx"
#include "ui/meetingwindow.hxx"
#include "ui/camerawidget.hxx"
#include "types/meetinginfo.hxx"
#include "types/exception.hxx"
#include "net/client.hxx"
#include "db/rtdb.hxx"

#include <QWidget>
#include <nlohmann/json.hpp>

#include <iostream>

Controller::MeetingCtrl::MeetingCtrl()
    : Controller()
    , m_cameraCounter(0)
    , m_client(nullptr)
    , m_meetingWindow(nullptr)
    , m_cameraMap()
{
    ControllerMgr* mgr = ControllerMgr::GetManager();
    ClientCtrl* ctrl = mgr->GetController<ClientCtrl>();
    m_client = ctrl->GetClient("meeting");
    m_client->ConnectToServer();
}

Controller::MeetingCtrl::~MeetingCtrl()
{
    delete m_meetingWindow;
}

void Controller::MeetingCtrl::CreateMeeting(const MeetingInfo& info)
{
    if ( nullptr == m_client )
    {
        return;
    }
    nlohmann::json jsonData;
    m_client->SendGetRequest("/create", "id=" + info.GetID() +
            "&password=" + info.GetPassword(), jsonData);
}

bool Controller::MeetingCtrl::IsExists(const MeetingInfo& info)
{
    if ( nullptr == m_client )
    {
        return false;
    }
    nlohmann::json jsonData;
    m_client->SendGetRequest("/is_exists",
            "id=" + info.GetID() +
            "&password=" + info.GetPassword(), jsonData);
    try
    {
        bool exists = jsonData["exists"];
        return exists;
    }
    catch (const nlohmann::json::exception& e)
    {
        throw Exception(e.what());
    }
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

void Controller::MeetingCtrl::AddCachedMeetingInfo(const MeetingInfo& info)
{
    DB::RTDB* pRTDB = DB::RTDB::GetInstance();
    bool bExists = false;
    nlohmann::json jsonData;
    pRTDB->GetJson(jsonData);
    try
    {
        for ( auto& meet : jsonData["meetings"] )
        {
            if ( meet["name"] == info.GetName() )
            {
                std::cout << "Meeting with this name exists" << std::endl;
                meet["password"] = info.GetRealPassword();
                bExists = true;
            }
        }
    }
    catch (const nlohmann::json::exception& e)
    {
        throw Exception(e.what());
    }
    if ( !bExists )
    {
        nlohmann::json meetingBlock = nlohmann::json::object({
                {"name", info.GetName()},
                {"password", info.GetRealPassword()},
                });
        try
        {
            jsonData["meetings"].push_back(meetingBlock);
        }
        catch (const nlohmann::json::exception& e)
        {
            throw Exception(e.what());
        }
    }
    std::cout << "DumpToFile: " << jsonData << std::endl;
    pRTDB->DumpToFile(jsonData);
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
