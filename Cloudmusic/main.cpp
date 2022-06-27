//qfcv
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "song.h"
#include "kugousong.h"
#include "kugoumv.h"
#include "lyric.h"
#include "lyricline.h"
#include "lyricdownload.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<Song,1>("Song",1,0,"Song");
    qmlRegisterType<KuGouSong,1>("KuGouSong",1,0,"KuGouSong");
    qmlRegisterType<KuGouMv, 1>("KuGouMv", 1, 0, "KuGouMv");
    //qmlRegisterType<KuGouPlayList, 1>("KuGouPlayList", 1, 0, "KuGouPlayList");
//    qmlRegisterType<Lyric,1>("Lyric",1,0,"Lyric");
    qmlRegisterType<LyricLine,1>("LyricLine",1,0,"LyricLine");
    qmlRegisterType<LyricDownload,1>("LyricDownload",1,0,"LyricDownload");

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
