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
    QString text_information = u8"Добро пожаловать в фрактал Мондельброта. Для смены режимов управления используйте клавишы C и V на английской раскладке. В режиме управления мышью масштабирования производится с помощью колесика мыши. В режиме выделения областей необходимо выделить область, чтобы увеличить. С помощью кнопки Z можно вернуться назад. С помощью стрелочек в обоих режимах можно двигать изображение, а с помощью + и - изменять масштаб. Для повторного вызова данного диалога нажмите клавишу I.";
};

#endif // DIALOGINFORMATION_H
