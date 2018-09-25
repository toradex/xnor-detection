#ifndef FRAMEGRABBER_H
#define FRAMEGRABBER_H

#include <QAbstractVideoFilter>
#include <QVideoSurfaceFormat>
#include <QString>
#include <QByteArray>
#include <QVideoFrame>
#include <boundingbox.h>
#include <QVariant>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define MIN_WIDTH 100
#define MIN_HEIGHT 100

/*
 struct BoundingBox{
    float x;
    float y;
    float width;
    float height;
    std::int32_t class_id;
    std::string label;
    float confidence;
} ;

*/

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

    int index=0;
    QImage imageWrapper(const QVideoFrame &frame);
    const QVector<QString> labels = {"Cat", "Dog", "Turtle", "Person", "Tordy", "Alien"};

private:
    FrameGrabber *m_frameGrabber;
    bool m_yuv;
};

class FilterResult : public QObject
{
    Q_OBJECT

public slots:
    QVariantList bboxes() const {return m_bboxes;} // contains the rects
    QVariantList labels() const {return m_labels;} // contains the labels
    QVariantList classIds() const {return m_class_ids;} // contains the class ids
    QVariant confidences() const {return m_confidence;}

private:
    QVariantList m_bboxes, m_labels, m_class_ids, m_confidence;
    friend class FilterRunnable;
};

#endif // FRAMEGRABBER_H
