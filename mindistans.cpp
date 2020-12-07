#include "mindistans.h"
#include "mindist.h"
#include "ui_mindistans.h"
#include <string>

mindistans::mindistans(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mindistans)
{
    ui->setupUi(this);
    std::string str="";
    if(mdans.size()==0) str="Not exist";
    else {
        for(int i=mdans.size()-1;i>=0;i--) {
            str+=(mdans[i]);
            if(i!=0) str+="->";
        }
    }
    ui->label->setText(QString::fromStdString(str));
}

mindistans::~mindistans()
{
    delete ui;
}
