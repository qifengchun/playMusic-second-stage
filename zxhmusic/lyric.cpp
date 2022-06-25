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
        char *ch=ba.data();//将QByteArray类型转为Qchar类型
        if(isNumber(ch)){
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
        ba=content.mid(pos+1,1).toLatin1();
        ch=ba.data();
        int i=0;
        if(content.mid(pos,1)=="["&& isNumber(ch)){
            start=pos;
            while(content.mid(pos,1)!="]"){
                pos++;
                i++;
            }
            pos++;
            int duration=0;
            if(content.midRef(start+1,i-1).length()==8){//还在查找资料
                m_lyricFlag=true;
                duration=translate(content.mid(start+1,i-1));
            }
            else{
                m_lyricFlag=false;
                duration=translate1(content.mid(start+1,i-1));
            }
            m_timeStamp<<duration;
        }
        else{
            pos++;
        }
    }
    sort();
    //将排序后的每个时间转化为时间戳格式，然后找到其对应的歌词并将其歌词存放到m_plainLyric数组中
    for(int i=0;i<m_timeStamp.length();i++){
        QString time;
        if(m_lyricFlag){
            time=translateStamp(m_timeStamp[i]);
        }
        else{
            time=translateStamp1(m_timeStamp[1]);
        }
        //测试
        m_plainLyric<<content.mid(m_highlightPos,m_highlightLength);
    }
    QList<QString>::const_iterator constIterator;
}

int Lyric::findTimeInterval(QString nowTime){
    //先把这个时间戳转化为毫秒，然后在时间戳数组中找到第一个比他大的时间，两个时间相减得到时间差，返回给qml
    QString nowTime1=nowTime.mid(1,5);
    int time=translate1(nowTime1);
    int interval=0,index=0;
    QList<int>::const_iterator constIterator;
    for(constIterator=m_timeStamp.constBegin();constIterator!=m_timeStamp.constEnd();++constIterator){
        if(time<=(*constIterator)){
            interval=(*constIterator)-time;
            break;
        }
        index++;
    }
    m_timeDif=interval;
    return index;
}

QString Lyric::translateStamp(int value){

}
