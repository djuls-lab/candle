#include <QStandardPaths>
#include <QPushButton>
#include <QScroller>
#include <QMimeDatabase>
#include <QMimeType>
#include <QStorageInfo>
#include <QList>
#include <QLabel>
#include <QHBoxLayout>
#include <QStateMachine>
#include <QState>
#include <QEventTransition>

#include "filedialog.h"
#include "ui_filedialog.h"

FileDialog::FileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileDialog)
{
    ui->setupUi(this);

    this->setWindowTitle(tr("Pick A File"));
//    this->setModal(false);
//    this->setWindowModality(Qt::WindowModal);

    QString rootpath = QDir::rootPath();

//    dirmodel = new QFileSystemModel(this);
//    dirmodel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs); // | QDir::Drives);
//    dirmodel->setNameFilterDisables(false);
//    dirmodel->setRootPath(rootpath);

//    dirproxy = new DirProxy(dirmodel);
//    ui->treeView->setModel(dirproxy);
////    dirmod = new QDirModel();
////    dirmod->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Drives);
////    dirmod->setSorting(QDir::DirsFirst | QDir::IgnoreCase | QDir::Name);
////    ui->treeView->setModel(dirmod);

////    ui->treeView->setRootIndex(dirproxy->index(0, 0));
//    ui->treeView->setRootIndex(dirproxy->mapFromSource(dirmodel->setRootPath(rootpath)));
////    ui->treeView->setRootIndex(dirproxy->mapFromSource(dirmodel->index(rootpath)));

//    for (int i = 1; i < dirmodel->columnCount(); ++i)
//        ui->treeView->hideColumn(i);
//    ui->treeView->setHeaderHidden(true);
//    ui->treeView->setAutoExpandDelay(0);
//    ui->treeView->setAutoScroll(true);

    currentId = 0;

    filemodel = new QFileSystemModel(this);
    filemodel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files);
    filemodel->setNameFilterDisables(false);
    filemodel->setRootPath(rootpath);
    filemodel->sort(3, Qt::DescendingOrder);

    ui->listView->setModel(filemodel);
    for (int i = 1; i < filemodel->columnCount(); ++i)
        ui->listView->hideColumn(i);
    ui->listView->setHeaderHidden(true);
    ui->listView->setIconSize(QSize(48, 48));

    for (int i = 0; i < filemodel->columnCount(); ++i) {
        ui->listView->header()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    }

    foreach (QPushButton *button, ui->buttonBox->findChildren<QPushButton*>()) {
        button->setIcon(QIcon());
    }

//    connect(dirmodel,SIGNAL(directoryLoaded(QString)),this,SLOT(on_DirectoryLoaded(QString)));

//    ui->treeView->setAttribute(Qt::WA_AcceptTouchEvents); // TEST !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//    QScroller::grabGesture(this->ui->treeView, QScroller::LeftMouseButtonGesture); // TEST !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    ui->listView->setAttribute(Qt::WA_AcceptTouchEvents); // TEST !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    QScroller::grabGesture(this->ui->listView, QScroller::LeftMouseButtonGesture); // TEST !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    ui->scrollArea->setAttribute(Qt::WA_AcceptTouchEvents); // TEST !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    QScroller::grabGesture(this->ui->scrollArea, QScroller::LeftMouseButtonGesture); // TEST !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


//    ui->treeView->deleteLater();


    QList<QStandardPaths::StandardLocation> standardLocations({QStandardPaths::DesktopLocation, QStandardPaths::HomeLocation, QStandardPaths::DocumentsLocation, QStandardPaths::DownloadLocation});
    // https://gist.github.com/peteristhegreat/c0ca6e1a57e5d4b9cd0bb1d7b3be1d6a
