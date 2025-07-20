#ifndef __UI_SIGNUPPOPUP_HXX__
#define __UI_SIGNUPPOPUP_HXX__

#include <QWidget>
#include <QDialog>
#include <QIcon>

namespace Ui {
class SignupPopup;
}

class SignupPopup : public QDialog
{
    Q_OBJECT

public:
    explicit SignupPopup(QWidget* parent = nullptr);
    ~SignupPopup();

private:
    void connectSlots();
    void initPasswordEye();

private slots:
    void changePassShowState();
    void openLogInDialog();

private:
    Ui::SignupPopup* m_ui;
    QWidget* m_parent;
    QIcon m_eyeOpened;
    QIcon m_eyeClosed;
};

#endif // __UI_SIGNUPPOPUP_HXX__
