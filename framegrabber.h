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
    QTime timer;
    int frameCount=0;

private:
    FrameGrabber *m_frameGrabber;
    bool m_yuv;
};

class FilterResult : public QObject
{
    Q_OBJECT

public slots:
    QVariant fps() const {return m_fps;}
    QVariantList bboxes() const {return m_bboxes;} // contains the rects
    QVariantList labels() const {return m_labels;} // contains the labels
    QVariantList classIds() const {return m_class_ids;} // contains the class ids
    QVariantList confidences() const {return m_confidence;}

private:
    QVariantList m_bboxes, m_labels, m_class_ids, m_confidence;
    QVariant m_fps;
    friend class FilterRunnable;
};

#endif // FRAMEGRABBER_H
