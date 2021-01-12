// This file is a part of "Candle" application.
// Copyright 2015-2016 Hayrullin Denis Ravilevich

#include <QApplication>
#include <QDebug>
#include <QGLWidget>
#include <QLocale>
#include <QTranslator>
#include <QFile>
#include <QStyleFactory>
#include <QFontDatabase>
#include <QMessageBox>

#include "parser/gcodepreprocessorutils.h"
#include "parser/gcodeparser.h"
#include "parser/gcodeviewparse.h"

#include "frmmain.h"

int main(int argc, char *argv[])
{
#ifdef UNIX
    bool styleOverrided = false;
    for (int i = 0; i < argc; i++) if (QString(argv[i]).toUpper() == "-STYLE") {
        styleOverrided = true;
        break;
    }
#endif

    QApplication a(argc, argv);

//    QFontDatabase::addApplicationFont(":/fonts/segoeui.ttf");
//    QFontDatabase::addApplicationFont(":/fonts/tahoma.ttf");

#ifdef GLES
    QFontDatabase::addApplicationFont(":/fonts/Ubuntu-R.ttf");
#endif

    QGLFormat glf = QGLFormat::defaultFormat();
    glf.setSampleBuffers(true);
    glf.setSamples(8);
    QGLFormat::setDefaultFormat(glf);

//    QLocale::setDefault(QLocale("es"));

    QString loc = QLocale().name().left(2);
    QString translationsFolder = qApp->applicationDirPath() + "/translations/";
    QString translationFileName = translationsFolder + qApp->applicationDisplayName() + "_" + loc + ".qm";

    qDebug() << "locale:" << loc;

    if(QFile::exists(translationFileName)) {
        QTranslator* translator = new QTranslator();
        if (translator->load(translationFileName)) a.installTranslator(translator); else delete translator;
    }

    QString baseTranslationFileName = translationsFolder + "qt_" + loc + ".qm";

    if(QFile::exists(translationFileName)) {
        QTranslator* baseTranslator = new QTranslator();
        if (baseTranslator->load(baseTranslationFileName)) a.installTranslator(baseTranslator); else delete baseTranslator;
    }

    a.setApplicationVersion(APP_VERSION);

#ifdef UNIX
    if (!styleOverrided) foreach (QString str, QStyleFactory::keys()) {
        qDebug() << "style" << str;
        if (str.contains("GTK+")) {
            a.setStyle(QStyleFactory::create(str));
            break;
        }
    }
#endif

#ifdef GLES
    a.setStyle(QStyleFactory::create("Fusion"));
    QPalette palette;
    palette.setColor(QPalette::Highlight, QColor(204, 204, 254));
    palette.setColor(QPalette::HighlightedText, QColor(0, 0, 0));
    a.setPalette(palette);

    a.setStyleSheet("QWidget {font-family: \"Ubuntu\";}\
                    QMenuBar {background-color: #303030; padding-top: 2px; padding-bottom: 2px;}\
                    QMenuBar::item {spacing: 3px; padding: 2px 8px; background: transparent; color: white;}\
                    QMenuBar::item:pressed {border: 1px solid #505050; border-bottom: 1px; border-top-left-radius: 3px; border-top-right-radius: 3px; background: #404040; color: white;}\
                    QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white;}\
                    QDialog {border: 1px solid palette(mid);}");

#endif    

    a.setStyle(QStyleFactory::create("Fusion"));
    // a.setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");
//    a.setStyleSheet(a.styleSheet() + R"(
//    #cmdHome { qproperty-icon: url(:/images/home.png); }
//    #cmdTouch { qproperty-icon: url(:/images/touch.png); }
//    #cmdZeroXY { qproperty-icon: url(:/images/zeroXY.png); }
//    #cmdZeroZ { qproperty-icon: url(:/images/zeroZ.png); }
//    #cmdRestoreOrigin { qproperty-icon: url(:/images/restoreOrigin.png); }
//    #cmdSafePosition { qproperty-icon: url(:/images/safePosition.png); }
//    #cmdReset { qproperty-icon: url(:/images/reset.png); }
//    #cmdUnlock { qproperty-icon: url(:/images/unlock.png); }
//    #cmdXMinus { qproperty-icon: url(:/images/xMinus.png); }
//    #cmdYPlus { qproperty-icon: url(:/images/yPlus.png); }
//    #cmdYMinus { qproperty-icon: url(:/images/yMinus.png); }
//    #cmdStop { qproperty-icon: url(:/images/stop.png); }
//    #cmdXPlus { qproperty-icon: url(:/images/xPlus.png); }
//    #cmdZPlus { qproperty-icon: url(:/images/zPlus.png); }
//    #cmdZMinus { qproperty-icon: url(:/images/zMinus.png); }
//    #cmdUser0 { qproperty-icon: url(:/images/user0.png); }
//    #cmdUser1 { qproperty-icon: url(:/images/user1.png); }
//    #cmdUser2 { qproperty-icon: url(:/images/user2.png); }
//    #cmdUser3 { qproperty-icon: url(:/images/user3.png); }
//    #cmdSpindle { qproperty-icon: url(:/images/spindle.png); }
//    #cmdCommandSend { qproperty-icon: url(:/images/commandSend.png); }
//    #cmdClearConsole { qproperty-icon: url(:/images/clearConsole.png); }

//    #cmdRefresh { qproperty-icon: url(:/images/reset.png); }
//    )");
//      a.setStyleSheet(a.styleSheet() + R"(
//        #cboCommand QComboBox {
//            padding-top: 3;
//            padding-bottom: 3;
//            padding-right: 8;
//        }

//        #cboCommand QComboBox::drop-down {
//            border: none;
//            width: 0px;
//        }

//        #cboCommand QComboBox::down-arrow {
//            image: none;
//            border: none;
//            width: 0px;
//        }
//      )");

    // a.setStyleSheet(a.styleSheet() + "#splitPanels QSplitter::handle { background-image: url(:/images/handle_small.png); }");

//    a.setStyleSheet(a.styleSheet() + R"(
//    /*QWidget {
//        font-size: 9pt;
//    }*/

//    QSpinBox, QDoubleSpinBox {
//        padding-top: 1px;
//        padding-bottom: 1px;
//    }

//    QGroupBox {
//    }

//    QGroupBox:disabled {
//        color: palette(shadow);
//    }

//    QGroupBox[overrided="true"] {
//        color: red;
//    }

//    QGroupBox[overrided="false"] {
//        color: palette(windowtext);
//    }

//    QGroupBox[checkable="true"]::title {
//        margin-top: 1px;
//    }

//    QGroupBox[checkable="true"]::indicator {
//        padding: 0 -2 -0 2;
//        width: 13;
//        height: 13;
//    }

//    QGroupBox[checkable="true"]::indicator:checked {
//        image: url(:/images/collapse.png);
//    }

//    QGroupBox[checkable="true"]::indicator:unchecked {
//        image: url(:/images/expand.png);
//    }

//    QFrame#frameManualControlXY,#frameManualControlZ {
//        border: 1px solid lightgray;
//        border-radius: 4px;
//    }

//    QSplitter::handle {
//        background-repeat: no-repeat;
//        background-position: center center;
//    }

//    QSplitter::handle:vertical {
//        background-image: url(":/images/handle_horizontal.png");
//    }
//    /*
//    QSplitter::handle:horizontal {
//        background-image: url(":/images/handle_vertical.png");
//    }
//    */
//    QTableView {
//        selection-background-color: #cdcdff;
//        selection-color: rgb(0, 0, 0);
//    }

//    QSlider::horizontal {
//        padding-top: 1px;
//        padding-bottom: 1px;
//    }

//    QSlider::groove:horizontal {
//        border: 1px solid #999999;
//        height: 2px;
//        background: #8f8f91;
//        margin: 2px 0;
//    }

//    QSlider::handle:horizontal {
//        background-image: url(:/images/handle2s.png);
//        border: 0px;
//        width: 16px;
//        margin: -7px 0;
//    }

//    QSlider::handle:horizontal:hover {
//        background-image: url(:/images/handle2sh.png);
//    }

//    /*QSlider::sub-page:horizontal {
//        background: red;
//        margin: 1px 0;
//    }*/

//    QWidget { font-size: 8pt; }

//    QSplitter::handle { background-image: url(:/images/handle_small.png); }

//    )");

    frmMain w;
    w.show();

//    qDebug() << GcodePreprocessorUtils::overrideSpeed("G0 X0 Y10 Z200 F123", 50);
//    qDebug() << GcodePreprocessorUtils::removeComment("G1 X10 ((test comment 1))");
//    qDebug() << GcodePreprocessorUtils::removeComment("G1 X10 ;;test comment 2");
//    qDebug() << GcodePreprocessorUtils::parseComment("G1 X10 ((test comment 1))");
//    qDebug() << GcodePreprocessorUtils::parseComment("G1 X10 ;;test comment 2");
//    qDebug() << GcodePreprocessorUtils::truncateDecimals(1, "G0 X123.4456 Y3.12345 Z0.5");
//    qDebug() << GcodePreprocessorUtils::removeAllWhitespace("   test spaces   ");
//    qDebug() << GcodePreprocessorUtils::parseCodes(QString("G0 X123.4456 Y3.12345 Z0.5").split(' '), 'X');
//    qDebug() << GcodePreprocessorUtils::parseGCodes("G0 G02 G12 G3 G021 M03");
//    qDebug() << GcodePreprocessorUtils::parseMCodes("G0 G02 G12 G3 G021 M03");
//    qDebug() << GcodePreprocessorUtils::splitCommand("G0 X123.4456 Y3.12345 Z0.5");
//    qDebug() << GcodePreprocessorUtils::updatePointWithCommand("G0 X10 Y20 Z30", QVector3D(10, 10, 10), false);
//    qDebug() << GcodePreprocessorUtils::updateCenterWithCommand(GcodePreprocessorUtils::splitCommand("G0 X10 Y20 I0 J20 K6"), QVector3D(10, 10, 10), QVector3D(20, 20, 20), false, true);
//    qDebug() << GcodePreprocessorUtils::generateG1FromPoints(QVector3D(10, 10, 10), QVector3D(20, 20, 20), true, 3);
//    qDebug() << GcodePreprocessorUtils::getAngle(QVector3D(0, 0, 0), QVector3D(-10, 0, 10));
//    qDebug() << GcodePreprocessorUtils::calculateSweep(M_PI / 2, 0, false);
//    qDebug() << GcodePreprocessorUtils::generatePointsAlongArcBDring(QVector3D(10, 0, 0), QVector3D(0, 10, 0), QVector3D(0, 0, 0), false, 10, 0.1, 5);

//    GcodeParser gp;

//    gp.addCommand("G1 X0 Y10");
//    gp.addCommand("G1 X10 Y0");
//    gp.addCommand("G1 X10 Y10 Z0");
//    gp.addCommand("G2 X20 Y0 R10");

//    qDebug() << "PointSegment list";

//    for (int i = 0; i < 10000; i++) {
//        GcodeParser gp1;

//        gp1.addCommand("G1 X0 Y10");
//        gp1.addCommand("G1 X10 Y0");
//        gp1.addCommand("G1 X10 Y10 Z0");
//        gp1.addCommand("G2 X20 Y0 R10");
//    }

//    foreach (PointSegment *ps, gp.getPointSegmentList()) {
//        qDebug() << *ps->point() << ps->isArc() << ps->isClockwise();
//    }

//    GcodeViewParse gvp;
//    QList<QString> commands;

//    commands.append("G1 X0 Y10");
//    commands.append("G1 X10 Y0");
//    commands.append("G1 X10 Y10 Z0");
//    commands.append("G2 X20 Y0 Z0 R10");

//    qDebug() << "LineSegment list";

//    for (int i = 0; i < 10000; i++)
//    {
//        GcodeViewParse gvp1;
//        foreach (LineSegment* ls, gvp1.toObjRedux(commands, 5)) {
//        }
//    }

//    foreach (LineSegment* ls, gvp.toObjRedux(commands, 5)) {
//        qDebug() << ls->getStart() << ls->getEnd() << ls->getLineNumber() << ls->isArc();
//    }

//    return 0;

    return a.exec();
}
