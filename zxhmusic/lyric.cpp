//#include "lyric.h"
//#include <QtDebug>
//#include <QByteArray>

//Lyric::Lyric(QObject *parent)
//    :QObject(parent),m_highlightPos{0},m_highlightLength{0},m_timeDif{0}
//{

//}

////增加标签，例如[00:00.00]
//QString Lyric::addTag(QString content,int pos,QString str){
//    pos=topOfLine(content,pos);//将光标移到当前行的首位
//    content.insert(pos,str);//将str插入到给定的索引位置，并返回对该字符串的引用
//    return content;
//}

////删除行内首标签
//QString Lyric::deleteHeaderLabel(QString content,int pos){
//    pos=topOfLine(content,pos);
//    QByteArray ba=content.mid(pos+1,1).toLatin1();//将QString类型转为QByteArray类型
//    char *s=ba.data();//将QByteArray类型转为Qchar类型
//    int i=0;
//    if(content.mid(pos,1)=="["&& isNumber(s)){
//        int start=pos;
//        while(content.mid(pos,1)!="]"){
//            pos++;
//            i++;
//        }
//        content.remove(start,i+1);
//    }
//    return content;

//}

////删除行内所有标签
//QString Lyric::deleteAllLabel(QString content,int pos){
//    pos=topOfLine(content,pos);
//    while(content.mid(pos,1)=="["){
//        QByteArray ba=content.mid(pos+1,1).toLatin1();//将QString类型转为QByteArray类型
//        char *ch=ba.data();//将QByteArray类型转为Qchar类型
//        if(isNumber(ch)){
//            int start=pos,i=0;
//            while(content.mid(pos,1)!="]"){
//                pos++;
//                i++;
//            }
//            content.remove(start,i+1);
//            pos=start;
//        }
//    }
//    return content;
//}

////测试歌词
//void Lyric::test(QString time){
//    QString content=m_lyric;
//    int pos=0,pos1=0;
//    int i;
//    int highlight_num;
//    int highlight_start;//每句歌词的开始位置
//    QString str,highlight;
//    int len=content.length();
//    int start=0;//每个时间标签的开始位置
//    QByteArray ba;
//    char *ch;
//    while(pos<=len){
//        ba=content.mid(pos+1,1).toLatin1();
//        ch=ba.data();
//        i=0;
//        if(content.mid(pos,1)=="["&&isNumber(ch)){
//            start=pos;
//            while(content.mid(pos,1)!="]"){
//                pos++;
//                i++;
//            }
//            pos++;
//            str=content.mid(start,i+1);//提取出每个时间标签
//            if(isEqual(str,time)){
//                pos1=pos;
//                highlight_num=0;
//                highlight_start=pos1;
//                while(content.mid(pos1,1)!="\n"&&content.mid(pos1,1)!="\r"){
//                    if(content.mid(pos1,1)=="["){//判断每个时间标签后面是不是标签
//                        while(content.mid(pos1,1)!="]"){//如果是，就跳过
//                            pos1++;
//                        }
//                        highlight_start=pos1+1;//高亮部分从跳过的标签位置开始
//                    }
//                    else{
//                        highlight_num++;//计算要高亮的字符的个数
//                    }
//                    pos1++;
//                }
//                m_highlightLength=highlight_num;
//                m_highlightPos=highlight_start;
//                highlight=content.mid(highlight_start,highlight_num);
//            }
//        }
//        else{
//            pos++;
//        }
//    }
//}

