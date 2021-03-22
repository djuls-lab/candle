#include "messagebox.h"
#include <QWidget>
#include <QPainter>
#include <QStyleOption>
#include <QDialogButtonBox>
#include <QLabel>
#include <QLayout>
#include <QPushButton>

//class MessageBox : public QMessageBox
MessageBox::MessageBox(QWidget *parent) : QMessageBox(parent)
{
    m_parent = parent;
//    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setWindowFlag(Qt::FramelessWindowHint, true);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setAttribute(Qt::WA_StyleSheetTarget, true);
    setContentsMargins(24, 12, 24, 32);
//    setFixedWidth(parent->width());
}

void MessageBox::resizeEvent(QResizeEvent *Event)
{
    QMessageBox::resizeEvent(Event);
    this->setFixedWidth(m_parent->width());
    this->setFixedHeight(this->height());

    QDialogButtonBox *buttonBox = this->findChildren<QDialogButtonBox*>(QLatin1String("qt_msgbox_buttonbox")).first();
    buttonBox->setCenterButtons(true);
    buttonBox->layout()->setSpacing(16);

    QLabel *label = this->findChildren<QLabel*>(QLatin1String("qt_msgbox_label")).first();
//    label->setMaximumHeight(0);
//    label->hide();

    QLabel *iconLabel = this->findChildren<QLabel*>(QLatin1String("qt_msgboxex_icon_label")).first();
//    iconLabel->setMaximumHeight(0);
//    iconLabel->hide();

    QLabel *informativeLabel = this->findChildren<QLabel*>(QLatin1String("qt_msgbox_informativelabel")).first();
    informativeLabel->setAlignment(Qt::AlignCenter | Qt::AlignTop);

    QGridLayout *grid = this->findChildren<QGridLayout*>().first();
    grid->setRowMinimumHeight(0, 0);
    grid->setHorizontalSpacing(0);
    grid->setVerticalSpacing(16);
    grid->removeWidget(label);
    grid->removeWidget(iconLabel);
}

void MessageBox::paintEvent(QPaintEvent *) {
//    if (!(windowFlags() & Qt::FramelessWindowHint) && !testAttribute(Qt::WA_TranslucentBackground))
//        return;  // nothing to do

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    // Have style sheet?
    if (testAttribute(Qt::WA_StyleSheetTarget)) {
        // Let QStylesheetStyle have its way with us.
        QStyleOption opt;
        opt.initFrom(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
        p.end();
        return;
    }

    // Paint thyself.
    QRectF rect(QPointF(0, 0), size());
    // Check for a border size.
    qreal penWidth = borderWidth;
    if (penWidth < 0.0) {
        QStyleOption opt;
        opt.initFrom(this);
        penWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth, &opt, this);
    }
    // Got pen?
    if (penWidth > 0.0) {
        p.setPen(QPen(palette().brush(foregroundRole()), penWidth));
        // Ensure border fits inside the available space.
        const qreal dlta = penWidth * 0.5;
        rect.adjust(dlta, dlta, -dlta, -dlta);
    }
    else {
        // QPainter comes with a default 1px pen when initialized on a QWidget.
        p.setPen(Qt::NoPen);
    }
    // Set the brush from palette role.
//    p.setBrush(palette().brush(backgroundRole()));
    p.setBrush(QBrush(QColor(0, 0, 0)));
    // Got radius?  Otherwise draw a quicker rect.
    if (radius > 0.0)
        p.drawRoundedRect(rect, radius, radius, Qt::AbsoluteSize);
    else
        p.drawRect(rect);

    // C'est finí
    p.end();
}

int MessageBox::warning(QWidget *parent, const QString &title, const QString& text,
                        StandardButtons buttons, StandardButton defaultButton) {

        MessageBox mb(parent);
        mb.setWindowTitle(title);
        mb.setInformativeText(text);
//        mb->addButton( "&Yes", QMessageBox::YesRole);
//        QPushButton *noBtn = mb->addButton( "&No", QMessageBox::NoRole);
//        mb->setDefaultButton(noBtn);
        QDialogButtonBox *buttonBox = mb.findChild<QDialogButtonBox*>();
        uint mask = QMessageBox::FirstButton;
        while (mask <= QMessageBox::LastButton) {
            uint sb = buttons & mask;
            mask <<= 1;
            if (!sb)
                continue;
            QPushButton *button = mb.addButton((QMessageBox::StandardButton)sb);
            button->setIcon(QIcon());
            // Choose the first accept role as the default
            if (mb.defaultButton())
                continue;
            if ((defaultButton == QMessageBox::NoButton && buttonBox->buttonRole(button) == QDialogButtonBox::AcceptRole)
                || (defaultButton != QMessageBox::NoButton && sb == uint(defaultButton)))
                mb.setDefaultButton(button);
        }

//        mb->addButton(QMessageBox::StandardButton(button0));
//        mb->addButton(QMessageBox::StandardButton(button1));
//        mb->addButton(QMessageBox::StandardButton(button2));

    return mb.exec();
}

void MessageBox::critical(QWidget *parent, const QString &title, const QString& text) {

    MessageBox mb(parent);
    mb.setWindowTitle(title);
    mb.setInformativeText(text);

    QPushButton *button = mb.addButton(QMessageBox::StandardButton(QMessageBox::Ok));
    button->setIcon(QIcon());
    mb.setDefaultButton(button);
    mb.exec();
}

void MessageBox::information(QWidget *parent, const QString &title, const QString& text) {

    MessageBox mb(parent);
    mb.setWindowTitle(title);
    mb.setInformativeText(text);

    QPushButton *button = mb.addButton(QMessageBox::StandardButton(QMessageBox::Ok));
    button->setIcon(QIcon());
    mb.setDefaultButton(button);
    mb.exec();
}
