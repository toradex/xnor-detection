#ifndef VIDEOOVERLAY_H
#define VIDEOOVERLAY_H

#include <QObject>
#include <QProcess>

class VideoOverlay : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)
public:
    explicit VideoOverlay(QObject *parent=nullptr, QString source="");

    QString source();
    void setSource(const QString &source);

    Q_INVOKABLE void init();

signals:
    void sourceChanged();

private:
    QString m_source;
};

#endif // VIDEOOVERLAY_H
