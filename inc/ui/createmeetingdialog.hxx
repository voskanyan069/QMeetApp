#ifndef __UI_CREATEMEETINGDIALOG_HXX__
#define __UI_CREATEMEETINGDIALOG_HXX__

#include <QDialog>
#include <QIcon>

namespace Ui {
class CreateMeetingDialog;
}

class CreateMeetingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateMeetingDialog(QWidget* parent = nullptr);
    ~CreateMeetingDialog();

private:
    void connectSlots();
    void initPasswordEye();

private slots:
    void changePassShowState();

private:
    Ui::CreateMeetingDialog* m_ui;
    QIcon m_eyeOpened;
    QIcon m_eyeClosed;
};

#endif // __UI_CREATEMEETINGDIALOG_HXX__
