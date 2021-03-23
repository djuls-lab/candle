#include <QDesktopWidget>
#include <QApplication>
#include <QStackedWidget>
#include <QMouseEvent>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QWindow>
#include <QScreen>
#include <QInputEvent>

#include "keyboard.h"

KeyBoard::KeyBoard(QWidget *parent) :
    QWidget(parent)
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    deskWidth = screenGeometry.width();
    deskHeight = screenGeometry.height();
//    frmWidth = this->width();
//    frmHeight = this->height();

    btnWidth = (deskWidth - 12 * 12) / 11;
    btnHeight = (deskHeight - 6 * 12)/ 2 / 5;

    this->initWindow();
    this->initForm();
    this->setVisible(false);
}

KeyBoard::~KeyBoard()
{
}

void KeyBoard::mouseMoveEvent(QMouseEvent *e)
{
    if (mousePressed && (e->buttons() & Qt::LeftButton))
    {
        this->move(e->globalPos() - mousePoint);
        this->repaint();
        e->accept();
    }
}

void KeyBoard::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void KeyBoard::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;
}

void KeyBoard::focusChanged(QWidget *, QWidget *widget)
{
    if (widget != 0 && !this->isAncestorOf(widget))
    {        
        currentInputWidget = 0;
        if (widget->inherits("QLineEdit")) {
            QLineEdit *lineEdit = (QLineEdit *)widget;
            if (!lineEdit->isReadOnly())
                currentInputWidget = lineEdit;
        }
        else if (widget->inherits("QComboBox")) {
            QComboBox *comboBox = (QComboBox*)widget;
            if (comboBox->isEditable())
                currentInputWidget = comboBox;
        }
        else if (widget->inherits("QDoubleSpinBox")) {
            QDoubleSpinBox *doubleSpinBox = (QDoubleSpinBox*)widget;
            if (!doubleSpinBox->isReadOnly())
                currentInputWidget = doubleSpinBox;
        }

        if (currentInputWidget != 0) {
            QPoint pos = currentInputWidget->mapToGlobal(currentInputWidget->rect().center());

//            qDebug() << "pos: " << pos;

            QPoint movePoint;

            // Mouse click position coordinates
//            if (QCursor::pos().y() > deskHeight / 2)
            if (pos.y() > deskHeight / 2)
            {
                // Top display
                movePoint = parentWidget()->mapToGlobal(QPoint(0, 0));
            }
            else
            {
                // Bottom display
                // movePoint = QPoint(0, deskHeight - frmHeight);
                movePoint = parentWidget()->mapToGlobal(QPoint(0, deskHeight - height()));
            }

            this->move(movePoint);
            this->repaint();
//            qApp->inputMethod()->hide(); // TEST !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            this->setVisible(true);
        }
        else {
            currentInputWidget = 0;
            this->setVisible(false);
            // Need to switch the input method to the original original state - lowercase
            isUpper = true;
            switchCase();
            keyWindow->setCurrentIndex(0);
        }
    }
}


QPushButton* KeyBoard::createKey(QString name, QString icon, QString text, int fixedWidth=0, int fixedHeight=0) {
    QPushButton *button = new QPushButton(this);
//    button->setProperty("type", name.toStdString().c_str());
    if (name != "") {
        button->setObjectName(name);
    }
    if (icon != "") {
        button->setIcon(QIcon(icon));
        button->setIconSize(QSize(48, 48));
    }
    button->setText(text);
    button->setFixedSize(fixedWidth == 0 ? btnWidth : fixedWidth , fixedHeight == 0 ? btnHeight : fixedHeight);
//    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    return button;
}

//void KeyBoard::focusMainWidget()
//{
//    foreach(QWidget *widget, qApp->topLevelWidgets())
//        if (QMainWindow *mainWindow = static_cast<QMainWindow*>(widget))
//            mainWindow->centralWidget()->setFocus();
//}


