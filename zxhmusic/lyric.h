#ifndef LYRIC_H
#define LYRIC_H

#include <QObject>
#include <QDebug>
#include <QList>

class Lyric:public QObject{
    Q_OBJECT
    Q_PROPERTY(int highlightPos READ highlightPos WRITE sethighlightPos NOTIFY highlightPosChanged)
    Q_PROPERTY(int highlightLength READ highlightLength WRITE sethighlightLength NOTIFY highlightLengthChanged)
    Q_PROPERTY(int lyric READ lyric WRITE lyric NOTIFY lyricChanged)
    Q_PROPERTY(int timeStamp READ timeStamp WRITE timeStamp NOTIFY timeStampChanged)//时间戳
    Q_PROPERTY(int plainLyric READ plainLyric WRITE plainLyric NOTIFY plainLyricChanged)
    Q_PROPERTY(int timeDif READ timeDif WRITE timeDif NOTIFY timeDifChanged)//时间差
public:
    explicit Lyric(QObject *parent=nullptr);

    //Q_INVOKABLE宏定义了函数在元对象中可以进行调用，这个宏要写到返回值的前面
    Q_INVOKABLE QString addTag(QString content,int pos,QString str);
    Q_INVOKABLE QString deleteHeaderLabel(QString content,int pos);
    Q_INVOKABLE QString deleteAllLabel(QString content,int pos);
    Q_INVOKABLE void test(QString time);//测试
    Q_INVOKABLE void extract_timeStamp();//提取时间戳
    Q_INVOKABLE int findTimeInterval(QString nowTime);//找到时间间隔
    Q_INVOKABLE QString translateStamp(int time);//将时间戳转换为毫秒 00：00.00
    Q_INVOKABLE QString translateStamp1(int time);
    Q_INVOKABLE bool lyricFlag(){return m_lyricFlag;}

    int translate(QString time);//将时间戳转换为毫秒 00：00.00
    int translate1(QString time);//将时间戳转换为毫秒 00：00
    void sort();//将转换后的时间戳数组按升序排列
    int highlightPos() const{
        return m_highlightPos;
    }
private:
    int topOfLine(QString content,int pos);
    bool isNumber(char *ch);
    bool isEqual(QString str1,QString str2);

    QString m_lyric;
    QList<int> m_timeStamp;//存放化为毫秒的时间戳
    int m_highlightPos;
    int m_highlightLength;
    int m_timeDif;//时间差
    QList<QString> m_plainLyric;
    bool m_lyricFlag;
};

#endif // LYRIC_H
