#include "gamepad.h"

#include "Windows.h"
#pragma comment(lib,"winmm.lib")

#include <QObject>
#include <QTimer>

#include <QDebug>

Gamepad::Gamepad(QObject *parent) :
    QTimer(parent)
{
    unsigned int maxGamepadId = joyGetNumDevs();
    // qDebug("maxGamepadId: %d", maxGamepadId);

    gamepadId = -1;

    ZeroMemory(&joyInfoEx, sizeof(joyInfoEx));
    joyInfoEx.dwSize = sizeof(joyInfoEx);
    joyInfoEx.dwFlags = JOY_RETURNALL;

    for (unsigned int id = 0; id < maxGamepadId; ++id) {
        MMRESULT result = joyGetPosEx(id, &joyInfoEx);
        bool isConnected = result == JOYERR_NOERROR ;
        if (isConnected) {
                gamepadId = id;
        }
    }

    JOYCAPS capabilities;

    if (joyGetDevCaps(gamepadId, &capabilities, sizeof(JOYCAPS))
            == JOYERR_NOERROR) {

        xMin = capabilities.wXmin;
        xMax = capabilities.wXmax;
        yMin = capabilities.wYmin;
        yMax = capabilities.wYmax;
        zMin = capabilities.wZmin;
        zMax = capabilities.wZmax;
        rMin = capabilities.wRmin;
        rMax = capabilities.wRmax;
        uMin = capabilities.wUmin;
        uMax = capabilities.wUmax;
        vMin = capabilities.wVmin;
        vMax = capabilities.wVmax;
        povMin = 0;
        povMax = 36000;
    }

    if (gamepadId != -1) {
        qDebug("gamepad detected");

        connect(this, SIGNAL(timeout()), this, SLOT(processOneThing()));
        start(75); //start Timer

    }else {
        qDebug("no gamepad detected");
    }
}

void Gamepad::processOneThing()
{
    joyGetPosEx(gamepadId, &joyInfoEx);

    //wait for zero values to start recording state changes
    if (!initialized) {
        if (joyInfoEx.dwXpos - 32767 == 0 &&
            joyInfoEx.dwYpos - 32767 == 0 &&
            joyInfoEx.dwZpos - 32767 == 0 &&
            joyInfoEx.dwRpos - 32767 == 0) {
            initialized = true;
        }
    }

    //get all values
    x = rounded(normalize(joyInfoEx.dwXpos, xMin, xMax, -1.0f, 1.0f));
    y = rounded(normalize(joyInfoEx.dwYpos, yMin, yMax, 1.0f, -1.0f));
    z = rounded(normalize(joyInfoEx.dwZpos, zMin, zMax, -1.0f, 1.0f));
    r = rounded(normalize(joyInfoEx.dwRpos, rMin, rMax, 1.0f, -1.0f));
    u = rounded(normalize(joyInfoEx.dwUpos, uMin, uMax, -1.0f, 1.0f));
    v = rounded(normalize(joyInfoEx.dwVpos, vMin, vMax, -1.0f, 1.0f));
    pov = rounded(normalize(joyInfoEx.dwPOV, povMin, povMax, 0.0f, 360.0f));
    button = joyInfoEx.dwButtons;


    QString state = QString("%1,%2,%3,%4")
            .arg((int)(x * 100))
            .arg((int)(y * 100))
            .arg((int)(z * 100))
            .arg((int)(r * 100));



    //qDebug() << currentState;
    //qDebug() << "state: " << state;

    if ((state != initialState || button != lastButton) && initialized) {
//    if ((state != initialState || button != lastButton) && (int)initOffset == 0) {
        emit stateChanged();
    }else {
        if (state != lastState) {
            emit zeroState();
        }
    }
    lastState = state;
    lastButton = button;
}
