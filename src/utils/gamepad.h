#ifndef GAMEPAD_H
#define GAMEPAD_H

#include <cmath>
#include <QTimer>
#include <QtGamepad>

//#include "Windows.h"

class Gamepad : public QTimer
{
    Q_OBJECT

    template<class T>
    float normalize(T value, float fromMin, float fromMax, float toMin, float toMax)
    {
        if ((fromMax != fromMin))
            return (static_cast<float>(value)-fromMin) /
               (fromMax-fromMin) * (toMax-toMin) + toMin;
        else
            return 0.0f;
    }

    template<class T>
    float rounded(T value, unsigned int digits=2)
    {
        return static_cast<float>(static_cast<int>(value * pow(10., digits) + 0.5)) / pow(10., digits);
    }

public:
//    QGamepadManager *m_gamepadManager;
    QGamepad *m_gamepad;

    Gamepad(QObject *parent = 0);
    //virtual ~Gamepad();

//    JOYINFOEX joyInfoEx;
//    int gamepadId;

    float x;
    float y;
    float z;
    float r;
//    float u = 0;
//    float v = 0;
//    float pov = 0;
//    unsigned int button = 0;

private:
    QTimer *model;

//    unsigned int xMin = 0;
//    unsigned int xMax = 65535;
//    unsigned int yMin = 0;
//    unsigned int yMax = 65535;
//    unsigned int zMin = 0;
//    unsigned int zMax = 65535;
//    unsigned int rMin = 0;
//    unsigned int rMax = 65535;
//    unsigned int uMin = 0;
//    unsigned int uMax = 65535;
//    unsigned int vMin = 0;
//    unsigned int vMax = 65535;
//    unsigned int povMin = 0;
//    unsigned int povMax = 65535;

    bool initialized;

//    QString initialState = QString("0,0,0,0");
    QString lastState;
//    unsigned int lastButton = 0;

public slots:
    void processOneThing();
    void connectedGamepadsChanged();
//    void axisLeftXChanged(double value);
//    void axisLeftYChanged(double value);
//    void buttonUpChanged(bool value);
//    void buttonDownChanged(bool value);

signals:
    void stateChanged();
    void zeroState();

};

#endif // GAMEPAD_H
