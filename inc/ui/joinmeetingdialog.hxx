#ifndef __UI_JOINMEETINGDIALOG_HXX__
#define __UI_JOINMEETINGDIALOG_HXX__

#include <QDialog>

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

private slots:
    void onJoinMeetingClicked();


private:
    QWidget* m_parent;
    Ui::JoinMeetingDialog* m_ui;
};

#endif // __UI_JOINMEETINGDIALOG_HXX__
