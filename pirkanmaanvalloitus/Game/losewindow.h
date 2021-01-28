#ifndef LOSEWINDOW_H
#define LOSEWINDOW_H

#include <QDialog>
#include <QApplication>
#include <QProcess>

namespace Ui {
/*
 * Lose window is used to ask the player what to do when game is over
 */
class LoseWindow;
}

class LoseWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoseWindow(QWidget *parent = 0);
    ~LoseWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::LoseWindow *ui;
};

#endif // LOSEWINDOW_H
