#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <QString>
#include <QMetaType>

class BoundingBox
{
public:
    BoundingBox();
    BoundingBox(const BoundingBox &other);
    BoundingBox(const float &x, const float &y, const float &width, const float &height, const float &confidence, const int &class_id, const std::string &label);
    ~BoundingBox();

    float x() const;
    float y() const;
    float width() const;
    float height() const;
    float confidence() const;
    int class_id() const;
    std::string label() const;

    void setX(const float &x);
    void setY(const float &y);
    void setWidth(const float &width);
    void setHeight(const float &height);
    void setConfidence(const float &confidence);
    void setClass_id(const int &class_id);
    void setLabel (const std::string &label);

private:
    int m_class_id;
    float m_x, m_y, m_width, m_height, m_confidence;
    std::string m_label;
};

Q_DECLARE_METATYPE(BoundingBox);

#endif // BOUNDINGBOX_H
