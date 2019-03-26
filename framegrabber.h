/****************************************************************************
**
** Copyright (C) 2019 Toradex Ag
** Contact: https://www.toradex.com/locations
**
** This file is part of the Toradex and XNOR people detection sample.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Toradex Ag nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

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
