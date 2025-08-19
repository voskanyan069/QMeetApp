#ifndef __UI_MEETINGWINDOW_HXX__
#define __UI_MEETINGWINDOW_HXX__

#include <QWidget>

namespace Ui
{
    class MeetingWindow;
}

namespace Controller
{
    class MeetingCtrl;
}

class CameraWidget;

class MeetingWindow : public QWidget
{
    Q_OBJECT

    friend class Controller::MeetingCtrl;

public:
    explicit MeetingWindow(QWidget* parent = nullptr);
    ~MeetingWindow();

private:
    void addMyWebcam();
    CameraWidget* addCameraWidget(int id);
    void tempInit();

private:
    Ui::MeetingWindow* m_ui;
};

#endif // __UI_MEETINGWINDOW_HXX__
