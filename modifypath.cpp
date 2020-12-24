#include "modifypath.h"
#include "Class.h"
#include "ui_modifypath.h"

modifypath::modifypath(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modifypath)
{
    ui->setupUi(this);
}

modifypath::~modifypath()
{
    delete ui;
}

void modifypath::on_buttonBox_accepted()
{
    cities.revisePath(ui->start->text().toStdString(),
                      ui->end->text().toStdString(),
                      ui->method->currentIndex(),
                      ui->dist->text().toDouble(),
                      ui->cost->text().toDouble(),
                      ui->time->text().toDouble());
}
