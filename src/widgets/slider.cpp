#include "widgets/slider.h"
#include <QRect>
#include <QPoint>
#include <QStyle>
#include <QStyleOptionSlider>

Slider::Slider(QWidget *parent) : QSlider(parent)
{
    m_currentValue = 250;
}

void Slider::paintEvent(QPaintEvent *ev)
{
    QSlider::paintEvent(ev);

    if (this->currentValue() != this->value()) {
//        QString previousStyleSheet = styleSheet();
//        setStyleSheet("QSlider::handle { background: none; }");

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

//        QImage image(":/images/handle2s1.png");
        int pos = ((double)this->width() - 18) / (this->maximum() - this->minimum()) * (this->m_currentValue - this->minimum()) + 9;
//        painter.drawImage(pos - image.width() / 2, (this->height() - image.height()) / 2, image);

        QStyleOptionSlider opt;
        initStyleOption(&opt);

        QRect rect = style()->subControlRect( QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);
        rect.moveTopLeft(QPoint(pos - rect.width() / 2, 0));

        opt.subControls = QStyle::SC_SliderHandle;
        opt.rect = rect;
//        opt.state &= ~QStyle::State_Enabled;

        painter.setOpacity(0.5f);
        QColor brushColor = QColor(Qt::darkGray);
        brushColor.setAlpha(196);
        painter.setBrush(brushColor);
        painter.setPen(QPen(Qt::darkGray, 2));
        painter.drawEllipse(rect.marginsRemoved(QMargins(1, 1, 1, 1)));
//        style()->drawComplexControl(QStyle::CC_Slider, &opt, &painter, this);
//        setStyleSheet(previousStyleSheet);
    }
}

void Slider::mousePressEvent(QMouseEvent *ev)
{
    QSlider::mousePressEvent(ev);

    setValue(QStyle::sliderValueFromPosition(minimum(), maximum(), ev->x(), width()));
    m_isDragging = true;
    this->repaint();
}

void Slider::mouseMoveEvent(QMouseEvent *ev)
{
    QSlider::mouseMoveEvent(ev);

    if (m_isDragging) {
        setValue(QStyle::sliderValueFromPosition(minimum(), maximum(), ev->x(), width()));
    }
    this->repaint();
}

void Slider::mouseReleaseEvent(QMouseEvent *ev)
{
    QSlider::mouseReleaseEvent(ev);

    m_isDragging = false;
    this->repaint();
}

int Slider::currentValue() const
{
    return m_currentValue;
}

void Slider::setCurrentValue(int currentValue)
{
    if (m_currentValue != currentValue) {
        m_currentValue = currentValue;
        this->repaint();
    }
}
