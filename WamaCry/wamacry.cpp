#include "wamacry.h"
#include "ui_wamacry.h"
#include <qtimer.h>
#include <QTime>
#include <QDateTime>
#include <QDesktopServices>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

WamaCry::WamaCry(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WamaCry)
{
    ui->setupUi(this);
    ui->label_3->setPixmap(QPixmap(":/gesloten-slot.png"));
    ui->label_3->setScaledContents( true );
    //ui->label_3->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    ui->label_4->setPixmap(QPixmap(":/Bitcoin_accepted_here_printable.png"));
    ui->label_4->setScaledContents( true );
    //ui->label_4->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );

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

void WamaCry::on_pushButton_4_clicked()
{
    QDesktopServices::openUrl(QUrl("https://bitcoin.org/en/"));
}

void WamaCry::on_pushButton_5_clicked()
{
    QDesktopServices::openUrl(QUrl("https://bitcoin.org/en/exchanges"));
}

void WamaCry::on_pushButton_6_clicked()
{
    QDesktopServices::openUrl(QUrl("https://github.com/bitdust/WamaCry/issues/1"));
}

void WamaCry::on_pushButton_clicked()
{
    QMessageBox msg;
    msg.setText("Error!");
    msg.exec();
}

void WamaCry::on_pushButton_2_clicked()
{
    QMessageBox msg;
    msg.setText("Service unavailable");
    msg.exec();
}

void WamaCry::on_pushButton_3_clicked()
{
    QMessageBox msg;
    msg.setText("Service unavailable");
    msg.exec();
}

void WamaCry::on_comboBox_currentIndexChanged(int index)
{
    if(index == 0)
    {
        QFile file(":/english.html");
        QTextStream in(&file);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        ui->textBrowser->setText(in.readAll());
    }
    else
    {
        QFile file(":/chinese.html");
        QTextStream in(&file);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        ui->textBrowser->setText(in.readAll());
    }
}
