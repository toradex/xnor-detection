#include "videooverlay.h"
#include <QDebug>
VideoOverlay::VideoOverlay(QObject *parent, QString source)
    : QObject(parent)
{
    QString program = "gst-launch-1.0 -v v4l2src device=";
    program.append(source);
    program.append("! image/jpeg, width=1280, height=720, framerate=\"(fraction)60/1\" ! jpegparse ! jpegdec ! videoconvert ! fpsdisplaysink sync=false");
    QProcess *gstProcess = new QProcess(this);
    gstProcess->start(program);

    qDebug() << gstProcess->isWindowType();
    qDebug() << gstProcess->isOpen();
    qDebug() << gstProcess->open();
}

QString VideoOverlay::source(){
    return m_source;
}

void VideoOverlay::setSource(const QString &source){
    if(m_source != source){
        m_source = source;
        emit sourceChanged();
    }
}

void VideoOverlay::init(){

}
