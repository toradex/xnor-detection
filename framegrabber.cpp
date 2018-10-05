#include "framegrabber.h"
#include <QDebug>
#include <stdlib.h>

QVideoFilterRunnable *FrameGrabber::createFilterRunnable()
{
    QThread *thread;
    FilterRunnable *filter = new FilterRunnable(this);

    connect(thread, SIGNAL(started()), filter, METHOD(process()));
    return filter;
}

FilterRunnable::FilterRunnable(FrameGrabber *frameGrabber)
    : m_frameGrabber(frameGrabber)
{

}

void FilterRunnable::process(){
    currentFrame->map(QAbstractVideoBuffer::ReadOnly);

    FilterResult *r = new FilterResult;

    if(frameCount==0){
        timerAvg.start();
    }
    timer.restart();

    QByteArray * imgBytes = new QByteArray((const char*)currentFrame->bits(), currentFrame->mappedBytes());

    // pass byte array to XNOR.ai class
    if(!imgBytes->isEmpty() && !imgBytes->isNull()){
            if(loadModel){
                /*** LOAD MODEL BUILT IN ***/
                xerror = xnor_model_load_built_in("", NULL, &xmodel);

                if(xerror != NULL){
                    qDebug() << "xnor_model_load_built_in return error\n"
                             << xnor_error_get_description(xerror);
                }
                loadModel = false;
            }

            /*** CREATE A HANDLE TO IMAGE INPUT ***/
            switch (currentFrame->pixelFormat()) {
            case QVideoFrame::Format_YUV420P:{
                // splits into planes
                uint8_t *y = (uint8_t *)currentFrame->bits(1); // each one
                uint8_t *u = (uint8_t *)currentFrame->bits(2); // of the
                uint8_t *v = (uint8_t *)currentFrame->bits(3); // planes
                xerror = xnor_input_create_yuv420p_image(currentFrame->width(), currentFrame->height(),y, u, v, &xinput);
                break;
            }
            case QVideoFrame::Format_RGB32:{
                xerror = xnor_input_create_rgb_image(currentFrame->width(), currentFrame->height(), (uint8_t *)imgBytes->data(), &xinput);
                break;
            }
            case QVideoFrame::Format_YUYV:{ // YUYV IS YUV422
               xerror = xnor_input_create_yuv422_image(currentFrame->width(), currentFrame->height(), (uint8_t *)imgBytes->data(), &xinput);
                break;
            }
            default:
                break;
            }

            if(xerror != NULL){
                qDebug() << "xnor_input_create_" << currentFrame->pixelFormat() << "image error!\n"
                         << xnor_error_get_description(xerror);
            }

            /*** EVALUATES THE GIVEN MODEL ON THE GIVEN INPUT  ***/
            xerror = xnor_model_evaluate(xmodel, xinput, NULL, &xresult);

            if(xerror != NULL){
                qDebug() << "xnor_model_evaluate error!\n"
                         << xnor_error_get_description(xerror);
            }

            FilterResult *r = new FilterResult;

            /*** GET THE TYPE OF AN EVALUATION RESULT ***/
            xtype = xnor_evaluation_result_get_type(xresult);

            switch (xtype) {
            case 0:{
                qDebug() << "Unknown result type";
                break;
                }
            case 1:{
                //qDebug() << "Bounding Boxes result type";*/

                // clean last patterns detected
                r->m_bboxes.clear();
                r->m_class_ids.clear();
                r->m_confidence.clear();
                r->m_labels.clear();

                out_size = xnor_evaluation_result_get_bounding_boxes(xresult, bbox, MAX_OUT_SIZE);

                xnor_evaluation_result_free(xresult);

                for(int i=0; i<out_size; i++){
                    r->m_bboxes.append(QRect(bbox[i].rectangle.x*(currentFrame->width()), bbox[i].rectangle.y*(currentFrame->height()),
                                             bbox[i].rectangle.width*(currentFrame->width()), bbox[i].rectangle.height*currentFrame->height()));
                    r->m_class_ids.append(bbox[i].class_label.class_id);
                    r->m_confidence.append(bbox[i].class_label.confidence*100);
                    r->m_labels.append(bbox[i].class_label.label);
                }
                frameCount++;
                r->m_fps = 1000/timer.elapsed();
                r->m_deltaT = timer.elapsed();
                r->m_fpsAvg = 1000*frameCount/timerAvg.elapsed();
                emit m_frameGrabber->finished(r);
                break;
                }
            case 2:{
                qDebug() << "Class Labels result type";
                break;
                }
            }
        }


    currentFrame->unmap();

    // free imgBytes
    delete imgBytes;
    imgBytes = NULL;

    // free xnor
    xnor_error_free(xerror);
    xnor_input_free(xinput);
}

QVideoFrame FilterRunnable::run(QVideoFrame *input, const QVideoSurfaceFormat &surfaceFormat, RunFlags flags){
    Q_UNUSED(surfaceFormat);
    Q_UNUSED(flags);

    currentFrame = input;

    process();


    return QVideoFrame();
}

