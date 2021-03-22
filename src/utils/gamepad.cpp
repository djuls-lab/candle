#include "gamepad.h"
#include <QtGamepad>

//#include "Windows.h"
#pragma comment(lib,"winmm.lib")

#include <QObject>
#include <QTimer>

#include <QDebug>

Gamepad::Gamepad(QObject *parent) :
    QTimer(parent)
{
    //    auto gamepads = QGamepadManager::instance()->connectedGamepads();
    //    ui->txtConsole->appendPlainText(QString::number(gamepads.size()));
//    connect(QGamepadManager::instance(), &QGamepadManager::connectedGamepadsChanged, this,[]()
//    { qDebug() << "connected gamepads changed:"; }
//    );
//    connect(QGamepadManager::instance(), &QGamepadManager::gamepadConnected, this,[](int deviceId)

//    { qDebug() << "gamepad connected:" << deviceId; }
//    );
//    connect(QGamepadManager::instance(), &QGamepadManager::gamepadDisconnected, this,[](int deviceId)

//    { qDebug() << "gamepad disconnected:" << deviceId; }
//    );



//    connect(QGamepadManager::instance(), &QGamepadManager::gamepadButtonPressEvent, this,[](int deviceId, QGamepadManager::GamepadButton button, double value){
//        qDebug() << "button press event:" << deviceId << button << value; }
//    );
//    m_gamepadManager = QGamepadManager::instance();

//    connect(QGamepadManager::instance(), &QGamepadManager::gamepadButtonReleaseEvent, this,[](int deviceId, QGamepadManager::GamepadButton button){
//        qDebug() << "button release event:" << deviceId << button; }
//    );

//    connect(QGamepadManager::instance(), &QGamepadManager::gamepadAxisEvent, this,[](int deviceId, QGamepadManager::GamepadAxis axis, double value){
//        qDebug() << "axis event:" << deviceId << axis << value; }
//    );

//    connect(QGamepadManager::instance(), &QGamepadManager::buttonConfigured, this,[](int deviceId, QGamepadManager::GamepadButton button)

//    { qDebug() << "button configured:" << deviceId << button; }
//    );
//    connect(QGamepadManager::instance(), &QGamepadManager::axisConfigured, this,[](int deviceId, QGamepadManager::GamepadAxis axis)

//    { qDebug() << "axis configured:" << deviceId << axis; }
//    );
//    connect(QGamepadManager::instance(), &QGamepadManager::configurationCanceled, this,[](int deviceId)

//    { qDebug() << "configuration canceled:" << deviceId; }
//    );

//    unsigned int maxGamepadId = joyGetNumDevs();
//    // qDebug("maxGamepadId: %d", maxGamepadId);

//    gamepadId = -1;

//    ZeroMemory(&joyInfoEx, sizeof(joyInfoEx));
//    joyInfoEx.dwSize = sizeof(joyInfoEx);
//    joyInfoEx.dwFlags = JOY_RETURNALL;

//    for (unsigned int id = 0; id < maxGamepadId; ++id) {
//        MMRESULT result = joyGetPosEx(id, &joyInfoEx);
//        bool isConnected = result == JOYERR_NOERROR ;
//        if (isConnected) {
//                gamepadId = id;
//        }
//    }

//    JOYCAPS capabilities;

//    if (joyGetDevCaps(gamepadId, &capabilities, sizeof(JOYCAPS))
//            == JOYERR_NOERROR) {

//        xMin = capabilities.wXmin;
//        xMax = capabilities.wXmax;
//        yMin = capabilities.wYmin;
//        yMax = capabilities.wYmax;
//        zMin = capabilities.wZmin;
//        zMax = capabilities.wZmax;
//        rMin = capabilities.wRmin;
//        rMax = capabilities.wRmax;
//        uMin = capabilities.wUmin;
//        uMax = capabilities.wUmax;
//        vMin = capabilities.wVmin;
//        vMax = capabilities.wVmax;
//        povMin = 0;
//        povMax = 36000;
//    }

//    if (gamepadId != -1) {
//        qDebug("gamepad detected");

//        connect(this, SIGNAL(timeout()), this, SLOT(processOneThing()));
//        start(75); //start Timer

//    }else {
//        qDebug("no gamepad detected");
//    }

    connectedGamepadsChanged();

    connect(QGamepadManager::instance(), SIGNAL(connectedGamepadsChanged()), this, SLOT(connectedGamepadsChanged()));
}

