//由qfc完成搜索模块
import QtQuick
import QtCore
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs

ApplicationWindow {
    id:songSearchWindow
    width:600
    height:500
    title: qsTr("搜索歌曲")
    visible: true
    property bool networkPlay:false
    property bool network:false
    property bool videoPlayFlag: false
    property double mX:0.0
    property double mY:0.0
    property alias songListView: songListView
    property alias play1: play1
    //    property alias pauseVideo: pauseVideo
    property alias songListModel: songListModel
    property alias inputField: inputField
    property string netLyric:""
//    property alias lyric_id:lyric_id

    background: Image {
        id: name
        fillMode: Image.PreserveAspectCrop
        source: imageUrl
        anchors.fill: parent
        opacity: 0.3
    }
    //搜索的主界面
    Rectangle{
        id:re1
        visible: true
        ColumnLayout{
            spacing: 10
            RowLayout{
                id:rowLayout
                TextField{
                    id:inputField
                    Layout.preferredWidth:300
                    Layout.preferredHeight: 40
                    Layout.leftMargin: (songSearchWindow.width-inputField.width)/2.5
                    focus: true
                    placeholderText: qsTr("陈奕迅")
                    Layout.topMargin: 30
                    selectByMouse: true//鼠标可以选择
                    font.pointSize: 12//字体大小
                    background: Rectangle{//设置边框
                        radius: 4
                        border.color: "black"
                    }
                    Keys.onPressed: {
                        if(event.key===Qt.Key_Return){
                            if(event.key===Qt.Key_Return) {
                                kugou.kuGouSong.searchSong(inputField.placeholderText)
                                inputField.text=inputField.placeholderText
                            }else{
                                kugou.kuGouSong.searchSong(inputField.text)
                            }
                        }
                    }
                }
                Button{
                    id:songSearchButton
                    text: qsTr("搜索")
                    Layout.preferredWidth: 70
                    Layout.preferredHeight: 40
                    Layout.topMargin: 30

                    onClicked: {
                        if(inputField.text.length===0) {
                            kugou.kuGouSong.searchSong(inputField.placeholderText)
                            inputField.text=inputField.placeholderText
                        } else {
                            kugou.kuGouSong.searchSong(inputField.text)
                        }
                    }
                }
            }
            TabBar{
                id:bar
                Layout.preferredWidth: parent.width/3

                TabButton{
                    text:qsTr("单曲")
                    implicitHeight: 30
                    implicitWidth:10
                    onClicked: {
                        if(inputField.text.length===0) {
                            kugou.kuGouSong.searchSong(inputField.placeholderText)
                            inputField.text=inputField.placeholderText
                        } else {
                            kugou.kuGouSong.searchSong(inputField.text)
                        }
                    }
                }

                TabButton {
                    text: qsTr("歌单")
                    implicitHeight:30
                    implicitWidth: 10
                    onClicked: {
                        if(inputField.text.length===0) {
                            kugou.kuGouPlayList.searchPlayList(inputField.placeholderText)
                            inputField.text=inputField.placeholderText
                        } else {
                            kugou.kuGouPlayList.searchPlayList(inputField.text)
                        }
                    }
                }

                TabButton{
                    text: qsTr("mv")
                    implicitHeight: 30
                    implicitWidth: 10
                    onClicked: {
                        if(inputField.text.length===0) {
                            kugou.kuGouMv.searchMv(inputField.placeholderText)
                            inputField.text=inputField.placeholderText
                        } else {
                            kugou.kuGouMv.searchMv(inputField.text)
                        }
                    }
                }
            }
            //StackLayout 类提供了一个项目堆栈，其中一次只有一个项目可见
            StackLayout {
                id: stack
                width: parent.width
                height: parent.height-bar.height-rowLayout-15
                currentIndex: bar.currentIndex//当前索引
                //歌曲界面
                Rectangle{
                    id:rec1
                    radius: 4
                    Layout.preferredWidth: songSearchWindow.width
                    Layout.preferredHeight: songSearchWindow.height-inputField.height
                    visible:false
                    border.color: "black"//边框颜色
                    //搜索歌曲排列

                    ColumnLayout{
                        anchors.fill: parent
                        //搜索歌曲的信息排列
                        RowLayout{
                            id:row1
                            Layout.fillWidth: true
                            Layout.leftMargin: 5
                            Text {
                                Layout.preferredWidth: 160
                                Layout.rightMargin: 40
                                text: qsTr("歌曲")
                                font.pixelSize: 15
                            }
                            Text {
                                Layout.preferredWidth: 120
                                Layout.rightMargin: 40
                                text: qsTr("专辑")
                                font.pixelSize: 15
                            }
                            Text {
                                Layout.preferredWidth: 80
                                text: qsTr("时长")
                                font.pixelSize: 15
                            }
                            Text {
                                Layout.preferredWidth: 60
                                Layout.leftMargin: 40
                                text: qsTr("来源")
                                font.pixelSize: 15
                            }
                        }
                        ListView{
                            id:songListView
                            Layout.preferredWidth: songSearchWindow.width
                            Layout.leftMargin: 5
                            Layout.preferredHeight: parent.height-row1.height
                            clip: true//此属性保存是否启用剪辑。 默认剪辑值为 false.
                            //                            //如果启用了剪辑，则项目会将其自己的绘画以及其子项的绘画剪辑到其边界矩形。
                            spacing: 5
                            model:songListModel
                            delegate: songListDelegate
                            //                            //垂直互式滚动条
                            ScrollBar.vertical: ScrollBar {
                                width: 12
                                policy: ScrollBar.AlwaysOn//ScrollBar.AsNeeded仅当内容太大而无法容纳时，才会显示滚动条。
                            }
                        }
                    }
                    ListModel{
                        id:songListModel
                    }
                    Component{
                        id:songListDelegate
                        Rectangle {

                            radius: 4
                            width: songListView.width - 20
                            height: 40
                            focus: true
                            color:ListView.isCurrentItem ? "lightgrey" : "white"//选择时的颜色
                            RowLayout{
                                id:sarchLayout
                                Text {
                                    text:song
                                    Layout.preferredWidth: 160
                                    Layout.rightMargin: 40
                                    elide: Text.ElideRight
                                }
                                Text {
                                    text: album
                                    Layout.preferredWidth: 120
                                    Layout.rightMargin: 40
                                    elide: Text.ElideRight
                                }
                                Text {
                                    text: duration
                                    Layout.preferredWidth: 80
                                    Layout.rightMargin: 20
                                }
                                Text {
                                    id: kugouText
                                    text: qsTr("酷狗音乐")
                                    Layout.preferredWidth:60
                                }
                            }
                            //鼠标右键弹出单曲的菜单界面
                            TapHandler{
                                id:tapHandler
                                acceptedButtons: Qt.RightButton
                                onTapped: {
                                    console.log("x="+eventPoint.scenePosition.x);
                                    console.log("y="+eventPoint.scenePosition.y);
                                    menu1.open()
                                }
                            }
                            TapHandler{
                                id:mouseArea1
                                //  gesturePolicy: TapHandler.ReleaseWithinBounds
                                acceptedButtons: Qt.LeftButton
                                onTapped: {
                                    songListView.currentIndex=index;//索引
                                    kugou.kuGouSong.getSongUrl(songListView.currentIndex)
                                    console.log("clicked")
                                }
                                onDoubleTapped: {
                                    play1.triggered();
                                    console.log("double clicked!")
                                }
                            }
                            Menu{
                                id:menu1
                                x:mX+100
                                y:mY
                                contentData: [
                                    play1,
                                    pause1,
                                    downloadSong
                                ]
                            }
                        }
                    }
                }
            }

        }
    }
    //退出之后清理后台缓存资源
    onClosing: {
        songListModel.clear()
        network = false
        inputField.clear();
    }
    KuGou{
        id:kugou
    }
    Action{
        id:play1
        text: qsTr("播放")
        onTriggered: {
            if(re1.visible) {
                content.player.source=kugou.kuGouSong.url
                content.player.play();
            } else {
                console.log("播放错误");
            }
        }
    }
    Action{
        id:downloadSong
        text:qsTr("下载")
        onTriggered: {
            saveSongDialog.open()
        }
    }
    Action{
        id:pause1
        text: qsTr("暂停")
        onTriggered: actions.pauseAction.triggered()
    }

    FileDialog{
        id: saveSongDialog
        title: "save music"
        currentFolder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
        nameFilters: ["*.mp3"]
        //        selectExisting: false
        onAccepted: {
            var path=fileUrl.toString().slice(7)
            var end=path.substring(path.length-4)
            if(end!=="mp3") {
                path+=".mp3"
            }
            if(re1.visible) {
                kugou.kuGouSong.downloadSong(songListView.currentIndex,path)
            } else {
                console.log("download faided!")
            }
        }
    }

    function showNetworkLyrics(){
//        dialogs.lyricDialog.lyric_id.lyric=netLyric
//        content.placeLyricToView()
    }
}
