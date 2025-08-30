#include "ui/camerawidget.hxx"
#include "ui/popupdialog.hxx"
#include "controller/controllermgr.hxx"
#include "controller/meetingctrl.hxx"
#include "types/exception.hxx"
#include "io/camera.hxx"

#include <QString>
#include <QTimer>
#include <QPainter>
#include <QPushButton>
#include <QVBoxLayout>

#include <opencv2/opencv.hpp>

CameraWidget::CameraWidget(QWidget* parent, int id)
    : QWidget(parent)
    , m_id(id)
    , m_uiCameraView(new QLabel(this))
    , m_errDialog(nullptr)
{
    setMinimumSize(80, 60);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    initCamera();
    QTimer* timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,QOverload<>::of(&CameraWidget::update));
    timer->start(30);
}

CameraWidget::~CameraWidget()
{
    if ( nullptr != m_errDialog )
    {
        delete m_errDialog;
    }
}

void CameraWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    cv::Mat frame;
    m_camDevice->ReadFrame(frame);
    m_camDevice->ReverseFrame(frame);
    if (!frame.empty())
    {
        QImage img(frame.data, frame.cols, frame.rows, frame.step,
                QImage::Format_BGR888);
        painter.drawImage(rect(), img);
    }
}

void CameraWidget::resizeEvent(QResizeEvent* event)
{
    int width = event->size().width();
    int height = (width * 3) / 4;
    setFixedHeight(height);
    QWidget::resizeEvent(event);
}

void CameraWidget::initCamera()
{
    m_camDevice = new IO::Camera(m_id, 640, 480);
    try
    {
        m_camDevice->Init();
    }
    catch (const Exception& e)
    {
        delete m_camDevice;
        m_errDialog = new PopupDialog(this,
                PopupBoxType::BOX_WITH_CUSTOM_BUTTONS,
                PopupMessageType::ERROR, e.what());
        QPushButton* tryAgainBtn = new QPushButton(m_errDialog);
        tryAgainBtn->setText("Try again");
        connect(tryAgainBtn, &QPushButton::clicked, this,
                &CameraWidget::onTryAgainClicked);
        m_errDialog->AddButton(tryAgainBtn);
        m_errDialog->exec();
    }
}

void CameraWidget::onTryAgainClicked()
{
    Controller::ControllerMgr* controller =
        Controller::ControllerMgr::GetManager();
    std::vector<QWidget*> widgets = {m_errDialog};
    Controller::MeetingCtrl* meetingCtrl =
        controller->GetController<Controller::MeetingCtrl>();
    meetingCtrl->SwitchToMeetingCtrl(widgets);
    delete m_errDialog;
}

void CameraWidget::updateCameraFrame()
{
    cv::Mat frame;
    m_camDevice->ReadFrame(frame);
    if ( frame.empty() )
    {
        return;
    }
    cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
    QImage img(frame.data, frame.cols, frame.rows, frame.step,
            QImage::Format_RGB888);
    m_uiCameraView->setPixmap(QPixmap::fromImage(img).scaled(
        m_uiCameraView->size(),
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation
    ));
}

int CameraWidget::GetID() const
{
    return m_id;
}
