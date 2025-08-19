#include "ui/meetingwindow.hxx"
#include "ui/camerawidget.hxx"
#include "ui_meetingwindow.h"
#include "controller/controllermgr.hxx"
#include "controller/meetingctrl.hxx"

MeetingWindow::MeetingWindow(QWidget *parent)
    : QWidget(parent)
    , m_ui(new Ui::MeetingWindow)
{
    m_ui->setupUi(this);
    m_ui->splitter->setSizes({300,100});
    addMyWebcam();
    tempInit();
}

MeetingWindow::~MeetingWindow()
{
    delete m_ui;
}

void MeetingWindow::addMyWebcam()
{
    CameraWidget* item = new CameraWidget(this, 0);
    item->setStyleSheet("background-color: red");
    m_ui->cameraGridLayout->addWidget(item, 0, 0);
}

CameraWidget* MeetingWindow::addCameraWidget(int id)
{
    int count = m_ui->cameraGridLayout->count();
    int itemsPerRow = 3;
    int row = count / itemsPerRow;
    int col = count % itemsPerRow;
    CameraWidget* item = new CameraWidget(this, id);
    m_ui->cameraGridLayout->addWidget(item, row, col);
    return item;
}

void MeetingWindow::tempInit()
{
    for (int i = 0; i < 50; ++i)
    {
        std::string user = "Username_";
        m_ui->participantsListWidget->addItem(QString(user.c_str()));
    }
    for (int i = 0; i < 20; ++i)
    {
        Controller::ControllerMgr* mgr =
            Controller::ControllerMgr::GetManager();
        Controller::MeetingCtrl* meetingCtrl =
            mgr->GetController<Controller::MeetingCtrl>();
        meetingCtrl->AddNewCameraWidget();
    }
}
