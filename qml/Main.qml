import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects
import ThemeSwitcher

ApplicationWindow {
  property string stagedPath: ""

  visible: true

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

  ColumnLayout {
    anchors.fill: parent
    anchors.topMargin: 20
    anchors.bottomMargin: 20

    Item {
      Layout.fillWidth: true
      Layout.fillHeight: true
      
      GridView {
        id: grid
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        model: wallpaperModel
        clip: true

        width: Math.floor(parent.width / cellWidth) * cellWidth
        cellWidth: 300
        cellHeight: 200

        delegate: Rectangle {
          id: card
          implicitWidth: 285
          implicitHeight: 185
          color: "transparent"

          radius: 12
          clip: true

          border.width: 5
          border.color: stagedPath === model.filePath ? "white" : "transparent"
          Behavior on border.color {
            ColorAnimation { duration: 150 }
          }

          Image {
            id: img
            anchors.fill: parent
            fillMode: Image.PreserveAspectCrop
            source: "file://" + model.filePath
            anchors.margins: stagedPath === model.filePath ? parent.border.width : 0
            Behavior on anchors.margins {
              NumberAnimation { duration: 150 }
            }

            layer.enabled: true
            layer.effect: OpacityMask {
              maskSource: Rectangle {
                width: img.width
                height: img.height
                radius: 12
              }
            }
          }

          MouseArea {
            anchors.fill: parent
            onClicked: stagedPath = model.filePath
          }
        }
      }
    }

    Item {
      Layout.fillWidth: true
      Layout.preferredHeight: 40

      Layout.leftMargin: 14
      Layout.rightMargin: 14

      Button {
        text: backend.busy ? "Applying..." : "Apply"
        enabled: stagedPath !== "" && !backend.busy

        anchors.right: parent.right
        anchors.bottom: parent.bottom

        implicitWidth: 120
        implicitHeight: 40

        background: Rectangle {
          radius: 8
          anchors.fill: parent
          color: parent.enabled ? (parent.hovered ? "#b1c5ff" : "#89b4fa") : "#1e1e2e"
          border.color: "#585b70"
          border.width: 1

          Behavior on color { ColorAnimation { duration: 100 } }
        }

        contentItem: Text {
          text: parent.text
          color: parent.enabled ? "#1e1e2e" : "#6c7086"
          horizontalAlignment: Text.AlignHCenter
          verticalAlignment: Text.AlignVCenter
        }

        onClicked: backend.applyWallpaper(stagedPath)
      }
    }
  }

}