////提取时间戳
//void Lyric::extract_timeStamp(){
//    m_timeStamp.clear();
//    m_plainLyric.clear();
//    QString content=m_lyric;
//    int pos=0;
//    int start=0;
//    QByteArray ba;
//    char *ch;
//    while(pos<=content.length()){
//        ba=content.mid(pos+1,1).toLatin1();
//        ch=ba.data();
//        int i=0;
//        if(content.mid(pos,1)=="["&& isNumber(ch)){
//            start=pos;
//            while(content.mid(pos,1)!="]"){
//                pos++;
//                i++;
//            }
//            pos++;
//            int duration=0;
//            if(content.mid(start+1,i-1).length()==8){//还在查找资料
//                m_lyricFlag=true;
//                duration=translate(content.mid(start+1,i-1));
//            }
//            else{
//                m_lyricFlag=false;
//                duration=translate1(content.mid(start+1,i-1));
//            }
//            m_timeStamp<<duration;
//        }
//        else{
//            pos++;
//        }
//    }
//    sort();
//    //将排序后的每个时间转化为时间戳格式，然后找到其对应的歌词并将其歌词存放到m_plainLyric数组中
//    for(int i=0;i<m_timeStamp.length();i++){
//        QString time;
//        if(m_lyricFlag){
//            time=translateStamp(m_timeStamp[i]);
//        }
//        else{
//            time=translateStamp1(m_timeStamp[1]);
//        }
//        //测试
//        m_plainLyric<<content.mid(m_highlightPos,m_highlightLength);
//    }
//    QList<QString>::const_iterator constIterator;
//}

//int Lyric::findTimeInterval(QString nowTime){
//    //先把这个时间戳转化为毫秒，然后在时间戳数组中找到第一个比他大的时间，两个时间相减得到时间差，返回给qml
//    QString nowTime1=nowTime.mid(1,5);
//    int time=translate1(nowTime1);
//    int interval=0,index=0;
//    QList<int>::const_iterator constIterator;
//    for(constIterator=m_timeStamp.constBegin();constIterator!=m_timeStamp.constEnd();++constIterator){
//        if(time<=(*constIterator)){
//            interval=(*constIterator)-time;
//            break;
//        }
//        index++;
//    }
//    m_timeDif=interval;
//    return index;
//}

//QString Lyric::translateStamp(int value){
//    QString timeStamp;
//    int m,s,ms;
//    QString m1,s1,ms1;
//    m=(value-value%60000)/60000;
//    s=((value-m*60000)-(value-m*60000)%1000)/1000;
//    ms=((value-m*60000-s*1000)-(value-m*60000-s*1000)%10)/10;
//    if(s>=0&&s<10){
//        if(ms>=10&&ms<100){
//            m1=QString::number(m);
//            s1=QString::number(s);
//            ms1=QString::number(ms);
//            timeStamp="[0"+m1+":0"+s1+"."+ms1+"]";
//        }
//        else{
//            m1=QString::number(m);
//            s1=QString::number(s);
//            ms1=QString::number(ms);
//            timeStamp="[0"+m1+":0"+s1+".0"+ms1+"]";
//        }
//    }
//    else{
//        if(ms>=10&&ms<100){
//            m1=QString::number(m);
//            s1=QString::number(s);
//            ms1=QString::number(ms);
//            timeStamp="[0"+m1+":"+s1+"."+ms1+"]";
//        }
//        else{
//            m1=QString::number(m);
//            s1=QString::number(s);
//            ms1=QString::number(ms);
//            timeStamp="[0"+m1+":"+s1+".0"+ms1+"]";
//        }
//    }
//    return timeStamp;
//}

//QString Lyric::translateStamp1(int value){
//    QString timeStamp;
//    int m,s;
//    QString m1,s1;
//    m=(value-value%60000)/60000;
//    s=((value-m*60000)-(value-m*60000)%1000)/1000;
//    if(s>=0&&s<10){
//        m1=QString::number(m);
//        s1=QString::number(s);
//        timeStamp="[0"+m1+":0"+s1+"]";
//    }
//    else{
//        m1=QString::number(m);
//        s1=QString::number(s);
//        timeStamp="[0"+m1+":"+s1+"]";
//    }
//    return timeStamp;
//}

//void Lyric::sort(){
//    for(int j=0;j<m_timeStamp.length()-1;j++){//外层循环控制排序次数
//        for(int i=0;i<m_timeStamp.length()-1;i++){
//            if(m_timeStamp[i]>m_timeStamp[i+1]){
//                int temp=m_timeStamp[i];
//                m_timeStamp[i]=m_timeStamp[i+1];
//                m_timeStamp[i+1]=temp;
//            }
//        }
//    }
//}

