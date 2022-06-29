import QtQuick
import Lyric

Item {
    width:400
    height: 500
    property alias lyric:lyric
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
        id:lyricListView
        model:lyricListModel
        delegate:lyricDelegate
        visible:false
        anchors.fill:parent
//        spacing:30
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
        Rectangle{
            width:350
            height: 30
            Text{
                id:mt
                text:currentLyrics

                font.pixelSize: ListView.isCurrentItem?25:18
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                color:ListView.isCurrentItem?"red":"black"
            }
        }



    }

    Lyric{
        id:lyric
    }
}
