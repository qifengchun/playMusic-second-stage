import QtQuick
import QtQuick.Controls

Item {
    property alias voiceAction : voice
    property alias openFileAction: openfile
    property alias openFolderAction: openfolder

    property alias exitAction: exit
    property alias openLyricAction: openLyric
    property alias closeLyricAction: closeLyric
    property alias addSongListAction: addsonglist
    property alias playAction: play
    property alias pauseAction: pause
    property alias previousAction: previous
    property alias nextAction: next
    property alias songListAction: songList
    property alias songdeleteAction: deletesong
    property alias songSearchAction: songsearch
    property alias mvSearchAction: mvsearch
    property alias recentPlayAction: recentplay
    property alias skinAction: skin
    property alias trackInformationAction: trackinformation
    property alias loginAction: login
    property alias aboutAction: about

    Action{
        id:openfile
        text:qsTr("打开文件")
        icon.name:"document-open"
    }
    Action{
        id:openfolder
        text:qsTr("打开文件夹")
        icon.name:"folder"
    }
    Action{
        id:exit
        text:qsTr("退出")
        icon.name:"application-exit"
        onTriggered: {
            appwindow.close()
        }
    }
    Action{
        id:openLyric
        text:qsTr("打开歌词")
        onTriggered: {
            dialogs.lyricDialog.visible=true
        }
    }
    Action{
        id:closeLyric
        text:qsTr("关闭歌词")
        onTriggered: {
            dialogs.lyricDialog.visible=false
        }
    }
    Action{
        id:addsonglist
        text:qsTr("添加歌单")
    }

    Action{
        id:play
        icon.name: "media-playback-start"
        icon.source:"qrc:/image/add.png"
        onTriggered:{
            play1.visible=false
            pause1.visible=true
        }
    }
    Action{
        id:pause
        icon.name: "media-playback-pause"
        onTriggered:{
            pause1.visible=false
            play1.visible=true
        }
    }
    Action{
        id:previous
        icon.name: "media-seek-backward"
    }
    Action{
        id:next
        icon.name: "media-seek-forward"
    }
    Action{
        id:voice

    }
    Action{
        id:songList
        text:qsTr("列表")
        icon.name:"list-add"
    }
    Action{
        id:deletesong
        text:qsTr("删除")
        icon.name: "list-remove"
    }
    Action{
        id:songsearch
        text:qsTr("搜索歌曲")
        icon.name: "system-search"
        onTriggered: {
            dialogs.songSearchDialog.visible=true
        }
    }
    Action{
        id:mvsearch
        text:qsTr("搜索MV")
        icon.name: "system-search"

    }
    Action{
        id:recentplay
        text:qsTr("最近播放")
    }
    Action{
        id:skin
        text:qsTr("主题")
        icon.source: "qrc:/image/skn.png"
        onTriggered: {
            dialogs.skinDialog.visible=true
        }
    }
    Action{
        id:trackinformation
        text:qsTr("曲目信息")
        icon.source: "qrc:/image/曲目信息.png"
        onTriggered: {
            dialogs.trackInformationDialog.visible=true
        }
    }
    Action{
        id:login
        text:qsTr("登陆")
    }
    Action{
        id:about
        text:qsTr("关于")
        icon.name: "help-about"
    }

}