//    foreach (QString location, QStandardPaths::standardLocations(QStandardPaths::DesktopLocation))  {
    foreach (QStandardPaths::StandardLocation location, standardLocations)  {
        QString path = QStandardPaths::standardLocations(location).first();
        QIcon icon = geticon(location);
        QString text = QStandardPaths::displayName(location);

//        QPushButton *button = new QPushButton(this);

//        // QIcon icon = QIcon::fromTheme("user-desktop");
//        button->setIconSize(QSize(48, 48));
//        button->setIcon(icon);
//        button->setText(text);
//        button->setProperty("path", path);
//        button->setStyleSheet( "QPushButton { background-color: transparent; padding: 6px; border: none; border-radius: 2px; text-align:left; } QPushButton::hover { background-color: palette(highlight); color: palette(highlighted-text); }");

//        if (button->sizeHint().width() + 6> this->ui->scrollArea->minimumWidth()) {
//            this->ui->scrollArea->setMinimumWidth(button->sizeHint().width() + 6);
//        }

//        connect(button, &QPushButton::clicked, [button, this]() {
////                  qDebug() << button->property("path");
//            on_pushButton_clicked(button);
//        });

//        ui->verticalLayout->addWidget(button);

        addBookmark(icon, text, path);

//        qDebug() << QStandardPaths::displayName(QStandardPaths::DesktopLocation) << " - " << location;
    }

//    foreach (const QFileInfo drive, QDir::drives()){
//        qDebug() << drive.baseName();
//    }





//    QString path = "/"; // filemodel->myComputer().toString();
//    QIcon icon = QIcon::fromTheme("folder");
//    QPushButton *button = new QPushButton(this);

//    // QIcon icon = QIcon::fromTheme("user-desktop");
//    button->setIconSize(QSize(48, 48));
//    button->setIcon(icon);
//    button->setText("Root");
//    button->setProperty("path", path);
//    button->setStyleSheet( "QPushButton { background-color: transparent; padding: 6px; border: none; border-radius: 2px; text-align:left; } QPushButton::hover { background-color: palette(highlight); color: palette(highlighted-text); }");

//    connect(button, &QPushButton::clicked, [button, this]() {
////                  qDebug() << button->property("path");
//        on_pushButton_clicked(button);
//    });

//    ui->verticalLayout->addWidget(button);







    foreach (const QStorageInfo &storage, QStorageInfo::mountedVolumes()) {
        if (storage.isValid() && storage.isReady() && storage.displayName() != "system-boot" && (storage.displayName() == "/" || !storage.name().isEmpty())  /*&& !storage.isReadOnly()*/) {
//                qDebug() << storage.displayName() << " - " << storage.rootPath() << storage.isRoot() << storage.device();
            // QApplication::style()->standardIcon(QStyle::SP_DriveHDIcon)
//                QIcon::fromTheme("drive-harddisk-usb");
            QString icon_name;
            if (storage.device().contains("sda"))
                icon_name = "drive-harddisk-usb";
            else
                icon_name = "drive-harddisk";

            QIcon icon = QIcon::fromTheme(icon_name);                     
            QString text = storage.displayName();
            QString path = storage.rootPath();

            if (text == "/")
                text = "File System";

//            QPushButton *button = new QPushButton(this);

//            button->setIconSize(QSize(48, 48));
//            button->setIcon(icon);
//            button->setText(text);
//            button->setProperty("path", path);
//            button->setStyleSheet( "QPushButton { background-color: transparent; padding: 6px; border: none; border-radius: 2px; text-align:left; } QPushButton::hover { background-color: palette(highlight); color: palette(highlighted-text); }");

//            if (button->sizeHint().width() + 6 > this->ui->scrollArea->minimumWidth()) {
//                this->ui->scrollArea->setMinimumWidth(button->sizeHint().width() + 6);
//            }

//            // connect(button, SIGNAL(clicked(QPushButton)), SLOT(on_pushButton_clicked(QPushButton)));
//            connect(button, &QPushButton::clicked, [button, this]() {
////                  qDebug() << button->property("path");
//                on_pushButton_clicked(button);
//            });

//            ui->verticalLayout->addWidget(button);

            addBookmark(icon, text, path);
        }
    }


    ui->verticalLayout->addStretch();

    ui->backButton->setIconSize(QSize(24, 24));
    ui->backButton->setIcon(QIcon::fromTheme("go-previous-symbolic", QApplication::style()->standardIcon(QStyle::SP_ArrowBack)));
    ui->backButton->setStyleSheet("QToolButton { min-width: 32px; min-height: 32px; padding: 6px; border: none; border-radius: 6px; border-top-right-radius: 0px; border-bottom-right-radius: 0px; background-color: palette(alternate-base); } QToolButton::hover { background-color: palette(light); color: palette(highlighted-text); }");

    ui->forwardButton->setIconSize(QSize(24, 24));
    ui->forwardButton->setIcon(QIcon::fromTheme("go-next-symbolic", QApplication::style()->standardIcon(QStyle::SP_ArrowForward)));
    ui->forwardButton->setStyleSheet("QToolButton { min-width: 32px; min-height: 32px; padding: 6px; border: none; border-radius: 6px; border-top-left-radius: 0px; border-bottom-left-radius: 0px; background-color: palette(alternate-base); } QToolButton::hover { background-color: palette(light); color: palette(highlighted-text); }");

    ui->lineEdit->setStyleSheet("QLineEdit { background-color: transparent; color: palette(dark); border: none; border-radius: 3px; }");

    ui->backButton->setDisabled(true);
    ui->forwardButton->setDisabled(true);

    connect(filemodel, SIGNAL(directoryLoaded(QString)), this, SLOT(on_DirectoryLoaded(QString)));


