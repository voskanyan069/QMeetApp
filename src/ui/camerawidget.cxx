#include "ui/camerawidget.hxx"
#include "io/camera.hxx"

#include <QString>
#include <QTimer>
#include <QPainter>
#include <QVBoxLayout>

#include <opencv2/opencv.hpp>

CameraWidget::CameraWidget(QWidget* parent, int id)
    : QWidget(parent)
    , m_id(id)
    , m_uiCameraView(new QLabel(this))
{
    setMinimumSize(80, 60);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    initCamera();

    QTimer* timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,QOverload<>::of(&CameraWidget::update));
    timer->start(30);
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
    catch (...)
    {
        /// TODO: Open dialog with error
    }
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
