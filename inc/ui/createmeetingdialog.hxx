#ifndef __UI_CREATEMEETINGDIALOG_HXX__
#define __UI_CREATEMEETINGDIALOG_HXX__

#include <QDialog>

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
    Ui::CreateMeetingDialog* m_ui;
};

#endif // __UI_CREATEMEETINGDIALOG_HXX__
