//由qfc完成的搜索模块
import QtQuick
import KuGouSong

Item {

    property alias kuGouSong:kuGouSong
    KuGouSong{
        id:kuGouSong
        onSongNameChanged: {
            addSongItem()
        }
        onUrlChanged: {
//            dialogs.lyricDialog.timerTest.running=false
            netLyric=kuGouSong.lyrics
            netSongName=kuGouSong.songName
            showNetworkLyrics();
        }
    }

    function addSongItem(){
        bar.currentIndex=0
        var s,m;
        songListModel.clear()
        for(var i=0;i<kuGouSong.singerName.length;i++) {
            m=(kuGouSong.duration[i]-kuGouSong.duration[i]%60)/60
            s=kuGouSong.duration[i]-m*60
            if(s>=0&s<10) {
                 songListModel.append({"song":kuGouSong.singerName[i]+"-"+kuGouSong.songName[i],"album":kuGouSong.albumName[i],"duration":m+":0"+s})
            } else {
                 songListModel.append({"song":kuGouSong.singerName[i]+"-"+kuGouSong.songName[i],"album":kuGouSong.albumName[i],"duration":m+":"+s})
            }
        }
    }



}
