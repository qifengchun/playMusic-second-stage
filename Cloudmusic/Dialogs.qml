import QtQuick
import QtQuick.Controls 2.5 as QQC
import QtQuick.Dialogs
import QtQuick.Layouts
import Qt.labs.platform

Item{
    function openAboutDialog() { about.open(); }
    function openFileDialog() { fileOpen.open(); }


    property alias fileOpenDialog: fileOpen
    property alias fileImageDialog:fileimageDialog
    property alias skinDialog:skinDialog
    property alias trackInformationDialog:trackInformationDialog
    property alias songSearchDialog:songSearchDialog
    property alias lyricDialog:lyricDialog

//打开文件
    FileDialog {
        id: fileOpen
        title: "Select some music files"
        fileMode: FileDialog.OpenFiles
        nameFilters: [ "Song files (*.mp3)" ]


    }
    FileDialog{
        id:fileimageDialog
        title:"请选择一张图片"
        //folder:shortcuts.documents
        nameFilters:["Image files (*.png *.jpeg *.jpg)"]
        onAccepted: {
            imageUrl=fileImageDialog.fileUrl
            dialogs.skinDialog.usingImage=imageUrl
            dialogs.skinDialog.close()
        }
    }

    QQC.Dialog{
        id:about
        title:"关于"
        width: 800
        contentItem:Text{
            text:"本软件名为Cloud Music,由齐逢春，向文勇，曾祥欢共同实现。"
        }
        standardButtons: StandardButton.Ok
    }

    SkinDialog{
        id:skinDialog
        visible:false
    }

    TrackInformationDialog{
        id:trackInformationDialog
        visible:false
    }

    SongSearchDialog{
        id:songSearchDialog
        visible: false
    }

    LyricPage{
        id:lyricDialog
        visible: false
    }


}
