#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->showMaximized();

    scene = new MainScene();
    view = new MainView(scene);
    this->setCentralWidget(view);
    scene->setSceneRect(0,0,view->width(),view->height());
    view->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    view->setRenderHint(QPainter::Antialiasing);
    //    group = scene->createItemGroup(*(new QList<QGraphicsItem*>));
    //    pixmapItem = new QGraphicsPixmapItem();
}

void MainWindow::wait(int ms)
{
    QTime n=QTime::currentTime();
    QTime now;
    do{
        now=QTime::currentTime();
    }while (n.msecsTo(now)<=ms);//等待一秒
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    //    scene->removeItem(pixmapItem);
    //    path = QFileDialog::getOpenFileName(this,tr("Open"),".",tr("Images(*.bmp *.png *.jpg)"));
    //    if(!path.isEmpty())
    //    {
    //        image = QImage(path);
    //        QPixmap p = QPixmap::fromImage(image);
    //        pixmapItem = new QGraphicsPixmapItem();
    //        pixmapItem->setPixmap(p);
    //        group->addToGroup(pixmapItem);
    scene->open();
    scene->update(view->rect());
    //    }
}

void MainWindow::on_actionSave_triggered()
{
    //    QString filename = QFileDialog::getSaveFileName(this, tr("Save As"), "untitled.png", tr("Images(*.bmp *.png *.jpg)"));
    //    if(!filename.isEmpty())
    //    {
    //        image.save(filename);
    //    }
    scene->save();
}

void MainWindow::on_actionInvert_triggered()
{
    //    if(!image.isNull())
    //    {
    //        image.invertPixels();
    //        QPixmap p = QPixmap::fromImage(image);
    //        pixmapItem->setPixmap(p);
    //        scene->update(view->rect());
    //    }
    scene->invert();
    scene->update(view->rect());
}

void MainWindow::on_actionGrayScale_triggered()
{
    //    if(!image.isNull())
    //    {
    //        for (int i=0; i<image.width(); i++)
    //        {
    //            for (int j=0; j<image.height(); j++)
    //            {
    //                QRgb color = image.pixel(i, j);
    //                int gray_value = (qRed(color)+qGreen(color)+qBlue(color))/3;
    //                image.setPixel(i, j, qRgb(gray_value, gray_value, gray_value) );
    //            }
    //        }
    //        QPixmap p = QPixmap::fromImage(image);
    //        pixmapItem->setPixmap(p);
    //        scene->update(view->rect());
    //    }
    scene->grayscale();
    scene->update(view->rect());
}

void MainWindow::on_actionRestore_triggered()
{
    //    if(!path.isEmpty())
    //    {
    //        image = QImage(path);
    //        QPixmap p = QPixmap::fromImage(image);
    //        pixmapItem->setPixmap(p);
    //        scene->update(view->rect());
    //    }
    scene->restore();
    scene->update(view->rect());
}

void MainWindow::on_actionMirror_H_triggered()
{
    //    if(!image.isNull())
    //    {
    //        image = image.mirrored(true,false);
    //        QPixmap p = QPixmap::fromImage(image);
    //        pixmapItem->setPixmap(p);
    //        scene->update(view->rect());
    //    }
    scene->mirrorH();
    scene->update(view->rect());
}

void MainWindow::on_actionMirror_V_triggered()
{
    //    if(!image.isNull())
    //    {
    //        image = image.mirrored(false,true);
    //        QPixmap p = QPixmap::fromImage(image);
    //        pixmapItem->setPixmap(p);
    //        scene->update(view->rect());
    //    }
    scene->mirrorV();
    scene->update(view->rect());
}

void MainWindow::on_actionIDW_triggered()
{
    scene->idwFunc();
}
