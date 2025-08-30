#ifndef __UI_JOINMEETINGDIALOG_HXX__
#define __UI_JOINMEETINGDIALOG_HXX__

#include <QDialog>
#include <QIcon>

#include <vector>

class MeetingInfo;
namespace Ui {
class JoinMeetingDialog;
}

class JoinMeetingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit JoinMeetingDialog(QWidget* parent = nullptr);
    ~JoinMeetingDialog();

private:
    void connectSlots();
    void fillCachedMeetingNames();
    void initPasswordEye();

private slots:
    void onJoinMeetingClicked();
    void onComboBoxIndexChanged(int index);
    void changePassShowState();

private:
    QWidget* m_parent;
    Ui::JoinMeetingDialog* m_ui;
    std::vector<MeetingInfo> m_cachedMeetings;
    QIcon m_eyeOpened;
    QIcon m_eyeClosed;
};

#endif // __UI_JOINMEETINGDIALOG_HXX__
