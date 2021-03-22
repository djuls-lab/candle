#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QMessageBox>

class MessageBox : public QMessageBox
{
    Q_OBJECT

public:
    explicit MessageBox(QWidget *parent = 0);

    QWidget *m_parent;
    qreal radius = 0.0;        // desired radius in absolute pixels
    qreal borderWidth = -1.0;

    static int warning(QWidget *parent, const QString &title, const QString& text,
                            StandardButtons buttons=QMessageBox::Yes | QMessageBox::No, StandardButton defaultButton=QMessageBox::No);

    static void critical(QWidget *parent, const QString &title, const QString& text);

    static void information(QWidget *parent, const QString &title, const QString& text);

protected:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);
};

#endif // MESSAGEBOX_H
