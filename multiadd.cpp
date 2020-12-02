#include "multiadd.h"
#include "ui_multiadd.h"

multiadd::multiadd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::multiadd)
{
    ui->setupUi(this);
}

multiadd::~multiadd()
{
    delete ui;
}
