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
            content.musicPlayer.audio.source=kuGouSong.url;

            content.musicPlayer.audio.play()
            content.musicPlayer.start.visible=false
            content.musicPlayer.pause.visible=true

            content.musicPlayer.fileName=songName[songListView.currentIndex]
            content.fileNameText.text=songName[songListView.currentIndex]
            content.singerText.text=singerName[songListView.currentIndex]

            appWindow.rootImage.source=image;
            content.leftImage.source=image;

            dialogs.miniDialog.musicStart.visible = false
            dialogs.miniDialog.musicPause.visible = true

            dialogs.lyricDialog.timerTest.running=false
            netLyric=kuGouSong.lyrics
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
