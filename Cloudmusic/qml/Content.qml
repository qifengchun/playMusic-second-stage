import QtQuick
import QtQuick.Dialogs
import QtMultimedia
//import QtQuick.Controls  as QQC
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick 2.5
import QtQuick.Window

Item{    
    property alias player: player

    function setFilesModel(){
        filesModel.clear();
        for(var i=0;i<arguments[0].length;i++){
            var data={"filePath": arguments[0][i]};
            filesModel.append(data);
            list.model=filesModel;
            list.currentIndex=0;
        }
    }
    function song_previous(){
        //接受数据
        list.currentIndex = index
        list.incrementCurrentIndex(list.currentIndex)
        player.source = dialogs.fileOpenDialog.currentFiles[0][index]
        player.play()
        //判断当前索引在
    }
    function durationtime_show(){


        var milliseconds = content.player.position
        var minutes = Math.floor(milliseconds / 60000)
        milliseconds = milliseconds - minutes * 60000
        var seconds = milliseconds / 1000
        seconds = Math.round(seconds)
        //        if (seconds < 10)
        //           now.text = minutes + ":0" + seconds
        //        else
        //           now = minutes + ":" + seconds
        if(minutes<10)
        {
            if(seconds<10) now.text ="0" +minutes + ":0" +seconds
            else now.text="0"+minutes+":"+seconds
        }
        else
        {
            if(seconds<10) now.text =minutes+":0"+seconds
            else now.text = minutes+":"+seconds
        }

    }
    function durationtime_endTime(){
        var  milliseconds = player.duration
        //console.log( milliseconds)
        var minutes = Math.floor(milliseconds / 60000)
        milliseconds = milliseconds - minutes * 60000
        var seconds = milliseconds / 1000
        seconds = Math.round(seconds)
        if(minutes<10)
        {
            if(seconds<10) endTime.text ="0" +minutes + ":0" +seconds
            else endTime.text="0"+minutes+":"+seconds
        }
        else
        {
            if(seconds<10) endTime.text =minutes+":0"+seconds
            else endTime.text = minutes+":"+seconds

        }
    }
    SplitView {
        anchors.fill: parent
        orientation: Qt.Horizontal  //视图排列方向
        //设计拖动的线 ，让其拖动必须设置implicitHeight，不然无法拖动
        handle:
            Rectangle {
            width: 1
            implicitWidth: 1
            //          implicitHeight: 3
            color: SplitHandle.hovered ? "#81e889" : "#FFFFFF"
        }
        //左边放列表
        Rectangle {
            id:leftrec
            implicitWidth: 300  //初始化的宽度
            //          implicitHeight: 100
            SplitView.maximumWidth:400  //能拖动的最大的宽度
            //          SplitView.maximumHeight: 300

            color: "lightblue"
            ListView{
                id:list
                anchors.fill: parent
                //                          anchors.left: parent.left
                model: filesModel
                delegate:audioDelegate

                ListModel{
                    id: filesModel
                }
                Component{
                    id:audioDelegate
                    Rectangle{
                        width: 300
                        height: 40
                        color:ListView.isCurrentItem ? "lightgrey" : "white"
                        Text {
                            id: serialNumberText
                            text: index+1
                            font.pointSize: 15
                            width: 40
                            color: "Teal"
                            anchors.rightMargin: 40
                        }
                        TapHandler{
                            onTapped: {
                                list.currentIndex = index
                                console.log(index)
                                console.log(filePath)
                                //                                    console.log(player.position)
                                //                                    console.log(Math.floor(181/60))
                                //                                    console.log(player.duration)
                                //                                    console.log(player.position/player.duration)
                                player.source= filePath
                                player.play
                                        ()
                            }
                        }
                    }
                }


                MediaPlayer{
                    id:player

                    audioOutput:  AudioOutput{
                        volume: slider1.value
                    }
                }

                Timer{
                    interval: 10;running: true;repeat: true
                    onTriggered:    slider2.value=  player.position/1000
                }

            }
        }
        Rectangle {
            id: centerItem
            SplitView.minimumWidth: 50 //可以达到的最小宽度
            //            implicitWidth: parent.width-300
            //            SplitView.minimumHeight: 90
            SplitView.fillWidth: true  //可以填满整个宽度
            SplitView.fillHeight: true
            color: "lightgray"
            SwipeView {



                //enabled:"false"

                id: swipeView
                anchors.fill:parent
                currentIndex:indicator.currentIndex

                Rectangle{
                    Image {
                        //id= name
                        source: "file:///root/QML/text2/image/上一曲.png"
                        anchors.fill:parent
                    }
                }
                Rectangle{
                    Image {
                        //id= name
                        source: "file:///root/QML/text2/image/下一曲.png"
                        anchors.fill: parent
                    }
                }
                Rectangle{
                    Image {
                        //id= name
                        source:"file:///root/QML/text2/image/播放.png"
                        anchors.fill: parent
                    }
                }
                Rectangle{
                    Image {
                        //id= name
                        source: "file:///root/QML/text2/image/暂停.png"
                        anchors.fill: parent
                    }
                }



            }

            //    //方法1
            //    PageIndicator {
            //          id: indicator
            //          count: swipeView.count
            //          currentIndex: swipeView.currentIndex
            //          interactive:true //可以点击
            //          anchors.bottom: swipeView.bottom
            //          anchors.horizontalCenter:parent.horizontalCenter
            //      }


            //方法2
            TabBar {
                id: indicator
                currentIndex: swipeView.currentIndex
                anchors.top: parent.top
                anchors.right: parent.right
                width: 400
                opacity :0.5


                TabButton {
                    text:qsTr("歌词")
                }
                TabButton {
                    text: qsTr("歌单")
                }
                TabButton {
                    text: qsTr("MV")
                }
                TabButton {
                    text: qsTr("Page 4")
                }
            }
        }


    }

}


















































