#include "ui/createmeetingdialog.hxx"
#include "ui_createmeetingdialog.h"

CreateMeetingDialog::CreateMeetingDialog(QWidget* parent)
    : QDialog(parent)
    , m_ui(new Ui::CreateMeetingDialog)
{
    m_ui->setupUi(this);
}

CreateMeetingDialog::~CreateMeetingDialog()
{
    delete m_ui;
}
