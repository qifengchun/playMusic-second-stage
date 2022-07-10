#ifndef LYRIC_H
#define LYRIC_H

#include <QObject>
#include <QVector>
class Lyric: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString lyrics READ lyrics WRITE setLyrics NOTIFY lyricsChanged)//从搜索中获得的一首歌的所有歌词（包括时间戳）
    Q_PROPERTY(QVector<QString> time READ time WRITE setTime NOTIFY timeChanged)//存放提取出来的时间戳
    Q_PROPERTY(QVector<QString> plainLyric READ plainLyric WRITE setPlainLyric NOTIFY plainLyricChanged)//存放每一行的歌词（没有时间戳的)

public:
    explicit Lyric();
    Q_INVOKABLE void parseLyric();//解析歌词
    bool isNum(char *ch);

    QString lyrics() const{
        return m_lyrics;
    }

    QVector<QString> time() const{
        return m_time;
    }

    QVector<QString> plainLyric() const{
        return m_plainLyric;
    }
public slots:
    void setLyrics(QString lyrics)
    {
        m_lyrics = lyrics;
        emit lyricsChanged(m_lyrics);
    }

    void setTime(QVector<QString> time)
    {
        if (m_time == time)
            return;

        m_time = time;
        emit timeChanged(m_time);
    }

    void setPlainLyric(QVector<QString> plainLyric)
    {
        if (m_plainLyric == plainLyric)
            return;

        m_plainLyric = plainLyric;
        emit plainLyricChanged(m_plainLyric);
    }
signals:
    void lyricsChanged(QString lyric);
    void timeChanged(QVector<QString> time);
    void plainLyricChanged(QVector<QString> plainLyric);
private:
    //bool isNum(char *ch);
    QString m_lyrics;//一首歌的所有歌词（包括时间戳）
    QVector<QString> m_time;//存放的时间
    QVector<QString> m_plainLyric;//存放每一行歌词（没有时间的）

};

#endif // LYRIC_H
