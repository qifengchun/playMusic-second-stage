#ifndef LYRICLINE_H
#define LYRICLINE_H

#include <QList>

class LyricLine{
public:
    LyricLine();
    void parseKrcLyric();//解析歌词
    void setLyricLine(QString lyric){m_lineLyric=lyric;}
    QString lyricLine(){return m_lineLyric;}
    int startTime(){return m_startTime;}
    int lineDuration(){return m_lineDuration;}
    QList<int> wordDuration() {return m_wordDuration;}
    QString plainLyric() {return m_plainLyric;}
private:
    QString m_lineLyric;//每行的歌词
    int m_startTime;//每行开始的时间
    int m_lineDuration;//每行持续的时间
    QList<int> m_wordDuration;//每行歌词中每个字的持续时间
    QString m_plainLyric;//每行纯歌词
};

#endif // LYRICLINE_H
