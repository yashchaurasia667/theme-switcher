import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ThemeSwitcher

ApplicationWindow {
  property string stagedPath: ""

  visible: true
  // color: "transparent"

  width: 1280
  height: 720
  title: "Theme Switcher"

  WallpaperModel { id: wallpaperModel }
  Backend { id: backend }

  // Label {
  //   text: stagedPath
  //   color: "white"
  //   z: 1
  // }

  GridView {
    model: wallpaperModel
    anchors.fill: parent

    cellWidth: 300
    cellHeight: 200

    delegate: Rectangle {
      width: 300
      height: 200

      // anchors.margins: 5
      radius: 12

      border.width: 5
      border.color: stagedPath === model.filePath ? "white" : "transparent"

      Image {
        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop
        source: "file://" + model.filePath
      }

      MouseArea {
        anchors.fill: parent
        onClicked: stagedPath = model.filePath
      }
    }
  }

  Button {
    anchors.bottom: parent.bottom
    anchors.right: parent.right
    text: backend.busy ? "Applying..." : "Apply"
    enabled: stagedPath !== "" && !backend.busy
    onClicked: backend.applyWallpaper(stagedPath)
  }

}
