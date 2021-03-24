#include "squarebutton.h"

SquareButton::SquareButton(QWidget *parent) : QToolButton(parent)
{

}

void SquareButton::resizeEvent(QResizeEvent *event)
{
    this->setFixedHeight(this->width());
}
