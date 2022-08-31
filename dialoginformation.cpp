#include "dialoginformation.h"
#include "ui_dialoginformation.h"

DialogInformation::DialogInformation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogInformation)
{
    ui->setupUi(this);
    ui->label_text_info->setWordWrap(true);
    ui->label_text_info->setText(text_information);
}

DialogInformation::~DialogInformation()
{
    delete ui;
}
