#ifndef DIALOGINFORMATION_H
#define DIALOGINFORMATION_H

#include <QDialog>

namespace Ui {
class DialogInformation;
}

class DialogInformation : public QDialog
{
    Q_OBJECT

public:
    explicit DialogInformation(QWidget *parent = nullptr);
    ~DialogInformation();

private:
    Ui::DialogInformation *ui;
    QString text_information = u8"����� ���������� � ������� ������������. ��� ����� ������� ���������� ����������� ������� C � V �� ���������� ���������. � ������ ���������� ����� ��������������� ������������ � ������� �������� ����. � ������ ��������� �������� ���������� �������� �������, ����� ���������. � ������� ������ Z ����� ��������� �����. � ������� ��������� � ����� ������� ����� ������� �����������, � � ������� + � - �������� �������. ��� ���������� ������ ������� ������� ������� ������� I.";
};

#endif // DIALOGINFORMATION_H
