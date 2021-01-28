#include "winwindow.h"
#include "ui_winwindow.h"

WinWindow::WinWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WinWindow)
{
    ui->setupUi(this);
    setWindowTitle("Victory");
}

WinWindow::~WinWindow()
{
    delete ui;
}

void WinWindow::on_pushButton_clicked() // continue
{
    this->reject();
}

void WinWindow::on_pushButton_2_clicked() // exit
{
    exit(1);
}

void WinWindow::on_pushButton_3_clicked() //restart
{
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}
