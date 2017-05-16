#ifndef WAMACRY_H
#define WAMACRY_H

#include <QMainWindow>
#include <QTime>
#include <QDateTime>

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
    void load_config();
    QString englishdoc;
    QString chinesedoc;
    QDateTime date_end;

private slots:
    void showTime();
    void on_link1_clicked();
    void on_link2_clicked();
    void on_link3_clicked();
    void on_button1_clicked();
    void on_button2_clicked();
    void on_button3_clicked();
    void on_comboBox_currentIndexChanged(int index);


};

#endif // WAMACRY_H
