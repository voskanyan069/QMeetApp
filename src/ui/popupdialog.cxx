#include "ui/popupdialog.hxx"
#include "ui_popupdialog.h"

PopupDialog::PopupDialog(QWidget* parent, const PopupBoxType& boxType,
        const PopupMessageType& msgType, const std::string& msgText)
    : QDialog(parent)
    , m_ui(new Ui::PopupDialog)
    , m_bYesNoResult(nullptr)
    , m_btnList({})
    , m_closeBtn(nullptr)
    , m_yesBtn(nullptr)
    , m_noBtn(nullptr)
{
    m_ui->setupUi(this);
    initMessageType(msgType, msgText);
    fillBtnList(boxType);
    initButtonBox();
}

PopupDialog::PopupDialog(QWidget* parent, bool* bResult,
        const PopupMessageType& msgType, const std::string& msgText)
    : QDialog(parent)
    , m_ui(new Ui::PopupDialog)
    , m_bYesNoResult(bResult)
    , m_btnList({})
    , m_closeBtn(nullptr)
    , m_yesBtn(nullptr)
    , m_noBtn(nullptr)
{
    m_ui->setupUi(this);
    initMessageType(msgType, msgText);
    fillBtnList(PopupBoxType::BOX_WITH_YES_NO);
    initButtonBox();
}

PopupDialog::~PopupDialog()
{
    delete m_ui;
    for ( int i = 0; i < m_btnList.size(); ++i )
    {
        delete m_btnList[i];
    }
}

void PopupDialog::AddButton(QPushButton* button)
{
    m_btnList.emplace_back(button);
    m_ui->buttonBox->addWidget(button);
}

void PopupDialog::initMessageType(const PopupMessageType& msgType,
        const std::string& msgText)
{
    switch (msgType)
    {
        case PopupMessageType::INFO:
        {
            setWindowTitle("Information");
            break;
        }
        case PopupMessageType::WARNING:
        {
            setWindowTitle("Warning");
            break;
        }
        case PopupMessageType::ERROR:
        {
            setWindowTitle("Error");
            break;
        }
    }
    m_ui->messageLabel->setText(msgText.c_str());
}

void PopupDialog::fillBtnList(const PopupBoxType& boxType)
{
    switch (boxType)
    {
        case PopupBoxType::BOX_WITH_CLOSE:
            m_closeBtn = new QPushButton(this);
            m_closeBtn->setText("Close");
            connect(m_closeBtn, &QPushButton::clicked, this,
                    &PopupDialog::closeWindow);
            m_btnList.push_back(m_closeBtn);
            break;
        case PopupBoxType::BOX_WITH_YES_NO:
            m_noBtn = new QPushButton(this);
            m_noBtn->setText("No");
            m_yesBtn = new QPushButton(this);
            m_yesBtn->setText("Yes");
            connect(m_noBtn, &QPushButton::clicked, this,
                    &PopupDialog::closeNoWindow);
            connect(m_yesBtn, &QPushButton::clicked, this,
                    &PopupDialog::closeYesWindow);
            m_btnList.push_back(m_noBtn);
            m_btnList.push_back(m_yesBtn);
            break;
    }
}

void PopupDialog::initButtonBox()
{
    for (int i = 0; i < m_btnList.size(); ++i)
    {
        m_ui->buttonBox->addWidget(m_btnList[i]);
    }
}

void PopupDialog::closeWindow()
{
    this->close();
}

void PopupDialog::closeNoWindow()
{
    *m_bYesNoResult = false;
    this->close();
}

void PopupDialog::closeYesWindow()
{
    *m_bYesNoResult = true;
    this->close();
}
