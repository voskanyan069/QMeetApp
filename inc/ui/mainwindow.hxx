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
    void tryLocalLogin();
    void onLogOut();
    void onLoginSuccess();
    void onUsernameClicked();

private slots:
    void onLoginBtnClicked();
    void onCreateMeetingBtnClicked();
    void onJoinMeetingBtnClicked();

private:
    Ui::MainWindow* m_ui;
};

#endif // __UI_MAINWINDOW_HXX__
