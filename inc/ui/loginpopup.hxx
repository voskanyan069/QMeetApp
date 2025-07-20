#ifndef __UI_LOGINPOPUP_HXX__
#define __UI_LOGINPOPUP_HXX__

#include <QWidget>
#include <QDialog>
#include <QIcon>

namespace Ui {
class LoginPopup;
}

class LoginPopup : public QDialog
{
    Q_OBJECT

public:
    explicit LoginPopup(QWidget* parent = nullptr);
    ~LoginPopup();

private:
    void connectSlots();
    void initPasswordEye();

private slots:
    void changePassShowState();
    void openSignUpDialog();

private:
    Ui::LoginPopup* m_ui;
    QWidget* m_parent;
    QIcon m_eyeOpened;
    QIcon m_eyeClosed;
};

#endif // __UI_LOGINPOPUP_HXX__