////    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
//    connect(ui->buttonBox, &QDialogButtonBox::accepted, [this]() {
//        qDebug() << "accepted !done!";
////        this->done(QDialog::Accepted);
//        SLOT(accept());
//        delete this;
////        this->close();
//    });
//    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

FileDialog::~FileDialog()
{
    delete ui;
//    delete dirmodel;
//    delete dirproxy;
//    delete filemodel;
}


void FileDialog::addBookmark(QIcon icon, QString text, QString path) {
    QPushButton *button = new QPushButton(this);

    button->setIconSize(QSize(48, 48));
    button->setIcon(icon);
    button->setText(text);
    button->setProperty("path", path);
    button->setStyleSheet( "QPushButton { background-color: transparent; padding: 6px; border: none; border-radius: 2px; text-align:left; } QPushButton::hover { background-color: palette(highlight); color: palette(highlighted-text); }");

    if (button->sizeHint().width() + 6 > this->ui->scrollArea->minimumWidth()) {
        this->ui->scrollArea->setMinimumWidth(button->sizeHint().width() + 6);
    }

    // connect(button, SIGNAL(clicked(QPushButton)), SLOT(on_pushButton_clicked(QPushButton)));
    connect(button, &QPushButton::clicked, [button, this]() {
        buttonClicked(button);
    });

    ui->verticalLayout->addWidget(button);
}

QIcon FileDialog::geticon(const QStandardPaths::StandardLocation &location) {
    QMimeDatabase mime;
    QMimeType mType;

    QString path = QStandardPaths::standardLocations(location).first();

    mType = mime.mimeTypeForFile(path);
    QString  iconName = ""; // mType.iconName();

    if (location == QStandardPaths::HomeLocation)
        iconName = "user-home";
    else if (location == QStandardPaths::DesktopLocation)
        iconName = "user-desktop";
    else if (location == QStandardPaths::DownloadLocation)
        iconName = "folder-download";
    else if (location == QStandardPaths::DocumentsLocation)
        iconName = "folder-documents";
//    else
//        iconName = "drive-harddisk-usb";

    return QIcon::fromTheme(iconName, QApplication::style()->standardIcon(QStyle::SP_DirIcon));
}

//void FileDialog::updateTreeViewGeometries()
//{
//    Q_D(QTreeView);
//    if (d->header) {
//        if (d->geometryRecursionBlock)
//            return;
//        d->geometryRecursionBlock = true;
//        QSize hint = d->header->isHidden() ? QSize(0, 0) : d->header->sizeHint();
//        setViewportMargins(0, hint.height(), 0, 0);
//        QRect vg = d->viewport->geometry();
//        QRect geometryRect(vg.left(), vg.top() - hint.height(), vg.width(), hint.height());
//        d->header->setGeometry(geometryRect);
//        //d->header->setOffset(horizontalScrollBar()->value()); // ### bug ???
//        QMetaObject::invokeMethod(d->header, "updateGeometries");
//        d->updateScrollBars();
//        d->geometryRecursionBlock = false;
//    }
//    QAbstractItemView::updateGeometries();
//}

