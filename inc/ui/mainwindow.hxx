#ifndef __UI_MAINWINDOW_HXX__
#define __UI_MAINWINDOW_HXX__

#include <QMainWindow>
#include <QLabel>
#include <QTimer>

namespace IO
{
    class Camera;
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void connectSlots();
    //void addMyWebcam();

private slots:
    //void updateMyWebcam();
    void onLoginBtnClicked();
    void onCreateMeetingBtnClicked();
    void onJoinMeetingBtnClicked();

private:
    Ui::MainWindow* m_ui;
    //QLabel* m_uiMyWebcam;
    //IO::Camera* m_pMyCamera;
    //QTimer m_timer;
};

#endif // __UI_MAINWINDOW_HXX__
