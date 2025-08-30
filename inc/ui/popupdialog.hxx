#ifndef __UI_POPUPDIALOG_HXX__
#define __UI_POPUPDIALOG_HXX__

#include <QDialog>
#include <QPushButton>

enum class PopupMessageType
{
    INFO,
    WARNING,
    ERROR
};

enum class PopupBoxType
{
    BOX_WITH_CLOSE,
    BOX_WITH_YES_NO,
    BOX_WITH_CUSTOM_BUTTONS
};

namespace Ui {
class PopupDialog;
}

class PopupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PopupDialog(QWidget* parent,
            const PopupBoxType& boxType = PopupBoxType::BOX_WITH_CLOSE,
            const PopupMessageType& msgType = PopupMessageType::INFO,
            const std::string& msgText = "");
    explicit PopupDialog(QWidget* parent, bool* bResult,
            const PopupMessageType& msgType = PopupMessageType::INFO,
            const std::string& msgText = "");
    ~PopupDialog();

public:
    void AddButton(QPushButton* button);
    
private:
    void initMessageType(const PopupMessageType& msgType,
            const std::string& msgText);
    void fillBtnList(const PopupBoxType& boxType);
    void initButtonBox();

private slots:
    void closeWindow();
    void closeYesWindow();
    void closeNoWindow();

private:
    Ui::PopupDialog* m_ui;
    bool* m_bYesNoResult;
    std::vector<QPushButton*> m_btnList;

private:
    QPushButton* m_closeBtn;
    QPushButton* m_yesBtn;
    QPushButton* m_noBtn;
};

#endif // __UI_POPUPDIALOG_HXX__
