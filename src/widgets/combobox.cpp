#include <QListView>

#include "combobox.h"

ComboBox::ComboBox(QWidget *parent) : QComboBox(parent)
{
    setView(new QListView());
}

void ComboBox::setEditable(bool editable)
{
    if (!editable) {
        if (currentText() != itemText(currentIndex())) {
            // Remove user item if exist
            QString value = currentText();
            if (itemData(count() - 1) == 1) {
                removeItem(count() - 1);
                removeItem(count() - 1);
            }

            // Add user item to the end of list
            insertSeparator(count());
            addItem(value, 1);
            setCurrentIndex(count() - 1);
        }
    }

    QComboBox::setEditable(editable);
}

void ComboBox::setCurrentNext()
{
    do {
        setCurrentIndex(qMin(currentIndex() + 1, count() - 1));
    } while (currentText().isEmpty());
}

void ComboBox::setCurrentPrevious()
{
    do {
        setCurrentIndex(qMax(currentIndex() - 1, 0));
    } while (currentText().isEmpty());
}

void ComboBox::setItems(QStringList items)
{
    if (items.isEmpty()) return;

    clear();

    bool userItem = false;
    foreach (QString item, items) {
        if (item.isEmpty()) {
            insertSeparator(count());
            userItem = true;
        } else {
            insertItem(count(), item, userItem ? 1 : QVariant());
        }
    }
}

QStringList ComboBox::items()
{
    QStringList items;

    for (int i = 0; i < count(); i++) items.append(itemText(i));

    return items;
}

void ComboBox::keyPressEvent(QKeyEvent *e)
{
    if (this->isEditable() || !isBlockedKey(e->key())) QComboBox::keyPressEvent(e);
}

void ComboBox::keyReleaseEvent(QKeyEvent *e)
{
    if (this->isEditable() || !isBlockedKey(e->key())) QComboBox::keyReleaseEvent(e);
}

bool ComboBox::isBlockedKey(int key)
{
    return key != Qt::Key_ScrollLock  && key != Qt::Key_Down && key != Qt::Key_Up;
}
