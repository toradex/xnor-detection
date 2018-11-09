#ifndef FRAMEGRABBER_H
#define FRAMEGRABBER_H

#include <QObject>
#include <QAbstractVideoFilter>
#include <QThreadPool>
#include <QTime>
#include <QVideoSurfaceFormat>
#include <QString>
#include <QQueue>
#include <QByteArray>
#include <QVideoFrame>
#include <QRunnable>
#include <QVariant>
#include <QDebug>

#include <public.h>

#define MAX_OUT_SIZE 50

class FrameGrabber : public QAbstractVideoFilter
{
    Q_OBJECT
public:
    QVideoFilterRunnable *createFilterRunnable() Q_DECL_OVERRIDE;

signals:
    void finished(QObject *e);

private:
    friend class FilterRunnable;
};

class FilterResult : public QObject
{
    Q_OBJECT

public slots:
    QVariant fps() const {return m_fps;}
    QVariant fpsAvg() const {return m_fpsAvg;}
    QVariant deltaT() const {return m_deltaT;}
    QVariant error() const {return m_error;}
    QVariantList bboxes() const {return m_bboxes;} // contains the rects
    QVariantList labels() const {return m_labels;} // contains the labels
    QVariantList classIds() const {return m_class_ids;} // contains the class ids
    QVariantList confidences() const {return m_confidence;}

private:
    QVariantList m_bboxes, m_labels, m_class_ids, m_confidence;
    QVariant m_fps, m_fpsAvg, m_deltaT, m_error;
    friend class FilterRunnable;
};

class FilterRunnable : public QVideoFilterRunnable
{

public:
    FilterRunnable(FrameGrabber *frameGrabber);
    QVideoFrame run(QVideoFrame *input, const QVideoSurfaceFormat &surfaceFormat, RunFlags flags) Q_DECL_OVERRIDE;
    int mediumFPS();

private:
    FrameGrabber *m_frameGrabber;
    QList<int> fpsList;
    xnor_model *xmodel;
    xnor_error *xerror; // error returned by the image handles
    xnor_evaluation_result *xresult;
    xnor_evaluation_result_type xtype;
    xnor_input *xinput; // input handle
    xnor_bounding_box bbox[MAX_OUT_SIZE];
    int32_t out_size;
    QTime timer, timerAvg;
    int frameCount=0;
    bool loadModel = true;
};



#endif // FRAMEGRABBER_H
