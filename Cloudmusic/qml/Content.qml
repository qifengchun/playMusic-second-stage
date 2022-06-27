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
        filesmodel.clear();
        for(var i=0;i<arguments[0].length;i++){
            var data={"filePath": arguments[0][i]};
            filesmodel.append(data);
            list.model=filesmodel;
            list.currentIndex=0;
        }
    }
    function song_previous(){
        //接受数据

        list.decrementCurrentIndex(list.currentIndex)
        player.source = dialogs.fileOpenDialog.currentFiles[list.currentIndex]
        player.play()
        //判断当前索引在
    }
    function song_next(){
        //接受数据
        //console.log(index)
        //list.currentIndex = index
        list.incrementCurrentIndex()
        player.source = dialogs.fileOpenDialog.currentFiles[list.currentIndex]
        player.play()
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
        opacity: 1
        z:1
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
//左边放swipview
     Rectangle {
            id:leftrec
            implicitWidth: 600 //初始化的宽度
            SplitView.maximumWidth:parent.width*0.8  //能拖动的最大的宽度
          color: "lightblue"

          SwipeView {
              id: view

              currentIndex: 1
              anchors.fill: parent

              Item {
                  id: firstPage
                  Image {
                      //id= name
                      source: "qrc:/image/播放.png"
                      anchors.fill:parent
                  }

              }
              Item {
                  id: secondPage
                  Image {
                      //id= name
                      source: "qrc:/image/下一曲.png"
                      anchors.fill: parent
                  }
              }
              Item {
                  id: thirdPage
                  Image {
                      //id= name
                      source:"qrc:/image/暂停.png"
                      anchors.fill: parent
                  }

              }
          }

          PageIndicator {
              id: indicator

              count: view.count
              currentIndex: view.currentIndex

              anchors.bottom: view.bottom
              anchors.horizontalCenter: parent.horizontalCenter}


            }

//右边放列表
     Rectangle {
                id: rightrec
                SplitView.minimumWidth: parent.width*0.2 //可以达到的最小宽度
                SplitView.fillWidth:    true  //可以填满整个宽度
                SplitView.fillHeight:   true
                color: "lightgray"
                ListView{
                    id:list
                    anchors.fill: parent
                    model: filesmodel
                    delegate:audioDelegate

                    ListModel{
                        id: filesmodel
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
                                    console.log(index+1)
                                    console.log(filePath)
                                    player.source= filePath
                                    player.play()
                                }
                            }
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


















































