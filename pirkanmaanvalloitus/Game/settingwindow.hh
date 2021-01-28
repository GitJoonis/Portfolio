#ifndef SETTINGWINDOW_HH
#define SETTINGWINDOW_HH

#include <QDialog>

namespace Ui {
class Settingwindow;
}
/*
 * \brief The Settingwindow class is used to ask the player information before executing the mainwindow
 */
class Settingwindow : public QDialog
{
    Q_OBJECT

public:
    explicit Settingwindow(QWidget *parent = 0);
    ~Settingwindow();

private:
    Ui::Settingwindow *ui;
    std::string map_size_ = "Small";
    std::string name_ = "Player";

signals:
    void sendSettings(std::string map_size, std::string name);
    void quit();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_comboBox_currentTextChanged(const QString &arg1);
    void on_lineEdit_textChanged(const QString &arg1);
};

#endif // SETTINGWINDOW_HH
