import QtQuick
import Lyric

Item {
    property alias lyricText:lyricText
    property alias lyricListView:lyricListView
    property alias lyricListModel:lyricListModel
    property alias lyricDelegate:lyricDelegate

    Text{
        id:lyricText
        text:qsTr("当前无歌词")
        visible:false
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        width:350
    }

    ListView{
        id:ltricListView
        model:lyricListModel
        delegate:lyricDelegate
        visible:false
        anchors.fill:parent
        spacing:30
        currentIndex: -1

        //固定currentItem的位置
        highlightRangeMode: ListView.ApplyRange
        preferredHighlightBegin: height/3+30
        preferredHighlightEnd: height/3+60
    }

    ListModel{
        id:lyricListModel
    }

    Component{
        id:lyricDelegate
        Text{
            id:mt
            text:currentLyrics
            width:350
            font.pixelSize: ListView.isCurrentItem?25:18
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            color:ListView.isCurrentItem?"red":"black"
        }
    }
    Lyric{
        id:lyric_id
    }
}
