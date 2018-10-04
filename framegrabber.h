#ifndef FRAMEGRABBER_H
#define FRAMEGRABBER_H

#include <QAbstractVideoFilter>
#include <QTime>
#include <QVideoSurfaceFormat>
#include <QString>
#include <QByteArray>
#include <QVideoFrame>
#include <QVariant>
#include <public.h>

#define MAX_OUT_SIZE 10

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

class FilterRunnable : public QVideoFilterRunnable
{
public:
    FilterRunnable(FrameGrabber *frameGrabber);
    QVideoFrame run(QVideoFrame *input, const QVideoSurfaceFormat &surfaceFormat, RunFlags flags) Q_DECL_OVERRIDE;
    xnor_model *xmodel = NULL;
    QTime timer;
    int frameCount=0;
    bool loadModel = true;

private:
    FrameGrabber *m_frameGrabber;
    bool m_yuv;
};

class FilterResult : public QObject
{
    Q_OBJECT

public slots:
    QVariant fps() const {return m_fps;}
    QVariant avgFps() const {return m_avgFps;}
    QVariant deltaT() const {return m_deltaT;}
    QVariantList bboxes() const {return m_bboxes;} // contains the rects
    QVariantList labels() const {return m_labels;} // contains the labels
    QVariantList classIds() const {return m_class_ids;} // contains the class ids
    QVariantList confidences() const {return m_confidence;}

private:
    QVariantList m_bboxes, m_labels, m_class_ids, m_confidence;
    QVariant m_fps, m_avgFps, m_deltaT;
    friend class FilterRunnable;
};

#endif // FRAMEGRABBER_H
