#include "mainscene.h"

MainScene::MainScene()
{
    group = createItemGroup(*(new QList<QGraphicsItem*>));
    pixmapItem = new QGraphicsPixmapItem();
//    idw = IDW(starts,ends);
    editable = false;
}

void MainScene::press(QMouseEvent *event)
{
    if(editable)
    {
        start = end = event->pos();
        QGraphicsLineItem* lineItem = new QGraphicsLineItem();
        lineItem->setLine(start.x(),start.y(),end.x(),end.y());
        items.push_back(lineItem);//新建对象放入Qvector
        group->addToGroup(lineItem);//加入组来决定先后顺序
    }
}

void MainScene::moving(QMouseEvent *event)
{
    if(editable)
    {
        end = event->pos();
        if(!items.isEmpty())
        {
            QGraphicsLineItem* lineItem = static_cast<QGraphicsLineItem*>(items.last());
            lineItem->setLine(start.x(),start.y(),end.x(),end.y());
        }
    }
}

void MainScene::release(QMouseEvent *event)
{
    if(editable)
    {
        end = event->pos();
        if(!items.isEmpty())
        {
            QGraphicsLineItem* lineItem = static_cast<QGraphicsLineItem*>(items.last());
            lineItem->setLine(start.x(),start.y(),end.x(),end.y());
        }
        starts.append(start);
        ends.append(end);
    }
}

void MainScene::open()
{
    removeItem(pixmapItem);
    path = QFileDialog::getOpenFileName(NULL,tr("Open"),".",tr("Images(*.bmp *.png *.jpg)"));
    if(!path.isEmpty())
    {
        image = QImage(path);
        QPixmap p = QPixmap::fromImage(image);
        pixmapItem = new QGraphicsPixmapItem();
        pixmapItem->setPixmap(p);
        group->addToGroup(pixmapItem);
        editable = true;
    }
}

void MainScene::save()
{
    QString filename = QFileDialog::getSaveFileName(NULL, tr("Save As"), "untitled.png", tr("Images(*.bmp *.png *.jpg)"));
    if(!filename.isEmpty())
    {
        image.save(filename);
    }
}

void MainScene::invert()
{
    if(!image.isNull())
    {
        image.invertPixels();
        QPixmap p = QPixmap::fromImage(image);
        pixmapItem->setPixmap(p);
    }
}

void MainScene::grayscale()
{
    if(!image.isNull())
    {
        for (int i=0; i<image.width(); i++)
        {
            for (int j=0; j<image.height(); j++)
            {
                QRgb color = image.pixel(i, j);
                int gray_value = (qRed(color)+qGreen(color)+qBlue(color))/3;
                image.setPixel(i, j, qRgb(gray_value, gray_value, gray_value) );
            }
        }
        QPixmap p = QPixmap::fromImage(image);
        pixmapItem->setPixmap(p);
    }
}

void MainScene::restore()
{
    if(!path.isEmpty())
    {
//        clear();
//        pixmapItem = new QGraphicsPixmapItem();
        deleteALL();
        removeItem(pixmapItem);
        group->addToGroup(pixmapItem);
        image = QImage(path);
        QPixmap p = QPixmap::fromImage(image);
        pixmapItem->setPixmap(p);
    }
}

void MainScene::mirrorH()
{
    if(!image.isNull())
    {
        image = image.mirrored(true,false);
        QPixmap p = QPixmap::fromImage(image);
        pixmapItem->setPixmap(p);
    }
}

void MainScene::mirrorV()
{
    if(!image.isNull())
    {
        image = image.mirrored(false,true);
        QPixmap p = QPixmap::fromImage(image);
        pixmapItem->setPixmap(p);
    }
}

void MainScene::deleteALL()
{
    if(items.isEmpty())
    {
//        QMessageBox::information(NULL,"Info","There's nothing to delete");
    }
    else
    {
        int initialCount = items.count();
        for(int i=0;i<initialCount;i++)
        {
            group->removeFromGroup(items.last());
            removeItem(items.last());
            items.pop_back();
            starts.pop_back();
            ends.pop_back();
        }
    }
}

void MainScene::idwFunc()
{
    if(!image.isNull())
    {
        idw = IDW(starts,ends);
        removeItem(pixmapItem);
        update(0,0,this->width(),this->height());
        QImage backup = image,newImg = QImage(image.width(),image.height(),QImage::Format_RGB32);
        newImg.fill(Qt::white);
        for (int i=0; i<image.width(); i++)
        {
            for (int j=0; j<image.height(); j++)
            {
                QPoint point = QPoint(i,j);
                point = idw.f(point);
//                QMessageBox::information(NULL,"OK",QString::number(point.x())+" "+QString::number(point.y()));
                newImg.setPixel(point,backup.pixel(i,j));
            }
        }
        image = newImg;
        QPixmap p = QPixmap::fromImage(newImg);
        pixmapItem = new QGraphicsPixmapItem();
        pixmapItem->setPixmap(p);
        deleteALL();
        group->addToGroup(pixmapItem);
    }
}


