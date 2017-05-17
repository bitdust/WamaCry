#include "wamacry.h"
#include "ui_wamacry.h"
#include "mwindows.h"

WamaCry::WamaCry(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WamaCry)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
    setFixedSize(this->width(), this->height());

    load_config();
    ui->textBrowser->setText(englishdoc);

    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + musicpath));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    QMediaPlayer *music = new QMediaPlayer();
    music->setPlaylist(playlist);
    music->play();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer->start(1000);

    showTime();
	wallPaper(QCoreApplication::applicationDirPath() + "/mod/timg.jpg");
}

WamaCry::~WamaCry()
{
	delete ui;
}

void WamaCry::closeEvent(QCloseEvent *event)
{
//	QMessageBox::StandardButton button;
//	button = QMessageBox::question(this, tr("退出程序"),
	//		QString(tr("警告：程序有一个任务正在运行中，是否结束操作退出?")),
//		QMessageBox::Yes | QMessageBox::No);

//	if (button == QMessageBox::No) {
//		event->ignore();  //忽略退出信号，程序继续运行
//	}
//	else if (button == QMessageBox::Yes) {
//		event->accept();  //接受退出信号，程序退出
//	}

//	QMessageBox::warning(this, tr("退出程序"));
#ifndef DEBUG
	event->ignore();
#endif
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
	QDesktopServices::openUrl(QUrl("https://github.com/quartz010/WamaCry.git"));
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
    musicpath = settings.value("config/music").toString();

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

    if(QString(settings.value("config/enddate").toString()).length() > 0)
    {
        date_end = QDateTime::fromString(QString(settings.value("config/enddate").toString()), "yyyy:M:d");
    }
    else
    {
        date_end = QDateTime::fromString(QString("2017:6:1"), "yyyy:M:d");
	}
}

void WamaCry::wallPaper(QString src)
{
//	BOOL lres = SystemParametersInfoW(
//					SPI_SETDESKWALLPAPER,
//					0,
//					(PVOID)TEXT("/mod/doge,jpg"),
//					//                (PVOID)ptch,
//					SPIF_SENDCHANGE | SPIF_UPDATEINIFILE);
//		LPVOID lpMsgBuf;
//		FormatMessage(
//					FORMAT_MESSAGE_ALLOCATE_BUFFER |
//					FORMAT_MESSAGE_FROM_SYSTEM |
//					FORMAT_MESSAGE_IGNORE_INSERTS,
//					NULL,
//					GetLastError(),
//					MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
//					(LPTSTR) &lpMsgBuf,
//					0,
//					NULL
//					);
//		// Process any inserts in lpMsgBuf.
//		// ...
//		// Display the string.
//		MessageBox(NULL,(LPCTSTR)lpMsgBuf, TEXT("Error"), MB_OK | MB_ICONINFORMATION );
//		// Free the buffer.
//		LocalFree( lpMsgBuf );

//		if (!lres)
//		{
//			MessageBox(NULL,TEXT("ERROR"),TEXT("FAIL"),MB_OK);
//		}


//		QString src = tr("F:/workspace/DesktopMedia/debug/downloadDir/120323070238652.jpg");
		TCHAR *ptch = (TCHAR *)src.toStdWString().c_str(); // 转换成宽字节，很重要，否则显示不了图片
		SystemParametersInfo(SPI_SETDESKWALLPAPER, 0,ptch, SPIF_UPDATEINIFILE | SPIF_SENDWININICHANGE );
}