void FileDialog::on_DirectoryLoaded(const QString &path) {
//    std::vector<std::pair<int, int> > indexes;

//    // first of all, I save all item "offsets" relative to its parent
//    QModelIndex ar_index = dirproxy->mapToSource(this->ui->treeView->currentIndex());

//    QModelIndex indexAbobe = ar_index.parent();
//    while (indexAbobe.isValid())
//    {
//        indexes.push_back(std::make_pair(indexAbobe.row(), indexAbobe.column()));
//        indexAbobe = indexAbobe.parent();
//    }

//    // now, select actual selection model

//    auto model = this->ui->treeView->selectionModel()->model();

//    // get root item

//    QModelIndex index = model->index(0, 0, QModelIndex());
//    if (index.isValid())
//    {
//        // now, expand all items below

//        for (auto it = indexes.rbegin(); it != indexes.rend() && index.isValid(); ++it)
//        {
//            auto row = (*it).first;
//            auto colum = (*it).second;

//            this->ui->treeView->setExpanded(index, true);

//            // and get a new item relative to parent
//            index = model->index(row, colum, index);
//        }
//    }

//    // finally, scroll to real item, after expanding everything above.
//    this->ui->treeView->scrollTo(ar_index);

//    qDebug() << "TOTO";
//    QModelIndex source = dirproxy->mapToSource(this->ui->treeView->currentIndex());
//    qDebug() << "YUYU: " << source;
//    if (source.isValid()) {
//        qDebug() << "TATA";
//        QString sPath = this->dirmodel->fileInfo(source).absoluteFilePath();
//        qDebug() << "TITI: " << sPath;
//    }

//    QModelIndex indexAbobe = ar_index.parent();
//    while (indexAbobe.isValid()) {
//        if (!this->ui->treeView->isExpanded(dirproxy->mapFromSource(indexAbobe))) {
//              this->ui->treeView->setExpanded(dirproxy->mapFromSource(indexAbobe), true);
//        }
//    }

//    qDebug() << this->ui->treeView->currentIndex().data(Qt::DisplayRole);
//    qDebug() << path;
//    this->ui->treeView->resizeColumnToContents(0);
//    this->ui->treeView->scrollTo(this->ui->treeView->currentIndex(), QAbstractItemView::PositionAtCenter);
//    qDebug() << "SCROLLED !";
//    QModelIndex source = dirproxy->mapToSource(this->ui->treeView->currentIndex());
//    if (source.isValid()) {
//         QString sPath = this->dirmodel->fileInfo(source).absoluteFilePath();
//         this->ui->treeView->scrollTo(this->dirmodel->index(sPath), QAbstractItemView::PositionAtCenter);
//         this->ui->treeView->expand(this->dirmodel->index(sPath));
//         this->ui->treeView->setCurrentIndex(this->dirmodel->index(sPath));
//    }

//    QModelIndex index = model->index("C:/");
//    this->ui->treeView->scrollTo(this->ui->treeView->currentIndex(), QAbstractItemView::PositionAtCenter);







//    QModelIndex source = dirproxy->mapToSource(this->ui->treeView->currentIndex());
//    if (source.isValid()) {
//         QString sPath = this->dirmodel->fileInfo(source).absoluteFilePath();
//         QModelIndex index = this->dirmodel->index(sPath);

//         this->ui->treeView->expand(index.parent());
//         this->ui->treeView->scrollTo(index.parent(), QAbstractItemView::PositionAtCenter);
//         this->ui->treeView->setCurrentIndex(index);
//         this->ui->treeView->resizeColumnToContents(0);

//         qDebug() << "SCROLLED TO: " << sPath;
//    }

    QString sPath = QStandardPaths::standardLocations(QStandardPaths::HomeLocation).first();
//    ui->listView->setRootIndex(filemodel->setRootPath(sPath));

//    updateAddressBar(sPath);
    goToPath(sPath);
//    QString sPath = this->filemodel->fileInfo(this->ui->listView->currentIndex()).absoluteFilePath();

//    if (sPath.startsWith("/"))
//        sPath = sPath.remove(0, 1);
//    ui->lineEdit->setText(sPath.replace("/", " > "));

    disconnect(filemodel, SIGNAL(directoryLoaded(QString)), this, SLOT(on_DirectoryLoaded(QString)));
}

void FileDialog::goToPath(QString sPath) {
    ui->listView->setRootIndex(filemodel->setRootPath(sPath));

    updateAddressBar(sPath);

//    qDebug() << "currentId: " << currentId;
}

//void FileDialog::on_treeView_clicked(const QModelIndex &index)
//{
//    QModelIndex source = dirproxy->mapToSource(index);
//    QString sPath = dirmodel->fileInfo(source).absoluteFilePath();
////    QString sPath = dirmod->fileInfo(index).absoluteFilePath();
//    ui->listView->setRootIndex(filemodel->setRootPath(sPath));
//}

