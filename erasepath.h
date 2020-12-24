#ifndef ERASEPATH_H
#define ERASEPATH_H

#include <QDialog>

namespace Ui {
class erasepath;
}

class erasepath : public QDialog
{
    Q_OBJECT

public:
    explicit erasepath(QWidget *parent = nullptr);
    ~erasepath();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::erasepath *ui;
};

#endif // ERASEPATH_H
