#include "wamacry.h"
#include "mwindows.h"
#include <QApplication>
#include <QFont>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	qDebug() << QCoreApplication::applicationDirPath();

	QPixmap mPixmap(QCoreApplication::applicationDirPath()+"/mod/picture2.png");
	QSplashScreen screen(mPixmap);

	QFont sansFont("Helvetica [Cronyx]", 80);
	screen.setFont(sansFont);

	screen.show();
	screen.showMessage(QObject::tr("正在打开445端口..."), Qt::AlignCenter, Qt::black);
	Sleep(1000);
	screen.showMessage(QObject::tr("正在卸载MS-17-101补丁..."), Qt::AlignCenter, Qt::black);
	Sleep(1500);
	screen.showMessage(QObject::tr("正在建立目录索引..."), Qt::AlignCenter, Qt::black);
	Sleep(1000);
	screen.showMessage(QObject::tr("正在生成秘钥..."), Qt::AlignCenter, Qt::black);
	Sleep(1000);


	screen.close();

	WamaCry w;
#ifndef DEBUG
	w.setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
#endif
	w.show();

    return a.exec();
}