void FileDialog::clearLayout(QLayout *layout) {
    QLayoutItem *item;
    while((item = layout->takeAt(0))) {
        if (item->layout()) {
            clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
           delete item->widget();
        }
        delete item;
    }
}

void FileDialog::updateAddressBar(QString sPath)
{
    clearLayout(ui->page1->layout());

    if (sPath.startsWith("/"))
        sPath = sPath.remove(0, 1);

    QStringList words = sPath.split("/");

//    foreach (QString word, words) {
    sPath = "";
    for (int i=0;i<words.size();i++) {
        QPushButton *button = new QPushButton(this);

        button->setIconSize(QSize(48, 48));
        button->setText(words[i]);

        sPath += "/";
        sPath += words[i];

        button->setProperty("path", sPath);

        button->setStyleSheet( "QPushButton { background-color: transparent; min-height: 32px; color: gray; padding: 6px; border: none; border-radius: 2px; text-align:left; } QPushButton::hover { background-color: palette(highlight); color: palette(highlighted-text); }");

        // connect(button, SIGNAL(clicked(QPushButton)), SLOT(on_pushButton_clicked(QPushButton)));
        connect(button, &QPushButton::clicked, [button, this]() {
            buttonClicked(button);
        });

        ui->page1->layout()->addWidget(button);

        if (i != words.size() - 1) {
            QLabel *label = new QLabel(this);
            label->setPixmap(QIcon::fromTheme("go-next-symbolic", QApplication::style()->standardIcon(QStyle::SP_ArrowForward)).pixmap(QSize(16, 16)));

            ui->page1->layout()->addWidget(label);
        }
    }

    ((QHBoxLayout *)ui->page1->layout())->addStretch();


    if (!addresses.contains(sPath)) {
        addresses.append(sPath);
        currentId = addresses.size() - 1;
    }else {
        currentId = addresses.indexOf(sPath);
    }

    ui->backButton->setDisabled(currentId == 0);
    ui->forwardButton->setDisabled(currentId == addresses.size() - 1);
}

void FileDialog::buttonClicked(QPushButton *sender)
{
    QString sPath = sender->property("path").toString();
//    ui->listView->setRootIndex(filemodel->setRootPath(sPath));

//    if (sPath.startsWith("/"))
//        sPath = sPath.remove(0, 1);
//    ui->lineEdit->setText(sPath.replace("/", " > "));

//    updateAddressBar(sPath);
    goToPath(sPath);
}

void FileDialog::on_listView_clicked(const QModelIndex &index)
{
    QString sPath = filemodel->fileInfo(index).absoluteFilePath();
    if (filemodel->fileInfo(index).isDir()) {
//        QString sPath = filemodel->fileInfo(index).absoluteFilePath();
//        ui->treeView->setCurrentIndex(dirproxy->mapFromSource(dirmodel->index(sPath)));
//        ui->treeView->setCurrentIndex(dirmod->index(sPath));
//        ui->listView->setRootIndex(filemodel->setRootPath(sPath));

//        if (sPath.startsWith("/"))
//            sPath = sPath.remove(0, 1);
//        ui->lineEdit->setText(sPath.replace("/", " > "));

//        updateAddressBar(sPath);
        goToPath(sPath);

    }else {
        QFileInfo fileInfo(sPath);
//        this->done(QDialog::Accepted);
        ui->lineEdit_2->setText(fileInfo.fileName());
    }
}

void FileDialog::on_listView_doubleClicked(const QModelIndex &index)
{
//    if (filemodel->fileInfo(index).isDir()) {
//        QString sPath = filemodel->fileInfo(index).absoluteFilePath();
////        ui->treeView->setCurrentIndex(dirproxy->mapFromSource(dirmodel->index(sPath)));
////        ui->treeView->setCurrentIndex(dirmod->index(sPath));
////        ui->listView->setRootIndex(filemodel->setRootPath(sPath));

////        if (sPath.startsWith("/"))
////            sPath = sPath.remove(0, 1);
////        ui->lineEdit->setText(sPath.replace("/", " > "));

////        updateAddressBar(sPath);
//        goToPath(sPath);

//    }else {
//        this->done(QDialog::Accepted);
//    }
    if (filemodel->fileInfo(index).isFile()) {
        this->done(QDialog::Accepted);
    }
}

