#include "lyric.h"
#include <QtDebug>
#include <QByteArray>
#include <QVector>
#include <iostream>
using namespace std;
Lyric::Lyric()
{

}

bool Lyric::isNum(char *ch){
    if(ch[0]>='0'&&ch[0]<='9'){
        return true;
    }
    else{
        return false;
    }
}


void Lyric::parseLyric(){
    QString content=m_lyrics;
    //    m_time.clear();
    //    m_plainLyric.clear();
    int pos=0;
    int pos1=0;
    int start=0;
    int len=content.length();
    QByteArray ba;
    char *ch;
    //整体走向
    while(pos<=len){
        ba=content.mid(pos+1,1).toLatin1();
        ch=ba.data();
        int i=0;
        //存
        if(content.mid(pos,1)=="[" && isNum(ch)){
            start=pos;
            //找时间
            while(content.mid(pos,1)!="]"){
                pos++;
                i++;
            }
            pos++;
            QString duration=content.mid(start+1,i-1);

            m_time.push_back(duration);
            pos1=pos;//歌词开始的位置
            while(!(content.mid(pos,1)=='\r' && content.mid(pos+1,1)=='\n')){
                pos++;
            }
            m_plainLyric.push_back(content.mid(pos1,pos-pos1));
          }

        else{
            pos++;
        }
    }
}
