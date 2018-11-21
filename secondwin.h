#ifndef SECONDWIN_H
#define SECONDWIN_H

#include <QDialog>

namespace Ui {
class SecondWin;
}

class SecondWin : public QDialog
{
    Q_OBJECT

public:
    explicit SecondWin(QWidget *parent = 0);
    ~SecondWin();

private:
    Ui::SecondWin *ui;

protected:
    void closeEvent(QCloseEvent *e);
};

#endif // SECONDWIN_H
