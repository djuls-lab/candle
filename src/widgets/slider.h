#ifndef SLIDER_H
#define SLIDER_H

#include <QWidget>
#include <QSlider>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QDebug>

class Slider : public QSlider
{
    Q_OBJECT
public:
    explicit Slider(QWidget *parent = 0);

    int currentValue() const;
    void setCurrentValue(int currentValue);

protected:
    void paintEvent(QPaintEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);

private:
    int m_currentValue;
    bool m_isDragging;
};

#endif // SLIDER_H
