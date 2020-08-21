import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 70*21
    height: 70*9
    title: qsTr("Hello World")
    
    property string map: loadedMap
    property var mapData: JSON.parse(loadedMap)// map.split("|")
    Column {
        Repeater {
            model: 9
            Row
            {
                property int rowIdx: index
                Repeater {
                    model: 21
                    Rectangle {
                        property int colIdx: index
                        width: 70
                        height: 70
                        border.width: 1
                        border.color: "gray"
                        Image {
                            id: cell
                            property int cellData: mapData[rowIdx][colIdx]
                            anchors.fill: parent
                            source: cellData == -3 ? "qrc:/images/mud.png" :
                                                      cellData == -2 ? "qrc:/images/trap.png" :
                                                                        cellData == -1 ? "qrc:/images/tree.png" :
                                                                                          cellData == 0 ? "qrc:/images/land.png" :
                                                                                                           "qrc:/images/gold.png"
                            Text {
                                visible: cell.cellData > 0
                                text: cell.cellData
                                color: "blue"
                                font.pixelSize: 24
                                anchors.horizontalCenter: parent.horizontalCenter

                            }
                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    if (cell.cellData >= 0)
                                        cell.cellData = -3
                                    else
                                        cell.cellData++
                                    mapData[rowIdx][colIdx] = cell.cellData
                                    CONTROLLER.setJson(JSON.stringify(mapData))
                                }
                                onMouseXChanged: {
                                    if(!containsPress) {
                                        if (mouseX < 0)
                                            cell.cellData = 0
                                        else
                                            cell.cellData = mouseX
                                        mapData[rowIdx][colIdx] = cell.cellData
                                        CONTROLLER.setJson(JSON.stringify(mapData))
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
