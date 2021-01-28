#include "losewindow.h"
#include "ui_losewindow.h"

LoseWindow::LoseWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoseWindow)
{
    ui->setupUi(this);
    setWindowTitle("Game Over!");
}

LoseWindow::~LoseWindow()
{
    delete ui;
}

void LoseWindow::on_pushButton_2_clicked() // exit
{
    exit(1);
}

void LoseWindow::on_pushButton_clicked() // retry
{
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}
