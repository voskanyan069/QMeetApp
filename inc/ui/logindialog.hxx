#ifndef __UI_LOGINDIALOG_HXX__
#define __UI_LOGINDIALOG_HXX__

#include <QWidget>
#include <QDialog>
#include <QIcon>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget* parent = nullptr);
    ~LoginDialog();

private:
    void connectSlots();
    void initPasswordEye();

private slots:
    void changePassShowState();
    void openSignUpDialog();

private:
    Ui::LoginDialog* m_ui;
    QWidget* m_parent;
    QIcon m_eyeOpened;
    QIcon m_eyeClosed;
};

#endif // __UI_LOGINDIALOG_HXX__
