//qfcv
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "song.h"
#include "kugousong.h"
#include "lyric.h"
#include "lyricline.h"
#include "lyricdownload.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<Song,1>("Song",1,0,"Song");
    qmlRegisterType<KuGouSong,1>("KuGouSong",1,0,"KuGouSong");
    qmlRegisterType<Lyric,1>("Lyric",1,0,"Lyric");
    qmlRegisterType<LyricLine,1>("LyricLine",1,0,"LyricLine");
    qmlRegisterType<LyricDownload,1>("LyricDownload",1,0,"LyricDownload");

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/CloudMusic/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
