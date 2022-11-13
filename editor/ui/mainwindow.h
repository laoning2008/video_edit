#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QItemSelectionModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void initVedioDirWidget();
    void initVedioFilesWidget();
    void updateCurSelVideoDir();
public slots:
    void videoTreeViewCurrentChanged(const QModelIndex &current, const QModelIndex &previous);
    void videoListViewCurrentChanged(const QModelIndex &current, const QModelIndex &previous);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
