//由qfc完成的搜索模块
#ifndef KUGOUSONG_H
#define KUGOUSONG_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QList>

class KuGouSong:public QObject
{
    Q_OBJECT

    //属性名称和类型以及读取函数是必需的。类型可以是QVariant支持的任何类型，也可以是用户定义的类型。其他项目是可选的，但写入功能很常见。属性默认为true，但USER除外，后者默认为false。
    Q_PROPERTY(QList<QString> singerName READ singerName WRITE setSingerName NOTIFY singerNameChanged)//歌手名字
    Q_PROPERTY(QList<QString> songName READ songName WRITE setSongName NOTIFY songNameChanged)//歌曲名
    Q_PROPERTY(QList<QString> albumName READ albumName WRITE setAlbumName NOTIFY albumNameChanged)//专辑名
    Q_PROPERTY(QList<double> duration READ duration WRITE setDuration NOTIFY durationChanged)//歌曲时长
    Q_PROPERTY(QString lyrics READ lyrics WRITE setLyrics NOTIFY lyricsChanged)//歌词
    Q_PROPERTY(QString image READ image WRITE setImage NOTIFY imageChanged)//图片
    Q_PROPERTY(QString url READ url WRITE setUrl NOTIFY urlChanged)//网址路径

public:
    explicit KuGouSong(QObject *parent=nullptr);
    //此宏用于在继承QObject的类中声明属性。属性的行为类似于类数据成员，但它们具有可通过元对象系统访问的其他功能。
    Q_INVOKABLE void searchSong(QString str);//搜索歌曲
    void parseJson_getAlbumID(QString json);//专辑
    void parseJson_getPlayUrl(QString json);//网址
    Q_INVOKABLE void getSongUrl(int index);//下载的地址
    Q_INVOKABLE void downloadSong(int index,QString path);//下载歌曲
    void clear();

    void sethashStr(QList<QString> hash) {
        if (hash == hashStr)
            return;
        hashStr=hash;
    }

    void setAlbum_idStr(QList<long> album) {
        QList<QString> album_id;
        for(int i=0;i<album.length();i++) {
            album_id<<QString::number(album[i]);
        }
        if (album_id == album_idStr)
            return;
        album_idStr=album_id;
    }



    QList<QString> singerName() const
    {
        return m_singerName;
    }

    QList<QString> songName() const
    {
        return m_songName;
    }

    QList<QString> albumName() const
    {
        return m_albumName;
    }

    QString url() const
    {
        return m_url;
    }

    QString lyrics() const
    {
        return m_lyrics;
    }



    QList<double> duration() const
    {
        return m_duration;
    }

    QString image() const
    {
        return m_image;
    }

public slots:
    void setSingerName(QList<QString> singerName)
    {
        if (m_singerName == singerName)
            return;

        m_singerName = singerName;
        emit singerNameChanged(m_singerName);//信号
    }

    void setSongName(QList<QString> songName)
    {
        if (m_songName == songName)
            return;

        m_songName = songName;
        emit songNameChanged(m_songName);
    }
//专辑名
    void setAlbumName(QList<QString> albumName)
    {
        if (m_albumName == albumName)
            return;

        m_albumName = albumName;
        emit albumNameChanged(m_albumName);
    }
//网址
    void setUrl(QString url)
    {
        if (m_url == url)
            return;

        m_url = url;
        emit urlChanged(m_url);
    }
//歌词设置
    void setLyrics(QString lyrics)
    {
        if (m_lyrics == lyrics)
            return;

        m_lyrics = lyrics;
        emit lyricsChanged(m_lyrics);
    }
//容器
    void setDuration(QList<double> duration)
    {
        if (m_duration == duration)
            return;

        m_duration = duration;
        emit durationChanged(m_duration);
    }
//专辑图片
    void setImage(QString image)
    {
        if (m_image == image)
            return;

        m_image = image;
        emit imageChanged(m_image);
    }

protected slots:
    //信号回复
    void replyFinished(QNetworkReply *reply);
    void replyFinished2(QNetworkReply*reply);
    void replyFinished3(QNetworkReply *reply);
    void writeUrl();

signals:
    void singerNameChanged(QList<QString> singerName);

    void songNameChanged(QList<QString> songName);

    void albumNameChanged(QList<QString> albumName);

    void urlChanged(QString url);

    void lyricsChanged(QString lyrics);

    void durationChanged(QList<double> duration);

    void imageChanged(QString image);
    void getUrl();
private:
    //处理请求
    QNetworkAccessManager *network_manager;
    QNetworkAccessManager *network_manager2;
    QNetworkAccessManager *network_manager3;
    //发出请求
    QNetworkRequest *network_request;
    QNetworkRequest *network_request2;
    QNetworkRequest *network_request3;

    QList<QString> album_idStr;
    QList<QString> hashStr;
    QList<QString> m_albumName;
    QList<QString> m_songName;
    QList<QString> m_singerName;
    QList<double> m_duration;
    QString m_image;
    QString m_lyrics;
    QString m_url;
    bool isDownloadSong=false;
    QString m_savePath;

};




#endif // KUGOUSONG_H
