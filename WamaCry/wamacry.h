#ifndef WAMACRY_H
#define WAMACRY_H

#include <QMainWindow>
#include <QTime>
#include <QDateTime>
#include <qtimer.h>
#include <QDesktopServices>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QSettings>
#include <QMovie>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QCloseEvent>
#include <QSplashScreen>
#include <QPixmap>
//#define DEBUG

namespace Ui {
class WamaCry;
}

class WamaCry : public QMainWindow
{
    Q_OBJECT

public:
    explicit WamaCry(QWidget *parent = 0);
    ~WamaCry();
	void closeEvent(QCloseEvent *event);

private:
    Ui::WamaCry *ui;
    void load_config();
    QString englishdoc;
    QString chinesedoc;
    QDateTime date_end;
    QString picture1path;
    QString picture2path;
    QString musicpath;
	void wallPaper(QString src);

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
