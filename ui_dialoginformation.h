/********************************************************************************
** Form generated from reading UI file 'dialoginformation.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGINFORMATION_H
#define UI_DIALOGINFORMATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_DialogInformation
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label_text_info;

    void setupUi(QDialog *DialogInformation)
    {
        if (DialogInformation->objectName().isEmpty())
            DialogInformation->setObjectName(QString::fromUtf8("DialogInformation"));
        DialogInformation->resize(632, 565);
        buttonBox = new QDialogButtonBox(DialogInformation);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(260, 520, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label_text_info = new QLabel(DialogInformation);
        label_text_info->setObjectName(QString::fromUtf8("label_text_info"));
        label_text_info->setGeometry(QRect(20, 20, 581, 481));
        QFont font;
        font.setFamily(QString::fromUtf8("Times New Roman"));
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        label_text_info->setFont(font);

        retranslateUi(DialogInformation);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogInformation, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogInformation, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogInformation);
    } // setupUi

    void retranslateUi(QDialog *DialogInformation)
    {
        DialogInformation->setWindowTitle(QCoreApplication::translate("DialogInformation", "Dialog", nullptr));
        label_text_info->setText(QCoreApplication::translate("DialogInformation", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogInformation: public Ui_DialogInformation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGINFORMATION_H