void FileDialog::on_backButton_clicked()
{
    currentId -= 1;
    if (currentId < 0) {
        currentId = 0;
        ui->backButton->setDisabled(true);
    }
    goToPath(addresses[currentId]);
}

void FileDialog::on_forwardButton_clicked()
{
    currentId += 1;
    if (currentId > addresses.size() - 1) {
        currentId = addresses.size() - 1;
        ui->forwardButton->setDisabled(true);
    }
    goToPath(addresses[currentId]);
}

QStringList FileDialog::makeFilterList(const QString &filter)
{
    QString f(filter);
    if (f.isEmpty())
        return QStringList();
    QString sep(QLatin1String(";;"));
    int i = f.indexOf(sep, 0);
    if (i == -1) {
        if (f.indexOf(QLatin1Char('\n'), 0) != -1) {
            sep = QLatin1Char('\n');
            i = f.indexOf(sep, 0);
        }
    }
//    qDebug() << "makeFilterList: " << f.split(sep);
    return f.split(sep);
}

QStringList FileDialog::stripFilters(const QStringList &filters)
{
    QStringList strippedFilters;
    QRegExp r(QString::fromLatin1("^(.*)\\(([a-zA-Z0-9_.,*? +;#\\-\\[\\]@\\{\\}/!<>\\$%&=^~:\\|]*)\\)$"));
    const int numFilters = filters.count();
    strippedFilters.reserve(numFilters);
    for (int i = 0; i < numFilters; ++i) {
        QString filterName;
        int index = r.indexIn(filters[i]);
        if (index >= 0)
            filterName = r.cap(1);
        strippedFilters.append(filterName.simplified());
    }
//    qDebug() << "stripFilters: " << strippedFilters;
    return strippedFilters;
}

QStringList FileDialog::cleanFilterList(const QString &filter)
{
#if QT_CONFIG(regularexpression)
    QRegularExpression regexp(QString::fromLatin1("^(.*)\\(([a-zA-Z0-9_.,*? +;#\\-\\[\\]@\\{\\}/!<>\\$%&=^~:\\|]*)\\)$"));
    Q_ASSERT(regexp.isValid());
    QString f = filter;
    QRegularExpressionMatch match;
    filter.indexOf(regexp, 0, &match);
    if (match.hasMatch())
        f = match.captured(2);
//    qDebug() << "cleanFilterList: " << f.split(QLatin1Char(' '), QString::SkipEmptyParts);
    return f.split(QLatin1Char(' '), QString::SkipEmptyParts);
#else
    return QStringList();
#endif
}

//int FileDialog::customExec() {
//  QStateMachine sm;
//  QState s1(&sm), s2(&sm);
//  sm.setInitialState(&s1);
//  QEventTransition transition(this, QEvent::Close);
//  s2.addTransition(&transition);
//  QEventLoop loop;
//  QObject::connect(&s2, &QState::entered, &loop, &QEventLoop::quit);
//  sm.start();

//  this->setAttribute(Qt::WA_DeleteOnClose, false);
//  this->setResult(0);
//  this->show();

//  qDebug() << "loop start";
//  (void) loop.exec(QEventLoop::DialogExec);
//  qDebug() << "loop end";

//  int res = result();
//  delete this;

//  return res;
//}

