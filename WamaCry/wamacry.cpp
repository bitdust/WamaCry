#include "wamacry.h"
#include "ui_wamacry.h"
#include <qtimer.h>
#include <QTime>
#include <QDateTime>
#include <QDesktopServices>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QSettings>

WamaCry::WamaCry(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WamaCry)
{
    ui->setupUi(this);

    // read settings
    QSettings settings("./mod/config.ini", QSettings::IniFormat);
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
    ui->picture1->setPixmap(QPixmap(settings.value("config/picture1").toString()));
    ui->picture2->setPixmap(QPixmap(settings.value("config/picture2").toString()));

    QFile file(settings.value("config/englishhtml").toString());
    QTextStream in(&file);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    ui->textBrowser->setText(in.readAll());

    ui->picture1->setScaledContents( true );
    ui->picture2->setScaledContents( true );

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
    QTime timenow = QTime::currentTime();
    QTime time_end = QTime::fromString(QString("23:59"),"hh:mm");
    QTime time_left = QTime::fromMSecsSinceStartOfDay(timenow.msecsTo(time_end));
    QString text = time_left.toString("hh:mm:ss");
    ui->lcdNumber->display(text);

    QDateTime datenow = QDateTime::currentDateTime();
    QDateTime date_end = QDateTime::fromString(QString("2017:6:3"), "yyyy:M:d");
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
        QSettings settings("./mod/config.ini", QSettings::IniFormat);
        settings.setIniCodec("UTF8");
        QFile file(settings.value("config/englishhtml").toString());
        QTextStream in(&file);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        ui->textBrowser->setText(in.readAll());
    }
    else
    {
        QSettings settings("./mod/config.ini", QSettings::IniFormat);
        settings.setIniCodec("UTF8");
        QFile file(settings.value("config/chinesehtml").toString());
        QTextStream in(&file);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        ui->textBrowser->setText(in.readAll());
    }
}
