#include "boundingbox.h"

BoundingBox::BoundingBox()
{

}

BoundingBox::BoundingBox(const BoundingBox &other){
    m_x = other.m_x;
    m_y = other.m_y;
    m_width = other.m_width;
    m_height = other.m_height;
    m_class_id = other.m_class_id;
    m_label = other.m_label;
    m_confidence = other.m_confidence;
}

BoundingBox::BoundingBox(const float &x, const float &y, const float &width, const float &height, const float &confidence, const int &class_id, const std::string &label){
    m_x = x;
    m_y = y;
    m_width = width;
    m_height = height;
    m_class_id = class_id;
    m_label = label;
    m_confidence = confidence;
}

BoundingBox::~BoundingBox(){

}

float BoundingBox::x() const{
    return m_x;
}

float BoundingBox::y() const{
    return m_y;
}

float BoundingBox::width() const{
    return m_width;
}

float BoundingBox::height() const {
    return m_height;
}

float BoundingBox::confidence() const {
    return m_confidence;
}

int BoundingBox::class_id() const {
    return m_class_id;
}

std::string BoundingBox::label() const {
    return m_label;
}

void BoundingBox::setClass_id(const int &class_id){
    if(class_id != m_class_id){
        m_class_id = class_id;
    }
}

void BoundingBox::setConfidence(const float &confidence){
    if(confidence != m_confidence){
        m_confidence = confidence;
    }
}

void BoundingBox::setHeight(const float &height){
    if(height != m_height){
        m_height = height;
    }
}

void BoundingBox::setWidth(const float &width){
    if(width != m_width){
        m_width = width;
    }
}

void BoundingBox::setLabel(const std::string &label){
    if(label != m_label){
        m_label = label;
    }
}

void BoundingBox::setX(const float &x){
    if(x != m_x){
        m_x = x;
    }
}

void BoundingBox::setY(const float &y){
    if(y != m_y){
        m_y = y;
    }
}
