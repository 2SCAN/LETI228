#ifndef INFO_H
#define INFO_H

#include <QDialog>

namespace Ui {
class Info;
}

class Info : public QDialog
{
    Q_OBJECT

    struct Information{
        QString firsthelp;
        int width;
        int height;
    };

public:
    explicit Info(QWidget *parent = 0);
    ~Info();
    void writeinformation();
    Information date;

private:
    Ui::Info *ui;
};

#endif // INFO_H