FileDialog* FileDialog::getOpenFileDialog(QWidget *parent, QString title, QString homeLocation, QString filters) {
    FileDialog *filedialog = new FileDialog(parent);

    filedialog->setWindowTitle(title);
    filedialog->ui->lineEdit_2->hide();

//    filedialog->dirmodel->setNameFilters(filters);
//    filedialog->filemodel->setNameFilters(stripFilters(makeFilterList(filters)));
    filedialog->filemodel->setNameFilters(cleanFilterList(makeFilterList(filters).first()));

//    filedialog->ui->treeView->setCurrentIndex(filedialog->dirproxy->mapFromSource(filedialog->dirmodel->index(homeLocation)));
    filedialog->ui->listView->setRootIndex(filedialog->filemodel->setRootPath(homeLocation));

//    filedialog->ui->treeView->update();
//    filedialog->ui->treeView->scrollTo(filedialog->ui->treeView->currentIndex());


//    filedialog->exec();
//    // filedialog->show();
//    //    filedialog->customExec();


//////    connect(filedialog->ui->buttonBox, &QDialogButtonBox::accepted, [filedialog]() {
////    connect(filedialog, &QDialog::accepted, [filedialog]() {
////        qDebug() << "accepted !done!";
//////        filedialog->done(QDialog::Accepted);

////        QString sPath;

////        QModelIndex index = filedialog->ui->listView->currentIndex();
////        if (filedialog->filemodel->fileInfo(index).isFile()) {
////            sPath = filedialog->filemodel->fileInfo(index).absoluteFilePath();
////        }

////        &QDialog::finished();

//////        SLOT(accept());
//////        this->close();
////        return sPath;
////    });

//    QString sPath;
//    QModelIndex index = filedialog->ui->listView->currentIndex();
//    if (filedialog->filemodel->fileInfo(index).isFile()) {
//        sPath = filedialog->filemodel->fileInfo(index).absoluteFilePath();
//    }
//    // filedialog->finished()

    return filedialog;
}

FileDialog* FileDialog::getSaveFileDialog(QWidget *parent, QString title, QString homeLocation, QString filters) {
    FileDialog *filedialog = new FileDialog(parent);

    filedialog->setWindowTitle(title);

//    filedialog->dirmodel->setNameFilters(filters);
//    filedialog->filemodel->setNameFilters(stripFilters(makeFilterList(filters)));
    filedialog->filemodel->setNameFilters(cleanFilterList(makeFilterList(filters).first()));

//    filedialog->ui->treeView->setCurrentIndex(filedialog->dirproxy->mapFromSource(filedialog->dirmodel->index(homeLocation)));
    filedialog->ui->listView->setRootIndex(filedialog->filemodel->setRootPath(homeLocation));

//    filedialog->ui->treeView->update();
//    filedialog->ui->treeView->scrollTo(filedialog->ui->treeView->currentIndex());





    // TO TEST !!!!!
//    QDialog::exec() blocks the main event loop, yes. It doesn't block the UI though, as it opens a local event loop inside exec(), which processes events while the dialog is open. That can be a source of nasty bugs: (Almost) anything can happen before exec() returns, external events (timers, network, IPC, whatever) can call slots, cause other dialogs to appear, etc. Just the ways for the user to do unexpected things directly are usually limited, given the modal nature of most such dialogs.

//    One needs to be aware of the possible issue and not leave the application in an inconsistent state when calling exec(), and not rely on things to be as they were afterwards.

//    Alternatively, call the non-blocking QDialog::open() and connect to the finished() signal.



//    filedialog->exec();
////    filedialog->show();
////    filedialog->customExec();

//    qDebug() << "getting result...";

//    QString sPath;

////    connect(filedialog->ui->buttonBox, &QDialogButtonBox::accepted, [filedialog]() {
////    connect(filedialog, &QDialog::accepted, [filedialog, sPath]() {
////        qDebug() << "accepted !done!";

//    //    QString sPath;
//    foreach (QPushButton *button, filedialog->ui->page1->findChildren<QPushButton*>()) {
//        QVariant path = button->property("path");
//        if (path.isValid())
//            sPath = path.toString();
//    }
//    //    qDebug() << "sPath: " << sPath;

//    if (!sPath.isEmpty())
//        sPath = QDir::cleanPath(sPath + QDir::separator() + filedialog->ui->lineEdit_2->text());

//    //    qDebug() << "sPath: " << sPath;

////        filedialog->close();
////    });

    return filedialog;
}

QString FileDialog::getOpenFileName() {
    qDebug() << "get open filename...";
    QString sPath;
    QModelIndex index = this->ui->listView->currentIndex();
    if (this->filemodel->fileInfo(index).isFile()) {
        sPath = this->filemodel->fileInfo(index).absoluteFilePath();
    }
    return sPath;
}

QString FileDialog::getSaveFileName() {
    qDebug() << "get save filename...";
    QString sPath;
    foreach (QPushButton *button, this->ui->page1->findChildren<QPushButton*>()) {
        QVariant path = button->property("path");
        if (path.isValid())
            sPath = path.toString();
    }
    if (!sPath.isEmpty())
        sPath = QDir::cleanPath(sPath + QDir::separator() + this->ui->lineEdit_2->text());
    return sPath;
}
