#include "settingwindow.hh"
#include "ui_settingwindow.h"
#include <QDebug>

Settingwindow::Settingwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settingwindow)
{
    ui->setupUi(this);
    QStringList sizes = {"Small", "Medium"};
    ui->comboBox->addItems(sizes);
}

Settingwindow::~Settingwindow()
{
    delete ui;
}


void Settingwindow::on_pushButton_clicked()
{
    emit sendSettings(map_size_, name_);
    Settingwindow::accept();
}

void Settingwindow::on_pushButton_2_clicked()
{
    this->reject();
    exit(1);
}



void Settingwindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    map_size_ = arg1.toStdString();
}


void Settingwindow::on_lineEdit_textChanged(const QString &arg1)
{
    name_ = arg1.toStdString();
}
