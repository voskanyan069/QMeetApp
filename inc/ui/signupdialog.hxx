#ifndef __UI_SIGNUPDIALOG_HXX__
#define __UI_SIGNUPDIALOG_HXX__

#include <QWidget>
#include <QDialog>
#include <QIcon>

namespace Ui {
class SignupDialog;
}

class SignupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SignupDialog(QWidget* parent = nullptr);
    ~SignupDialog();

private:
    void connectSlots();
    void initPasswordEye();

private slots:
    void changePassShowState();
    void openLogInDialog();

private:
    Ui::SignupDialog* m_ui;
    QWidget* m_parent;
    QIcon m_eyeOpened;
    QIcon m_eyeClosed;
};

#endif // __UI_SIGNUPDIALOG_HXX__
