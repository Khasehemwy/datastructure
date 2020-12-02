#ifndef MULTIADD_H
#define MULTIADD_H

#include <QDialog>

namespace Ui {
class multiadd;
}

class multiadd : public QDialog
{
    Q_OBJECT

public:
    explicit multiadd(QWidget *parent = nullptr);
    ~multiadd();

private:
    Ui::multiadd *ui;
};

#endif // MULTIADD_H
