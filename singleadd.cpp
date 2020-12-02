#include "singleadd.h"
#include "Class.h"
#include "ui_singleadd.h"

singleadd::singleadd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::singleadd)
{
    ui->setupUi(this);
}

singleadd::~singleadd()
{
    delete ui;
}

void singleadd::on_buttonBox_accepted()
{
    citys.addCity(ui->name->text().toStdString());
}
