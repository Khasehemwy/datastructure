#include "erasepath.h"
#include "Class.h"
#include "ui_erasepath.h"

erasepath::erasepath(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::erasepath)
{
    ui->setupUi(this);
}

erasepath::~erasepath()
{
    delete ui;
}

void erasepath::on_buttonBox_accepted()
{
    cities.removePath(ui->start->text().toStdString(),
                     ui->end->text().toStdString(),
                     ui->method->currentIndex());
}
