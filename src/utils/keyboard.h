#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QWidget>
#include <QStackedWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QList>
#include <QMainWindow>
#include <QHBoxLayout>

//#define BTN_WIDTH 64
//#define BTN_HEIGHT 64

class KeyBoard : public QWidget
{
    Q_OBJECT
public:
//    explicit KeyBoard(QWidget *parent = 0);
    KeyBoard(QWidget *parent = 0);
    ~KeyBoard();

    int btnWidth;
    int btnHeight;

protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);

private slots:
    void focusChanged(QWidget *, QWidget *nowWidget);
    void slotBtnClicked();

private:
    int deskWidth;
    int deskHeight;

    QPoint mousePoint;
    bool mousePressed;
    void initWindow();
    void initForm();
    void close();
    void toggleKeys();

    QWidget *currentInputWidget;
    bool isUpper;
    bool showSigns;
    void switchCase();
//    void focusMainWidget();

//    QStackedWidget *keyWindow;
//    QWidget *letterWindow;
//    QWidget *signWindow;
//    QLabel *infoLabel;

    QPushButton *closeBtn;
    QPushButton *delBtn;
    QPushButton *capsBtn;
    QPushButton *signsBtn;
    QPushButton *spaceBtn;
    QPushButton *enterBtn;
    QPushButton *upBtn;
    QPushButton *downBtn;
    QPushButton *leftBtn;
    QPushButton *rightBtn;
    QPushButton *dotBtn;

    QList<QPushButton *> numericButtons;

    QList<QPushButton *> alphaButtons;

    QList<QPushButton *> signButtons;

    QPushButton* createKey(QString type, QString icon, QString text, int fixedWidth, int fixedHeight);
};

#endif // KEYBOARD_H
