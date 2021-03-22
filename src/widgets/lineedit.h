// This file is a part of "Candle" application.
// Copyright 2015-2016 Hayrullin Denis Ravilevich

#ifndef COMBOBOX_H
#define COMBOBOX_H

#include <QWidget>
//#include <QComboBox>
#include <QLineEdit>
#include <QCompleter>
#include <QStringListModel>
#include <QStringList>
#include <QComboBox>

//class ComboBox : public QComboBox
class LineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit LineEdit(QWidget *parent = 0);
    ~LineEdit();

    QCompleter *m_completer;
//    QStringListModel *m_model;
    QStringList *m_stringList;

    QStringList items();

//    int m_maxCount = 32;

    void storeText();
//    int count();
//    int maxCount();
//    void setMaxCount(int value);
//    void insertItem(int index, QString value);
//    void removeItem(int index);
//    const QString currentText();
//    const QString itemText(int index);
//    void setCurrentIndex(int index);
    void addItems(QStringList items);
//    void setCurrentText(QString value);
//    void setMaxVisibleItems(int value);
//    void setEditable(bool value);
//    void setInsertPolicy(QComboBox::InsertPolicy value);
    void setAutoCompletion(bool value);

    void updateAutoCompleteModel();

public slots:
    void on_returnPressed();

//Q_SIGNALS:
//    void returnPressed();

//protected:
//    void keyPressEvent(QKeyEvent *e);
};

#endif // COMBOBOX_H
