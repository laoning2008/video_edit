#include "ui/mainwindow.h"
#include "ui/MediaItemDelegate.h"
#include "MediaItem.h"
#include "ui_mainwindow.h"

#include <QDirIterator>
#include <QFileSystemModel>
#include <QStandardItem>
#include <libffmpegthumbnailer/videothumbnailer.h>

using namespace ffmpegthumbnailer;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);
//    setFixedSize(this->width(),this->height());

    QList<int> sizesMain;
    sizesMain << 45000 << 55000;
    ui->splitterMain->setSizes(sizesMain);

    QList<int> sizesTop;
    sizesTop << 60000 << 40000;
    ui->splitterTop->setSizes(sizesTop);

    QList<int> sizesDir;
    sizesDir << 30000 << 70000;
    ui->splitterMaterial->setSizes(sizesDir);


    ui->frameDirActionBar->layout()->setAlignment(Qt::AlignLeft);
    ui->frameFilesActionBar->layout()->setAlignment(Qt::AlignLeft);


    initVedioDirWidget();
    initVedioFilesWidget();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::initVedioDirWidget() {
    QFileSystemModel *model = new QFileSystemModel;
    model->setFilter(QDir::NoDotAndDotDot | QDir::Dirs);

    ui->treeViewDir->setModel(model);
    ui->treeViewDir->setRootIndex(model->setRootPath(QDir::currentPath()));

//    ui->treeViewDir->header()->hide();
    for (int i = 1; i < model->columnCount(); ++i) {
        ui->treeViewDir->hideColumn(i);
    }


    connect(ui->treeViewDir->selectionModel(), SIGNAL(currentChanged(const QModelIndex&, const QModelIndex&)), this, SLOT(videoTreeViewCurrentChanged(const QModelIndex&, const QModelIndex&)));
}

void MainWindow::initVedioFilesWidget() {
    auto delegate = new MediaItemDelegate(this);
    ui->lvFiles->setItemDelegate(delegate);
    ui->lvFiles->setModel(new QStandardItemModel);

    connect(ui->lvFiles->selectionModel(), SIGNAL(currentChanged(const QModelIndex, const QModelIndex)), this, SLOT(videoFileSelectionChanged(QModelIndex, QModelIndex)));
}


void MainWindow::updateCurSelVideoDir() {
    QStandardItemModel* lvModel = (QStandardItemModel*)ui->lvFiles->model();
    lvModel->clear();

    auto index =  ui->treeViewDir->selectionModel()->currentIndex();
    QFileSystemModel* tvModel = (QFileSystemModel*)ui->treeViewDir->model();
    QString filesPath = tvModel->fileInfo(index).absoluteFilePath();


    QDirIterator dirIt(filesPath);
    while (dirIt.hasNext()) {
        QString filePath = dirIt.next();

        if (!dirIt.fileInfo().isFile() || filePath.isEmpty()) {
            continue;
        }


        MediaItem::MaterialType materialType = MediaItem::MaterialType_Media;
        MediaItem::MediaType mediaType = MediaItem::MediaType_Unknown;
        uint32_t timeLen = MediaItem::DEFAULT_TIME_LEN;
        QString thumbnail;
        if (filePath.endsWith(".jpeg")) {
            mediaType = MediaItem::MediaType_Image;
            thumbnail = filePath;
        } else if (filePath.endsWith(".mp4")) {
            mediaType = MediaItem::MediaType_Video;

            thumbnail = filePath;
            thumbnail.replace(".mp4", "_thumbnail.png");
            VideoThumbnailer videoThumbnailer;
            videoThumbnailer.setImageQuality(10);
            videoThumbnailer.setThumbnailSize(150, 120);
            videoThumbnailer.generateThumbnail(filePath.toStdString(), ThumbnailerImageType::Png, thumbnail.toStdString());

        } else {
            continue;
        }

        QStandardItem *item = new QStandardItem;
        MediaItem itemData(filePath, dirIt.fileName(), timeLen, mediaType, materialType, true, thumbnail);
        item->setData(QVariant::fromValue(itemData),Qt::UserRole);

        lvModel->appendRow(item);
    }
}


void MainWindow::videoTreeViewCurrentChanged(const QModelIndex &current, const QModelIndex &previous) {
    updateCurSelVideoDir();
}

void MainWindow::videoListViewCurrentChanged(const QModelIndex &current, const QModelIndex &previous) {
}