//int Lyric::translate(QString time){
//    int pos=0;
//    int m_ms=0,s_ms=0,ms_ms=0;
//    if(time.mid(pos,1)=="0"&&time.mid(pos+1,1)=="0"){//如果分钟数为0
//        m_ms=0;
//        if(time.mid(pos+3,1)=="0"&&time.mid(pos+4,1)=="0"){//如果秒数为0
//            s_ms=0;
//            if(time.mid(pos+6,1)=="0"&&time.mid(pos+7,1)=="0"){//如果毫秒数为0
//                ms_ms=0;
//                return m_ms+s_ms+ms_ms;
//            }
//            else{
//                ms_ms=time.mid(pos+6,2).toInt()*10;
//                return m_ms+s_ms+ms_ms;
//            }
//        }
//        else{
//            s_ms=time.mid(pos+3,2).toInt()*1000;
//            if(time.mid(pos+6,1)=="0"&&time.mid(pos+7,1)=="0"){
//                ms_ms=0;
//                return m_ms+s_ms+ms_ms;
//            }
//            else{
//                ms_ms=time.mid(pos+6,2).toInt()*10;
//                return m_ms+s_ms+ms_ms;
//            }
//        }
//    }
//    else{
//        m_ms=time.mid(pos,2).toInt()*60000;
//        if(time.mid(pos+3,1)=="0" && time.mid(pos+4,1)=="0") {
//            s_ms=0;
//            if(time.mid(pos+6,1)=="0" && time.mid(pos+7,1)=="0") {
//                ms_ms=0;
//                return m_ms+s_ms+ms_ms;
//            } else {
//                ms_ms=time.mid(pos+6,2).toInt()*10;
//                return m_ms+s_ms+ms_ms;
//            }
//        } else {
//            s_ms=time.mid(pos+3,2).toInt()*1000;
//            if(time.mid(pos+6,1)=="0" && time.mid(pos+7,1)=="0") {
//                ms_ms=0;
//                return m_ms+s_ms+ms_ms;
//            } else {
//                ms_ms=time.mid(pos+6,2).toInt()*10;
//                return m_ms+s_ms+ms_ms;
//            }
//        }
//    }
//}

//int Lyric::translate1(QString time){
//    int pos=0;
//    int m_ms=0,s_ms=0;
//    if(time.mid(pos,1)=="0" && time.mid(pos+1,1)=="0") {  //如果分钟数为0
//        m_ms=0;
//        if(time.mid(pos+3,1)=="0" && time.mid(pos+4,1)=="0") {   //如果秒数为0
//            s_ms=0;
//            return m_ms+s_ms;
//        } else {
//            s_ms=time.mid(pos+3,2).toInt()*1000;
//            return m_ms+s_ms;
//        }
//    } else {
//         m_ms=time.mid(pos,2).toInt()*60000;
//         if(time.mid(pos+3,1)=="0" && time.mid(pos+4,1)=="0") {   //如果秒数为0
//             s_ms=0;
//             return m_ms+s_ms;
//         } else {
//             s_ms=time.mid(pos+3,2).toInt()*1000;
//             return m_ms+s_ms;
//         }
//    }
//}

////将光标移到当前行的首位
//int Lyric::topOfLine(QString content, int pos){
//    while((content.mid(pos-1,1)!="/r")&&(content.mid(pos-1,1)!="\n")&&(pos!=0)){
//        pos--;
//    }
//    return pos;
//}

//bool Lyric::isNumber(char *ch){
//    if(ch[0]>='0'&&ch[0]<='9')
//        return true;
//    return false;
//}

//bool Lyric::isEqual(QString str1, QString str2){
//    QByteArray ba=str1.toLatin1();
//    char *s1=ba.data();
//    ba=str2.toLatin1();
//    char *s2=ba.data();
//    if(strcmp(s1,s2)==0){
//        return true;
//    }
//    else{
//        return false;
//    }
//}
