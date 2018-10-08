import QtQuick 2.11
import QtQuick.Window 2.3
import QtQuick.Layouts 1.3
import QtMultimedia 5.9
import qt.toradex.xnor 1.0

Window {
    id: window
    visible: true
    visibility: Window.FullScreen

    GridLayout{
        columns: 2
        columnSpacing: 100
        anchors.centerIn: parent
        Repeater{
            model: QtMultimedia.availableCameras
            Rectangle{
                id: rectCamera
                width: 320
                height: 240
                color: "transparent"
                Camera {
                    id: camera
                    deviceId: QtMultimedia.availableCameras[index]
                    viewfinder{
                        resolution: "640x480"
                    }
                }
                VideoOutput {
                    id: videoOutput
                    source: camera
                    anchors.fill: rectCamera
                    filters: [frameGrabber]
                }

                FrameGrabber{
                    id: frameGrabber
                    active: true
                    onFinished: {
                        var bb = e.bboxes();
                        var labels = e.labels();
                        var classIds = e.classIds();
                        var conf = e.confidences();
                        fpsText.fps = e.fps()
                        fpsText.deltaT = e.deltaT()
                        fpsText.fpsAvg = e.fpsAvg()

                        resetRects()

                        for (var i = 0; i < bb.length; ++i) {
                            var xr = videoOutput.width / videoOutput.sourceRect.width
                            var yr = videoOutput.height / videoOutput.sourceRect.height
                            var bbox = rectRepeater.itemAt(i)
                            bbox.x = videoOutput.x + bb[i].x * xr
                            bbox.y = videoOutput.y + bb[i].y * yr
                            bbox.width = bb[i].width * xr
                            bbox.height = bb[i].height * yr
                            bbox.class_id = classIds[i]
                            bbox.label = labels[i]
                            bbox.confidence = conf[i]
                            bbox.visible = true
                        }
                    }
                }
                function resetRects(){
                    for (var i = 0; i < rectRepeater.count; ++i)
                        rectRepeater.itemAt(i).visible = false;
                }

                Rectangle{
                    color: Qt.rgba(0, 0, 0, 0.5)
                    width: fpsText.width + 10
                    height: fpsText.height + 10
                    radius: width/10
                    Text {
                        id: fpsText
                        property double fps: 0
                        property double fpsAvg: 0
                        property double deltaT: 0
                        text: "FPS: " + Math.round(fps).toString() +
                              "\nDelta T (ms): " + Math.round(deltaT).toString()
                        color: "white"
                        font.pixelSize: 15
                        anchors.centerIn: parent
                    }
                }
                Repeater{
                    id: rectRepeater
                    model: 10

                    Rectangle{
                        id: rect
                        x: Math.random()*Screen.width + videoOutput.x
                        y: Math.random()*Screen.height + videoOutput.y
                        width: Math.random()*Screen.width
                        height: Math.random()*Screen.height
                        color:  "transparent"
                        border.color:  Qt.rgba(Math.random(), Math.random(), Math.random(), 1)
                        border.width: 8
                        visible: false
                        property int class_id
                        property string label
                        property int confidence
                        Rectangle{
                            color: parent.border.color
                            width: label_confidence.width + 5
                            height: label_confidence.height + 2
                            anchors.top: parent.top
                            anchors.left: parent.left
                            Text {
                                id: label_confidence
                                text: "Label: " + rect.label  +"\n" +
                                      "Confidence: " + rect.confidence + "%\n" +
                                      "Class ID: " + rect.class_id
                                anchors.centerIn: parent
                                color: "white"
                                font.pixelSize: 15
                            }
                        }
                    }
                }
            }
        }
    }
}
