#include "wamacry.h"
#include "ui_wamacry.h"
#include <qtimer.h>
#include <QDesktopServices>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QSettings>
#include <QMovie>

WamaCry::WamaCry(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WamaCry)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
    setFixedSize(this->width(), this->height());

    load_config();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer->start(1000);

    showTime();
}

WamaCry::~WamaCry()
{
    delete ui;
}

void WamaCry::showTime()
{
    load_config();

    QTime timenow = QTime::currentTime();
    QTime time_end = QTime::fromString(QString("23:59"),"hh:mm");
    QTime time_left = QTime::fromMSecsSinceStartOfDay(timenow.msecsTo(time_end));
    QString text = time_left.toString("hh:mm:ss");
    ui->lcdNumber->display(text);

    QDateTime datenow = QDateTime::currentDateTime();
    ui->end_of_world->setText(date_end.toString("yyyy-M-d:hh:mm"));
    int days_left = datenow.secsTo(date_end)/3600/24;
    int hours_left = (datenow.secsTo(date_end)-days_left*24*3600)/3600;
    int mins_left = (datenow.secsTo(date_end)-days_left*24*3600-hours_left*3600)/60;
    // int secs_left = datenow.secsTo(date_end)%60;
    QString text2;
    text2 = QString::number(days_left) + "d:" + QString::number(hours_left) + ":" + QString::number(mins_left);
    ui->lcdNumber_2->display(text2);
}

void WamaCry::on_link1_clicked()
{
    QDesktopServices::openUrl(QUrl("https://bitcoin.org/en/"));
}

void WamaCry::on_link2_clicked()
{
    QDesktopServices::openUrl(QUrl("https://bitcoin.org/en/exchanges"));
}

void WamaCry::on_link3_clicked()
{
    QDesktopServices::openUrl(QUrl("https://github.com/bitdust/WamaCry/issues/1"));
}

void WamaCry::on_button1_clicked()
{
    QMessageBox msg;
    msg.setText("Error!");
    msg.exec();
}

void WamaCry::on_button2_clicked()
{
    QMessageBox msg;
    msg.setText("Service unavailable");
    msg.exec();
}

void WamaCry::on_button3_clicked()
{
    QMessageBox msg;
    msg.setText("Service unavailable");
    msg.exec();
}

void WamaCry::on_comboBox_currentIndexChanged(int index)
{
    if(index == 0)
    {
        ui->textBrowser->setText(englishdoc);
    }
    else
    {
        ui->textBrowser->setText(chinesedoc);
    }
}

void WamaCry::load_config()
{
    // read settings
    QSettings settings(QCoreApplication::applicationDirPath() + "/mod/config.ini", QSettings::IniFormat);
    settings.setIniCodec("UTF8");
    this->setStyleSheet(QString("background-color: ")+settings.value("config/bgcolor").toString());
    ui->title->setText(settings.value("config/title").toString());
    ui->title->setStyleSheet(QString("color: ")+settings.value("config/titlecolor").toString());
    ui->countdown1->setText(settings.value("config/countdown1").toString());
    ui->countdown2->setText(settings.value("config/countdown2").toString());
    ui->countdown3->setText(settings.value("config/countdown3").toString());
    ui->countdown4->setText(settings.value("config/countdown4").toString());
    ui->text->setText(settings.value("config/text").toString());
    ui->countdown1->setStyleSheet(QString("color: ")+settings.value("config/txtcolor").toString());
    ui->countdown2->setStyleSheet(QString("color: ")+settings.value("config/txtcolor").toString());
    ui->countdown3->setStyleSheet(QString("color: ")+settings.value("config/txtcolor").toString());
    ui->countdown4->setStyleSheet(QString("color: ")+settings.value("config/txtcolor").toString());
    ui->text->setStyleSheet(QString("color: ")+settings.value("config/txtcolor").toString());
    ui->address->setText(settings.value("config/address").toString());
    ui->button1->setText(settings.value("config/button1").toString());
    ui->button2->setText(settings.value("config/button2").toString());
    ui->button3->setText(settings.value("config/button3").toString());
    ui->link1->setText(settings.value("config/link1").toString());
    ui->link2->setText(settings.value("config/link2").toString());
    ui->link3->setText(settings.value("config/link3").toString());

    if (settings.value("config/picture1").toString() != picture1path)
    {
        picture1path = settings.value("config/picture1").toString();
        if (settings.value("config/picture1").toString().contains(QString(".gif")))
        {
            QMovie *movie1 = new QMovie(QCoreApplication::applicationDirPath() + picture1path);
            ui->picture1->setMovie(movie1);
            movie1->start();
        }
        else
        {
            ui->picture1->setPixmap(QPixmap(QCoreApplication::applicationDirPath() + picture1path));
        }
    }

    if (settings.value("config/picture2").toString() != picture2path)
    {
        picture2path = settings.value("config/picture2").toString();
        if (settings.value("config/picture2").toString().contains(QString(".gif")))
        {
            QMovie *movie2 = new QMovie(QCoreApplication::applicationDirPath() + picture1path);
            ui->picture2->setMovie(movie2);
            movie2->start();
        }
        else
        {
            ui->picture2->setPixmap(QPixmap(QCoreApplication::applicationDirPath() + picture2path));
        }
    }

    QFile file1(QCoreApplication::applicationDirPath() + settings.value("config/englishhtml").toString());
    QTextStream in1(&file1);
    in1.setCodec("UTF-8");
    file1.open(QIODevice::ReadOnly | QIODevice::Text);
    englishdoc = in1.readAll();
    file1.close();

    QFile file2(QCoreApplication::applicationDirPath() + settings.value("config/chinesehtml").toString());
    QTextStream in2(&file2);
    in2.setCodec("UTF-8");
    file2.open(QIODevice::ReadOnly | QIODevice::Text);
    chinesedoc = in2.readAll();
    file2.close();

    ui->picture1->setScaledContents( true );
    ui->picture2->setScaledContents( true );

    date_end = QDateTime::fromString(QString(settings.value("config/enddate").toString()), "yyyy:M:d");
}
