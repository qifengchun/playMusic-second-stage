#include "lyric.h"
#include <QtDebug>
#include <QByteArray>

Lyric::Lyric(QObject *parent):QObject(parent),m_highlightPos{0},m_highlightLength{0},m_timeDif{0}
{

}

//增加标签，例如[00:00.00]
QString Lyric::addTag(QString content,int pos,QString str){
    pos=topOfLine(content,pos);//将光标移到当前行的首位
    content.insert(pos,str);//将str插入到给定的索引位置，并返回对该字符串的引用
    return content;
}

//删除行内首标签
QString Lyric::deleteHeaderLabel(QString content,int pos){
    pos=topOfLine(content,pos);
    QByteArray ba=content.mid(pos+1,1).toLatin1();//将QString类型转为QByteArray类型
    char *s=ba.data();//将QByteArray类型转为Qchar类型
    int i=0;
    if(content.mid(pos,1)=="["&& isNumber(s)){
        int start=pos;
        while(content.mid(pos,1)!="]"){
            pos++;
            i++;
        }
        content.remove(start,i+1);
    }
    return content;

}

//删除行内所有标签
QString Lyric::deleteAllLabel(QString content,int pos){
    pos=topOfLine(content,pos);
    while(content.mid(pos,1)=="["){
        QByteArray ba=content.mid(pos+1,1).toLatin1();//将QString类型转为QByteArray类型
        char *s=ba.data();//将QByteArray类型转为Qchar类型
        if(isNumber(s)){
            int start=pos,i=0;
            while(content.mid(pos,1)!="]"){
                pos++;
                i++;
            }
            content.remove(start,i+1);
            pos=start;
        }
    }
    return content;
}

//测试歌词

//提取时间戳
void Lyric::extract_timeStamp(){
    m_timeStamp.clear();
    m_plainLyric.clear();
    QString content=m_lyric;
    int pos=0;
    int start=0;
    QByteArray ba;
    char *ch;
    while(pos<=content.length()){

    }
}
