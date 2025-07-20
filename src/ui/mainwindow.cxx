#include "ui/mainwindow.hxx"
#include "ui/loginpopup.hxx"
#include "io/camera.hxx"
#include "sys/macro.hxx"
#include "ui_mainwindow.h"

#include <QApplication>
#include <QLabel>
#include <QImage>
#include <QTimer>
#include <opencv2/opencv.hpp>

#include <chrono>
#include <thread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
    //, m_uiMyWebcam(m_ui->myCamWidget)
    //, m_pMyCamera(nullptr)
    //, m_timer()
{
    m_ui->setupUi(this);
    connectSlots();
    //addMyWebcam();
    //connect(&m_timer, &QTimer::timeout, this, &MainWindow::updateMyWebcam);
    //m_timer.start(30);
}

void MainWindow::connectSlots()
{
    connect(m_ui->loginBtn, &QPushButton::clicked, this,
            &MainWindow::onLoginBtnClicked);
}

/*
void MainWindow::updateMyWebcam()
{
    cv::Mat frame;
    m_pMyCamera->ReadFrame(frame);
    if ( frame.empty() )
    {
        return;
    }
    cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
    QImage img(frame.data, frame.cols, frame.rows, frame.step,
            QImage::Format_RGB888);
    m_uiMyWebcam->setPixmap(QPixmap::fromImage(img).scaled(
        m_uiMyWebcam->size(),
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation
    ));
}
*/

/*
void MainWindow::addMyWebcam()
{
    QSize size(640, 480);
    m_pMyCamera = new IO::Camera(0, size.width(), size.height());
    m_pMyCamera->Init();
    m_uiMyWebcam->resize(size);
    m_uiMyWebcam->show();
}
*/

MainWindow::~MainWindow()
{
    delete m_ui;
    //SAFE_DELETE(m_pMyCamera);
}

void MainWindow::onLoginBtnClicked()
{
    LoginPopup login(this);
    login.exec();
}

