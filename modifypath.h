#ifndef MODIFYPATH_H
#define MODIFYPATH_H

#include <QDialog>

namespace Ui {
class modifypath;
}

class modifypath : public QDialog
{
    Q_OBJECT

public:
    explicit modifypath(QWidget *parent = nullptr);
    ~modifypath();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::modifypath *ui;
};

#endif // MODIFYPATH_H
