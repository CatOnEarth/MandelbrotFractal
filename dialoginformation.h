#ifndef DIALOGINFORMATION_H
#define DIALOGINFORMATION_H

#include <QDialog>

/** Namespace for user interface dialog */
namespace Ui {
class DialogInformation;
}

/** Dialog info */
class DialogInformation : public QDialog {
    Q_OBJECT

public:
    explicit DialogInformation(QWidget *parent = nullptr);
    ~DialogInformation();

private:
    Ui::DialogInformation *ui;
    /** Text to dialog window */
    QString text_information = u8"����� ���������� � ������� ������������. ��� ����� ������� ���������� ����������� ������� C � V �� ���������� ���������. � ������ ���������� ����� ��������������� ������������ � ������� �������� ����. � ������ ��������� �������� ���������� �������� �������, ����� ���������. � ������� ������ Z ����� ��������� �����. � ������� ��������� � ����� ������� ����� ������� �����������, � � ������� + � - �������� �������. ��� ���������� ������ ������� ������� ������� ������� I.";
};

#endif // DIALOGINFORMATION_H
