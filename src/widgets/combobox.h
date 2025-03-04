#ifndef COMBOBOXKEY_H
#define COMBOBOXKEY_H

#include <QWidget>
#include <QComboBox>
#include <QKeyEvent>
#include <QDebug>

class ComboBox : public QComboBox
{
public:
    explicit ComboBox(QWidget *parent = 0);

    void setEditable(bool editable);

    void setCurrentNext();
    void setCurrentPrevious();

    void setItems(QStringList items);
    QStringList items();

protected:
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);

private:
    bool isBlockedKey(int key);
};

#endif // COMBOBOXKEY_H
