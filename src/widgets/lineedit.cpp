// This file is a part of "Candle" application.
// Copyright 2015-2016 Hayrullin Denis Ravilevich

#include <QDebug>
#include <QKeyEvent>
#include "lineedit.h"

//ComboBox::ComboBox(QWidget *parent) : QComboBox(parent)
LineEdit::LineEdit(QWidget *parent) : QLineEdit(parent)
{
//    m_stringList << "toto" << "tata" << "tonton" << "titi";
    m_stringList = new QStringList();
//    m_model = new QStringListModel(*m_stringList, this);
//    m_completer = new QCompleter(m_model, this);
    m_completer = new QCompleter(this);
    this->setCompleter(m_completer);

////    m_completer->setMaxVisibleItems(5);
    m_completer->setCaseSensitivity(Qt::CaseInsensitive);
    m_completer->setCompletionMode(QCompleter::InlineCompletion);
////    m_completer->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
//    m_completer->complete();

    updateAutoCompleteModel();

    this->connect(this, SIGNAL(returnPressed()), this, SLOT(on_returnPressed()));
}

LineEdit::~LineEdit()
{
}

QStringList LineEdit::items() {
    return *m_stringList;
}

void LineEdit::storeText()
{
    if (this->text() != "") {
        m_stringList->insert(0, this->text());
        m_stringList->removeDuplicates();
        updateAutoCompleteModel();
    }
}

void LineEdit::addItems(QStringList items) {
    m_stringList->append(items);
    m_stringList->removeDuplicates();
//    m_model = new QStringListModel(*m_stringList, this);
//    m_completer->setModel(m_model);
//    m_completer->complete();
    updateAutoCompleteModel();
}

void LineEdit::updateAutoCompleteModel() {
    QStringListModel *model;
    model = (QStringListModel*)(m_completer->model());
    if(model==NULL)
        model = new QStringListModel();
    model->setStringList(*m_stringList);
    m_completer->setModel(model);
//    m_completer->complete();
}

//int LineEdit::count() {
//    return m_stringList.size();
//}

//int LineEdit::maxCount() {
//    return m_maxCount;
//}

//void LineEdit::setMaxCount(int value) {
//    m_maxCount = value;
//}

//void LineEdit::insertItem(int index, QString value) {
////    m_stringList.insert(index, value);
//}

//void LineEdit::removeItem(int index) {
////    m_stringList.removeAt(index);
//}

//const QString LineEdit::currentText() {
//    return this->text();
//}

//void LineEdit::setCurrentText(QString value) {
////    this->setText(value);
//}

//void LineEdit::setMaxVisibleItems(int value){
////    m_completer->setMaxVisibleItems(value);
//}

//void LineEdit::setEditable(bool value) {}
//void LineEdit::setInsertPolicy(QComboBox::InsertPolicy value) {}
void LineEdit::setAutoCompletion(bool value) {
    if (value == true) {
        this->setCompleter(m_completer);
        m_completer->complete();
    }
    else {
        this->setCompleter(nullptr);
    }
}

//const QString LineEdit::itemText(int index) {
//    return m_stringList.value(index);
//}

//void LineEdit::setCurrentIndex(int index) {
////    m_stringList.removeAt(index);
////    setText(m_stringList.value(index));
//}

//void LineEdit::keyPressEvent(QKeyEvent *e)
////void ComboBox::on_returnPressed()
//{
////    QString text = this->text();
////    if (!m_stringList.contains(text)) {
////        m_stringList.append(text);
//////        m_model = new QStringListModel(m_stringList, this);
//////        m_completer->setModel(m_model);
////        m_completer->complete();
////    }
////    qDebug() << "append text: " << text;
////    qDebug() << "words: " << m_stringList;

////    emit returnPressed();

////    if (!m_stringList.contains(text)) {
////        qDebug() << "append text: " << text;
////        qDebug() << "words: " << m_stringList;
////        m_stringList.append(text);
////    }

////    if (e->key() == Qt::Key_Return) {
////        if (this->count() == this->maxCount()) this->removeItem(this->maxCount() - 1);  // TODO: Make removing selected item
////    }
//////    QComboBox::keyPressEvent(e);
////    QLineEdit::keyPressEvent(e);

//    QLineEdit::keyPressEvent(e);

//    if (e->key() == Qt::Key_Return || e->key() == Qt::Key_Enter) {
//        on_returnPressed();
////        this->setCurrentIndex(-1);
//    }
//}

void LineEdit::on_returnPressed(){
//    QString text = this->text();
//    if (text != "" && !m_stringList->contains(text)) {
//        m_stringList->append(text);
////        m_model = new QStringListModel(*m_stringList, this);
////        m_completer->setModel(m_model);
////        m_completer->complete();

//        updateAutoCompleteModel();

//        qDebug() << "append item: " << text;
//        qDebug() << "items: " << *m_stringList;
//    }
    storeText();
//    this->setText("");
}
