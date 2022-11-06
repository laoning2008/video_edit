#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);

    QList<int> sizesMain;
    sizesMain << 45000 << 55000;
    ui->splitter_main->setSizes(sizesMain);

    QList<int> sizesTop;
    sizesTop << 20000 << 40000 << 40000;
    ui->splitte_top->setSizes(sizesTop);

}

MainWindow::~MainWindow()
{
    delete ui;
}