void KeyBoard::slotBtnClicked()
{
    QPushButton *btn = (QPushButton *)sender();
//    QString name = btn->property("type").toString();
    QString name = btn->objectName();

//    if (name != "num" && name != "alpha" && name != "sign") {
//    if (name == "close" || name == "caps" || name == "switch" || name != "backspace") {
//        qDebug() << "btnType: " << name;

    if (name == "close") {

//            focusMainWidget();
//            this->parentWidget()->setFocus();  // TEST !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//            this->setVisible(false);
//            isUpper = true;
//            switchCase();
//            keyWindow->setCurrentIndex(0);
        close();
    }
    else if (name == "caps") {
        isUpper = !isUpper;
        keyWindow->setCurrentIndex(0);
        switchCase();
    }
    else if (name == "switch") {
        if (keyWindow->currentIndex() == 0) {
            keyWindow->setCurrentIndex(1);
            signalBtn->setText("ABC");
        }
        else {
            keyWindow->setCurrentIndex(0);
            signalBtn->setText("#+=");
        }
    }
    else if (name == "backspace") {
        if (currentInputWidget != 0)
        {
//               currentInputWidget->backspace();
//               currentInputWidget->activateWindow(); // TEST !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            qApp->postEvent(currentInputWidget, new QKeyEvent(QEvent::KeyPress, Qt::Key_Backspace, Qt::NoModifier));
        }
    }
    else if (name == "enter") {
        if (currentInputWidget != 0)
        {
            qApp->postEvent(currentInputWidget, new QKeyEvent(QEvent::KeyPress, Qt::Key_Return, Qt::NoModifier));

            close();
        }
    }
//    }
    else
    {
        QString value = btn->text();
        // If it is the & button, because the corresponding & is filtered, the real text is to remove the previous & character
        if (value == "&&")
        {
            value = value.right(1);
        }
        if (currentInputWidget != 0)
        {
//            currentInputWidget->insert(value);
//            currentInputWidget->activateWindow(); // TEST !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            qApp->postEvent(currentInputWidget, new QKeyEvent(QEvent::KeyPress, Qt::Key_Any, Qt::NoModifier, value));
        }
    }
}


void KeyBoard::close(){
    this->parentWidget()->setFocus();  // TEST !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    this->setVisible(false);
    isUpper = true;
    switchCase();
    keyWindow->setCurrentIndex(0);
}


