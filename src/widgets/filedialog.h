#ifndef FILEDIALOG_H
#define FILEDIALOG_H

#include <QDialog>
#include <QFileSystemModel>
#include <QObject>
#include <QModelIndex>
#include <QFileInfo>
#include <QDir>
#include <QSortFilterProxyModel>
#include <QDebug>
#include <QStandardPaths>
//#include <QDirModel>


//class DirProxy : public QSortFilterProxyModel
//{
//    Q_OBJECT

//public:
//    explicit DirProxy(QFileSystemModel *dirmodel) {
//        this->setSourceModel(dirmodel);
//    }

//    bool hasChildren(const QModelIndex &parent) const override {
//        QModelIndex sourceParent = this->mapToSource(parent);
//        if (sourceParent.isValid()) {
//            QFileSystemModel *dirmodel = ((QFileSystemModel *) sourceModel());
//            if (dirmodel->isDir(sourceParent)) {
//                QString sPath = dirmodel->fileInfo(sourceParent).absoluteFilePath();
//                QDir qdir = QDir(sPath);
//                return !qdir.entryInfoList(dirmodel->filter()).isEmpty();
//            }
//        }
//        return true;
//    }

//    bool filterAcceptsRow(int row, const QModelIndex &parent) const override {
//        QModelIndex source = ((QFileSystemModel *) this->sourceModel())->index(row, 0, parent);
//        if (source.isValid()) {
//            QFileSystemModel *dirmodel = ((QFileSystemModel *) sourceModel());
//            if (dirmodel->isDir(source)) {
//                QString sPath = dirmodel->fileInfo(source).absoluteFilePath();
//                QDir qdir = QDir(sPath);
//                qdir.setNameFilters(dirmodel->nameFilters());
//                return !qdir.entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries | QDir::AllDirs).isEmpty();
//            }
//        }
//        return true;
//    }
//};

namespace Ui {
class FileDialog;
}

class FileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FileDialog(QWidget *parent = nullptr);
    ~FileDialog();

    QStringList addresses;
    int currentId;

    void goToPath(QString sPath);
    void updateAddressBar(QString sPath);
    void clearLayout(QLayout *layout);
    void addBookmark(QIcon icon, QString text, QString path);

    static QStringList makeFilterList(const QString &filter);
    static QStringList stripFilters(const QStringList &filters);
    static QStringList cleanFilterList(const QString &filters);

    QIcon geticon(const QStandardPaths::StandardLocation &location);

    static FileDialog* getOpenFileDialog(QWidget *parent, QString title, QString folder, QString filters);
    static FileDialog* getSaveFileDialog(QWidget *parent, QString title, QString folder, QString filters);

//    int customExec();

    QString getOpenFileName();
    QString getSaveFileName();

private slots:
    void on_DirectoryLoaded(const QString &path);
//    void on_treeView_clicked(const QModelIndex &index);
    void on_listView_doubleClicked(const QModelIndex &index);

    void buttonClicked(QPushButton *sender);

    void on_backButton_clicked();

    void on_forwardButton_clicked();

    void on_listView_clicked(const QModelIndex &index);

private:
    Ui::FileDialog *ui;
//    QDirModel *dirmod;
//    QFileSystemModel *dirmodel;
    QFileSystemModel *filemodel;
//    DirProxy *dirproxy;
};

#endif // FILEDIALOG_H
