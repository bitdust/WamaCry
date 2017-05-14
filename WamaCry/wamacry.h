#ifndef WAMACRY_H
#define WAMACRY_H

#include <QMainWindow>

namespace Ui {
class WamaCry;
}

class WamaCry : public QMainWindow
{
    Q_OBJECT

public:
    explicit WamaCry(QWidget *parent = 0);
    ~WamaCry();

private:
    Ui::WamaCry *ui;

private slots:
    void showTime();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_comboBox_currentIndexChanged(int index);
};

#endif // WAMACRY_H