void KeyBoard::initWindow()
{
//    this->setProperty("form", true);
//    this->setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
//    this->setFixedSize(11 * BTN_SIZE, 5 * BTN_SIZE);
    this->setWindowFlags(Qt::Dialog | Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint | Qt::FramelessWindowHint);
    this->setFixedSize(deskWidth, deskHeight / 2);
    this->setFocusPolicy(Qt::NoFocus);
    this->setAttribute(Qt::WA_X11DoNotAcceptFocus, true); // TEST !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    this->setAttribute(Qt::WA_ShowWithoutActivating, true); // TEST !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    keyWindow = new QStackedWidget(this);
//    keyWindow->setFixedSize(10 * BTN_SIZE, 4 * BTN_SIZE);
    keyWindow->setContentsMargins(0, 0, 0, 0);
    letterWindow = new QWidget;
    signWindow = new QWidget;


    // Add function button
    closeBtn = createKey("close", ":/images/hidekeyboard.svg", "");

    // Delete a character
    delBtn = createKey("backspace", ":/images/backspace.svg", ""); //, 2 * (btnWidth + 12) - 12);

    // Change the input type: uppercase, lowercase
    typeBtn = createKey("caps", ":/images/capslock.svg", "", 2 * (btnWidth + 12) - (12 / 2 + 1));

    // Change character or letter input
    signalBtn = createKey("switch", "", "#+=", 2 * (btnWidth + 12) - (12 / 2 + 1));

    // Change character or letter input
    enterBtn = createKey("enter", ":/images/enter.svg", "", 2 * (btnWidth + 12) - 12, 2 * (btnHeight + 12) - 12);


    const QList<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    for (int i=0; i<numbers.size(); i++ ) {
        numericButtons << createKey("num", "", QString::number(numbers[i]));
    }


    // Fill in the alphabet keyboard
    const QString alphas = "azertyuiopqsdfghjklmwxcvbn";
    for (int i=0; i<alphas.size(); i++ ) {
        alphaButtons << createKey("alpha", "", alphas[i]);
    }


    //Space
    btnSpace = createKey("alpha", "", " ", 7 * (btnWidth + 12) - 12);

    QGridLayout *letterLayout = new QGridLayout;

    int i = 0;
    for (int j=0; j<10; j++) {
        letterLayout->addWidget(alphaButtons[i], 0, j, 1, 1);
        i++;
    }
    for (int j=0; j<9; j++) {
        letterLayout->addWidget(alphaButtons[i], 1, j + 1, 1, 1);
        i++;
    }
    for (int j=0; j<7; j++) {
        letterLayout->addWidget(alphaButtons[i], 2, j + 1, 1, 1);
        i++;
    }

    letterLayout->addWidget(btnSpace,3,1,1,7);
    // Set row and column spacing
    letterLayout->setSpacing(12);

    // Set and frame spacing
    letterLayout->setContentsMargins(0, 0, 0, 0);
    letterWindow->setLayout(letterLayout);


    const QList<QString> signs = {"!","@","#","$","%","^","&&","*","(",")",",",".","?","~","_","-","+","/","=","[","]","{","}","|","\\","'"};
    for (int i=0; i<signs.size(); i++ ) {
        signButtons << createKey("sign", "", signs[i]);
    }

    //Space
    btnSpace = createKey("alpha", "", " ", 7 * (btnWidth + 12) - 12);

    QGridLayout *signLayout = new QGridLayout;

    i = 0;
    for (int j=0; j<10; j++) {
        signLayout->addWidget(signButtons[i], 0, j, 1, 1);
        i++;
    }
    for (int j=0; j<9; j++) {
        signLayout->addWidget(signButtons[i], 1, j + 1, 1, 1);
        i++;
    }
    for (int j=0; j<7; j++) {
        signLayout->addWidget(signButtons[i], 2, j + 1, 1, 1);
        i++;
    }


    signLayout->addWidget(btnSpace,3,1,1,7);
    // Set row and column spacing
    signLayout->setSpacing(12);

    // Set and frame spacing
    signLayout->setContentsMargins(0, 0, 0, 0);
    signWindow->setLayout(signLayout);

    keyWindow->addWidget(letterWindow);
    keyWindow->addWidget(signWindow);
    keyWindow->setCurrentIndex(0);

    // Global layout
    QGridLayout *layout = new QGridLayout;

    for (int i=0; i<numericButtons.size(); i++) {
//        layout->addWidget(numericButtons[i],0,i+1,1, 1);
        layout->addWidget(numericButtons[i],0,i,1, 1);
    }

//    layout->addWidget(delBtn,   3,9,1,2);
    layout->addWidget(delBtn,   0,10,1,1);
//    layout->addWidget(closeBtn, 0,0,1,1);
    layout->addWidget(closeBtn, 4,0,1,1);
    layout->addWidget(typeBtn,  2,0,1,1);
    layout->addWidget(signalBtn,3,0,1,2);
    layout->addWidget(keyWindow,1,1,4,10);
    layout->addWidget(enterBtn, 3,9,2,2);
    layout->setSpacing(12);
    layout->setContentsMargins(12, 12, 12, 12);
    this->setLayout(layout);

    this->setStyleSheet(QString("QWidget { background-color: rgb(48, 48, 48); } QPushButton { background-color: black; color: white; } QPushButton:hover { background-color: palette(highlight); } #close { background-color: rgb(16, 16, 16); } #backspace { background-color: red; }"));
}

void KeyBoard::initForm()
{
    currentInputWidget = 0;
    mousePressed = false;
    isUpper = false;
    switchCase();

    QList<QPushButton *> btn = this->findChildren<QPushButton *>();
    foreach (QPushButton * b, btn) {
        connect(b, SIGNAL(clicked()), this, SLOT(slotBtnClicked()));
    }

    // Bind to change the focus signal slot globally
    connect(qApp, SIGNAL(focusChanged(QWidget *, QWidget *)),
            this, SLOT(focusChanged(QWidget *, QWidget *)));
}

void KeyBoard::switchCase()
{
//    isUpper ? typeBtn->setText(tr("Lower")) : typeBtn->setText(tr("Upper"));
    isUpper ? typeBtn->setIcon(QIcon(":/images/shift.svg")) : typeBtn->setIcon(QIcon(":/images/capslock.svg"));
    foreach (QPushButton *button, alphaButtons) {
        isUpper ? button->setText(button->text().toUpper()) : button->setText(button->text().toLower());
    }
}
