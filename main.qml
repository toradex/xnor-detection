import QtQuick 2.11
import QtQuick.Window 2.3
import QtQuick.Layouts 1.3
import QtMultimedia 5.9
import qt.toradex.xnor 1.0


Window {
    id: window
    visible: true
    //visibility: Window.FullScreen
    width: 1024
    height: 600



    Rectangle{
        anchors.fill: parent
        color: "#1f438d"
        //color: "transparent"

        Row{
            id: row
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: Screen.width-toradexLogo.width-xnorLogo.width
            //spacing: 5
            Image{
                id: toradexLogo
                source: "qrc:/imgs/toradex-logo.png"
                width: 300
                fillMode: Image.PreserveAspectFit
            }
            Image{
                id: xnorLogo
                source: "qrc:/imgs/xnor-logo.png"
                width: 300
                fillMode: Image.PreserveAspectFit
            }
        }

        GridLayout{
            columns: 3
            columnSpacing: 5
            rowSpacing: 5
            anchors.centerIn: parent

            Repeater{
                model: QtMultimedia.availableCameras

                Rectangle{
                    id: rectCamera
                    width: (4/9)*Screen.height + border.width*6
                    height: (1/3)*Screen.height + border.width*6
                    color: "transparent"
                    border.color: "#7dd825"
                    border.width: 10

                    Camera {
                        id: camera
                        deviceId: String(QtMultimedia.availableCameras[index])
                        viewfinder.resolution: "320x240"
                    }
                    VideoOutput {
                        id: videoOutput
                        //visible: false
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
                            fpsText.nPeople = bb.length

                            if(e.error()){
                                fpsText.text = e.error()
                            }

                            resetRects()
                            if(bb.length > 0 && bb.length < 50){
                                for (var i = 0; i < bb.length; ++i) {
                                    var xr = videoOutput.width / videoOutput.sourceRect.width
                                    var yr = videoOutput.height / videoOutput.sourceRect.height
                                    var bbox = rectRepeater.itemAt(i)
                                    bbox.x = videoOutput.x + bb[i].x * xr
                                    bbox.y = videoOutput.y + bb[i].y * yr
                                    bbox.width = bb[i].width * xr
                                    bbox.height = bb[i].height * yr
                                    bbox.class_id = classIds[i]
                                    bbox.label = "person"
                                    bbox.confidence = conf[i]
                                    bbox.visible = true
                                }
                                if(fpsText.nPeople > 1){
                                    fpsText.text = "FPS: " + Math.round(fpsText.fps).toString() +
                                      "\n" + fpsText.nPeople.toString() + " people" +
                                      "\n Camera " + index
                                } else {
                                    fpsText.text = "FPS: " + Math.round(fpsText.fps).toString() +
                                      "\n" + fpsText.nPeople.toString() + " person" +
                                      "\n Camera " + index
                                }
                            }
                        }
                    }
                    function resetRects(){
                        for (var i = 0; i < rectRepeater.count; ++i)
                            rectRepeater.itemAt(i).visible = false;
                    }

                    Rectangle{
                        color: Qt.rgba(0, 0, 0, 0.5)
                        x: 10
                        y: 10
                        width: fpsText.width + 10
                        height: fpsText.height + 10
                        radius: width/10
                        Text {
                            id: fpsText
                            property double fps: 0
                            property int nPeople: 0
                            color: "white"
                            font.pixelSize: 10
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
                                    font.pixelSize: 10
                                }
                            }
                        }
                    }
                }
            }
        }
    }

}
