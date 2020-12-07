#include "mincostans.h"
#include "mincost.h"
#include "ui_mincostans.h"
#include <string>

mincostans::mincostans(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mincostans)
{
    ui->setupUi(this);
    std::string str="";
    if(mans.size()==0) str="Not exist";
    else {
        for(int i=mans.size()-1;i>=0;i--) {
            str+=(mans[i]);
            if(i!=0) str+="->";
        }
    }
    ui->label->setText(QString::fromStdString(str));
}

mincostans::~mincostans()
{
    delete ui;
}
