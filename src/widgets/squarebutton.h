#ifndef SQUAREBUTTON_H
#define SQUAREBUTTON_H

#include <QWidget>
#include <QToolButton>
#include <QResizeEvent>

class SquareButton : public QToolButton
{
    Q_OBJECT

public:
    explicit SquareButton(QWidget *parent = 0);
    ~SquareButton() {};

private:
//    QSize sizeHint() const override {return QSize(this->geometry().width(), this->geometry().width());}
    void resizeEvent(QResizeEvent *event);
};

#endif // SQUAREBUTTON_H