void Gamepad::connectedGamepadsChanged(){
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
    r = 0.0f;
    initialized = false;
    lastState = QString("0,0,0,0");

    QList<int> connectedGamepadIDs = QGamepadManager::instance()->connectedGamepads();
    qDebug() << connectedGamepadIDs.count() << " gamepad(s) detected";
    if (!connectedGamepadIDs.isEmpty()) {        

        m_gamepad = new QGamepad(connectedGamepadIDs.first(), this);
//        connect(m_gamepad, SIGNAL(axisLeftXChanged(double)), this, SLOT(axisLeftXChanged(double)));
//        connect(m_gamepad, SIGNAL(axisLeftYChanged(double)), this, SLOT(axisLeftYChanged(double)));
//        connect(m_gamepad, SIGNAL(buttonUpChanged(bool)), this, SLOT(buttonUpChanged(bool)));
//        connect(m_gamepad, SIGNAL(buttonDownChanged(bool)), this, SLOT(buttonDownChanged(bool)));
        connect(this, SIGNAL(timeout()), this, SLOT(processOneThing()));
        start(75); //start Timer
    }
}

//void Gamepad::axisLeftXChanged(double value)
//{
////    qDebug() << "axis left X changed: " << value;
////    x = value;
//}

//void Gamepad::axisLeftYChanged(double value)
//{
////    qDebug() << "axis left Y changed: " << value;
////    y = value;
//}

//void Gamepad::buttonUpChanged(bool value)
//{
////    qDebug() << "button up changed: " << value;
////    z = value;
//}

//void Gamepad::buttonDownChanged(bool value)
//{
////    qDebug() << "button down changed: " << value;
////    r = value;
//}

