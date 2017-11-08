#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QFileDialog>
#include <QGraphicsItemGroup>
#include <QMessageBox>
#include <QTime>
#include "mainview.h"
#include "mainscene.h"
#include "idw.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void wait(int ms);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionInvert_triggered();

    void on_actionGrayScale_triggered();

    void on_actionRestore_triggered();

    void on_actionMirror_H_triggered();

    void on_actionMirror_V_triggered();

    void on_actionIDW_triggered();

    void on_actionRBF_triggered();

private:
    Ui::MainWindow *ui;
    MainView* view;
    MainScene* scene;
    //    QGraphicsPixmapItem* pixmapItem;
    //    QImage image;
    //    QGraphicsItemGroup* group;
    //    QString path;
    //    IDW idw;
};

#endif // MAINWINDOW_H
