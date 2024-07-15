#ifndef CONSTANTS_H
#define CONSTANTS_H

#define STATE_OFF   0
#define STATE_ON    1
#define STATE_FAULT 2

#define Q_DECLARE_ROTATION \
    Q_PROPERTY(Rotation      rotation READ rotation      WRITE setRotation); \
    \
    public: \
        enum Rotation {       \
            NoRotation = 0,   \
            Rotate90   = 90,  \
            Rotate180  = 180, \
            Rotate270  = 270  \
        }; \
        \
        Q_ENUM(Rotation) \
        \
        Rotation rotation() const \
        { \
            return m_rotation; \
        } \
        \
        void setRotation(const Rotation angle) \
        { \
            m_rotation = angle; \
            update(); \
        } \
    \
    private: \
        Rotation m_rotation;

#define Q_DECLARE_FLIP \
    Q_PROPERTY(FlipDirection flip     READ flipDirection WRITE setFlipDirection); \
    \
    public: \
        enum FlipDirection { \
            NoFlip, \
            Horizontal, \
            Vertical \
        }; \
        \
        Q_ENUM(FlipDirection); \
        \
        FlipDirection flipDirection() const \
        { \
            return m_flip; \
        } \
        void setFlipDirection(const FlipDirection direction) \
        { \
            m_flip = direction; \
            update(); \
        } \
    \
    private: \
        FlipDirection m_flip;

#define Q_IMPLEMENT_FLIP \
    QTransform t; \
    if (m_flip == FlipDirection::Vertical) { \
        t.translate(width, 0); \
        t.scale(-1, 1); \
        painter.setTransform(t);\
    } \
    else if (m_flip == FlipDirection::Horizontal) { \
        t.translate(0, height); \
        t.scale(1, -1); \
        painter.setTransform(t); \
    } \
    else { \
        t.scale(1, 1); \
        painter.setTransform(t); \
    } \

#define Q_IMPLEMENT_ROTATION \
    int angle = (int) m_rotation; \
    bool rotated = false; \
    if (angle != Rotation::NoRotation) { \
        painter.translate(width / 2, height / 2); \
        painter.rotate(angle); \
        painter.translate(-width / 2, -height / 2); \
        rotated = true; \
    } \
    else { \
        if (rotated) { \
            painter.translate(width / 2, height / 2); \
            painter.rotate(-1 * angle); \
            painter.translate(-width / 2, -height / 2); \
            rotated = false; \
        } \
    } \


#endif // CONSTANTS_H
