#ifndef WINWINDOW_H
#define WINWINDOW_H

#include <QDialog>
#include <QApplication>
#include <QProcess>


namespace Ui {
class WinWindow;
}
/*
 * \brief The WinWindow class is used to give information and ask the player what to do after game is won
 */
class WinWindow : public QDialog
{
    Q_OBJECT

public:
    explicit WinWindow(QWidget *parent = 0);
    ~WinWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::WinWindow *ui;
};

#endif // WINWINDOW_H
