#include "videowidget.h"
#include "ui_videowidget.h"
#include <QDebug>

VideoWidget::VideoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoWidget)
{
    ui->setupUi(this);
    setStyleSheet("background-color: rgb(0, 0, 0);");
}

VideoWidget::~VideoWidget()
{
    delete ui;
}





void VideoWidget::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key()==16777216){
        if(is_full_screen){
            setWindowFlags(Qt::SubWindow);
            showNormal();
            is_full_screen = false;
        }
    }
}


void VideoWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(is_full_screen){
        setWindowFlags(Qt::SubWindow);
        showNormal();
        is_full_screen = false;
    }else{
        setWindowFlags(Qt::Window);
        showFullScreen();
        is_full_screen = true;
    }

}
