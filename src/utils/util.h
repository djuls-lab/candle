// This file is a part of "Candle" application.
// Copyright 2015-2016 Hayrullin Denis Ravilevich

#ifndef UTIL
#define UTIL

#include <QColor>
#include <QIcon>
#include <QImage>
#include <QAbstractButton>
#include <QVector3D>
#include <QEventLoop>
#include <QTimer>
#include <QPainter>

class Util
{
public:
    static double nMin(double v1, double v2)
    {
        if (!qIsNaN(v1) && !qIsNaN(v2)) return qMin<double>(v1, v2);
        else if (!qIsNaN(v1)) return v1;
        else if (!qIsNaN(v2)) return v2;
        else return qQNaN();
    }

    static double nMax(double v1, double v2)
    {
        if (!qIsNaN(v1) && !qIsNaN(v2)) return qMax<double>(v1, v2);
        else if (!qIsNaN(v1)) return v1;
        else if (!qIsNaN(v2)) return v2;
        else return qQNaN();
    }

    static QVector3D colorToVector(QColor color)
    {
        return QVector3D(color.redF(), color.greenF(), color.blueF());
    }

    static void waitEvents(int ms)
    {
        QEventLoop loop;

        QTimer::singleShot(ms, &loop, SLOT(quit()));
        loop.exec();
    }

    static QIcon invertIconColors(QIcon icon)
    {
        QImage img = icon.pixmap(icon.actualSize(QSize(64, 64))).toImage();
        img.invertPixels();

        return QIcon(QPixmap::fromImage(img));
    }

    static QIcon changeIconColor(QIcon icon, QColor color)
    {
//        QColor rgb;
//        QImage img = icon.pixmap(icon.actualSize(QSize(64, 64))).toImage().convertToFormat(QImage::Format_ARGB32);
//        for (int j=0; j<img.height();++j) {
//            for (int i=0; i<img.width();++i) {
////                 QColor rgb = img -> pixelColor(i, j);
////                 img -> setPixelColor(i, j, QColor(color.red(), color.green(), color.blue(), rgb.alpha()));
//                rgb = color;
////                QRgb rgb = color.rgba();
//                rgb.setAlpha(QColor(img.pixel(i, j)).alpha());
//                img.setPixel(i, j, rgb.rgba());
//            }
//        }

//        QRgb base_color; // desired image color

        QPixmap new_image = icon.pixmap(icon.actualSize(QSize(64, 64))); //.convertToFormat(QImage::Format_ARGB32);
        QPainter painter(&new_image);
        painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
        painter.fillRect(new_image.rect(), color);
        painter.end();

//        return QIcon(QPixmap::fromImage(img));
        return QIcon(new_image);
    }

    static void invertButtonIconColors(QAbstractButton *button)
    {
        button->setIcon(invertIconColors(button->icon()));
    }

    static void changeButtonIconColor(QAbstractButton *button, QColor color, QColor disabledColor=nullptr)
    {
//        button->setIcon(changeIconColor(button->icon(), color));
        QIcon icon = button->icon();
        icon.addPixmap(changeIconColor(button->icon(), color).pixmap(icon.actualSize(QSize(64, 64))), QIcon::Normal);
        icon.addPixmap(changeIconColor(button->icon(), disabledColor).pixmap(icon.actualSize(QSize(64, 64))), QIcon::Disabled);
        button->setIcon(icon);
    }

    static QString toCamelCase(const QString& s)
    {
        QString tmp = s;
        QStringList parts = tmp.split(' ', QString::SkipEmptyParts);
        for (int i = 0; i < parts.size(); ++i)
            parts[i].replace(0, 1, parts[i][0].toUpper());
        tmp = parts.join(" ");
        tmp[0] = tmp[0].toLower();
        return tmp;
    }
};

#endif // UTIL