void Gamepad::processOneThing()
{
//    joyGetPosEx(gamepadId, &joyInfoEx);

//    //wait for zero values to start recording state changes
//    if (!initialized) {
//        if (joyInfoEx.dwXpos - 32767 == 0 &&
//            joyInfoEx.dwYpos - 32767 == 0 &&
//            joyInfoEx.dwZpos - 32767 == 0 &&
//            joyInfoEx.dwRpos - 32767 == 0) {
//            initialized = true;
//        }
//    }

//    //get all values
//    x = rounded(normalize(joyInfoEx.dwXpos, xMin, xMax, -1.0f, 1.0f));
//    y = rounded(normalize(joyInfoEx.dwYpos, yMin, yMax, 1.0f, -1.0f));
//    z = rounded(normalize(joyInfoEx.dwZpos, zMin, zMax, -1.0f, 1.0f));
//    r = rounded(normalize(joyInfoEx.dwRpos, rMin, rMax, 1.0f, -1.0f));
//    u = rounded(normalize(joyInfoEx.dwUpos, uMin, uMax, -1.0f, 1.0f));
//    v = rounded(normalize(joyInfoEx.dwVpos, vMin, vMax, -1.0f, 1.0f));
//    pov = rounded(normalize(joyInfoEx.dwPOV, povMin, povMax, 0.0f, 360.0f));
//    button = joyInfoEx.dwButtons;

//    if (m_gamepad->axisLeftX() != 0.0f and m_gamepad->axisLeftX() != false)
//        qDebug() << "axisLeftX: " << m_gamepad->axisLeftX();
//    if (m_gamepad->axisLeftY() != 0.0f and m_gamepad->axisLeftY() != false)
//        qDebug() << "axisLeftY: " << m_gamepad->axisLeftY();
//    if (m_gamepad->axisRightX() != 0.0f and m_gamepad->axisRightX() != false)
//        qDebug() << "axisRightX: " << m_gamepad->axisRightX();
//    if (m_gamepad->axisRightY() != 0.0f and m_gamepad->axisRightY() != false)
//        qDebug() << "axisRightY: " << m_gamepad->axisRightY();
//    if (m_gamepad->buttonA() != 0.0f and m_gamepad->buttonA() != false)
//        qDebug() << "buttonA: " << m_gamepad->buttonA();
//    if (m_gamepad->buttonB() != 0.0f and m_gamepad->buttonB() != false)
//        qDebug() << "buttonB: " << m_gamepad->buttonB();
//    if (m_gamepad->buttonCenter() != 0.0f and m_gamepad->buttonCenter() != false)
//        qDebug() << "buttonCenter: " << m_gamepad->buttonCenter();
//    if (m_gamepad->buttonDown() != 0.0f and m_gamepad->buttonDown() != false)
//        qDebug() << "buttonDown: " << m_gamepad->buttonDown();
//    if (m_gamepad->buttonGuide() != 0.0f and m_gamepad->buttonGuide() != false)
//        qDebug() << "buttonGuide: " << m_gamepad->buttonGuide();
//    if (m_gamepad->buttonL1() != 0.0f and m_gamepad->buttonL1() != false)
//        qDebug() << "buttonL1: " << m_gamepad->buttonL1();
//    if (m_gamepad->buttonL2() != 0.0f and m_gamepad->buttonL2() != false)
//        qDebug() << "buttonL2: " << m_gamepad->buttonL2();
//    if (m_gamepad->buttonL3() != 0.0f and m_gamepad->buttonL3() != false)
//        qDebug() << "buttonL3: " << m_gamepad->buttonL3();
//    if (m_gamepad->buttonLeft() != 0.0f and m_gamepad->buttonLeft() != false)
//        qDebug() << "buttonLeft: " << m_gamepad->buttonLeft();
//    if (m_gamepad->buttonR1() != 0.0f and m_gamepad->buttonR1() != false)
//        qDebug() << "buttonR1: " << m_gamepad->buttonR1();
//    if (m_gamepad->buttonR2() != 0.0f and m_gamepad->buttonR2() != false)
//        qDebug() << "buttonR2: " << m_gamepad->buttonR2();
//    if (m_gamepad->buttonR3() != 0.0f and m_gamepad->buttonR3() != false)
//        qDebug() << "buttonR3: " << m_gamepad->buttonR3();
//    if (m_gamepad->buttonRight() != 0.0f and m_gamepad->buttonRight() != false)
//        qDebug() << "buttonRight: " << m_gamepad->buttonRight();
//    if (m_gamepad->buttonSelect() != 0.0f and m_gamepad->buttonSelect() != false)
//        qDebug() << "buttonSelect: " << m_gamepad->buttonSelect();
//    if (m_gamepad->buttonStart() != 0.0f and m_gamepad->buttonStart() != false)
//        qDebug() << "buttonStart: " << m_gamepad->buttonStart();
//    if (m_gamepad->buttonUp() != 0.0f and m_gamepad->buttonUp() != false)
//        qDebug() << "buttonUp: " << m_gamepad->buttonUp();
//    if (m_gamepad->buttonX() != 0.0f and m_gamepad->buttonX() != false)
//        qDebug() << "buttonX: " << m_gamepad->buttonX();
//    if (m_gamepad->buttonY() != 0.0f and m_gamepad->buttonY() != false)
//        qDebug() << "buttonY: " << m_gamepad->buttonY();

//    x = rounded(normalize(m_gamepad->buttonR2(), 0.0f, -1.0f, -1.0f, 1.0f));
    x = rounded(normalize(m_gamepad->axisLeftX(), -1.0f, 1.0f, -1.0f, 1.0f));
    y = rounded(normalize(m_gamepad->axisLeftY(), 1.0f, -1.0f, -1.0f, 1.0f));
    z = rounded(normalize(1 - m_gamepad->buttonR2(), 0.0f, 1.0f, -1.0f, 1.0f));
    r = rounded(normalize(m_gamepad->buttonL2(), 0.0f, 1.0f, -1.0f, 1.0f));

    // wait for 0 values
    if (!initialized) {
        if (x == 0 &&
            y == 0 &&
            z == 0 &&
            r == 0) {
            initialized = true;
        }
    }

    QString state = QString("%1,%2,%3,%4")
            .arg((double)(x))
            .arg((double)(y))
            .arg((double)(z))
            .arg((double)(r));



//    //qDebug() << currentState;
//    if (state != "0 0 0 0")


//    if ((state != initialState || button != lastButton) && initialized) {
    QString initialState = QString("0,0,0,0");

    if (state != initialState && initialized) {
//    if ((state != initialState || button != lastButton) && (int)initOffset == 0) {
        qDebug() << "state: " << state;
        emit stateChanged();
    }else {
        if (state != lastState) {
            emit zeroState();
        }
    }
    lastState = state;
//    lastButton = button;
}
