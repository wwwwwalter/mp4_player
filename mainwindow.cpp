#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QPaintEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("mp4 player");

    qMediaPlayer = new QMediaPlayer(this);
    qMediaPlaylist = new QMediaPlaylist(this);
    qMediaPlaylist->setPlaybackMode(QMediaPlaylist::Loop);
    qVideoWidget = new QVideoWidget(ui->widget);
    qVideoWidget->resize(ui->widget->size());


    qMediaPlayer->setPlaylist(qMediaPlaylist);
    qMediaPlayer->setVideoOutput(qVideoWidget);


    ui->horizontalSlider_volumn->setRange(0,100);
    ui->horizontalSlider_volumn->setValue(50);
    qMediaPlayer->setVolume(50);




    connect(qMediaPlayer,&QMediaPlayer::durationChanged,ui->horizontalSlider_time,[&](qint64 time){
        ui->horizontalSlider_time->setRange(0,(int)time);
        ui->label_time_range->setText(calculateTime((int)time));
    });
    connect(qMediaPlayer,&QMediaPlayer::positionChanged,ui->horizontalSlider_time,[&](qint64 time){
        ui->horizontalSlider_time->setValue((int)time);
        ui->label_time_play->setText(calculateTime((int)time));
    });

    connect(qMediaPlayer,&QMediaPlayer::mediaStatusChanged,this,[&](QMediaPlayer::MediaStatus status){
        switch (status) {
        case QMediaPlayer::MediaStatus::BufferedMedia:
            ui->pushButton_play->setText(QString::fromLocal8Bit("暂停"));
            is_play = true;
            break;
        case QMediaPlayer::MediaStatus::EndOfMedia:
            ui->pushButton_play->setText(QString::fromLocal8Bit("播放"));
            is_play = false;
            break;
        default:
            break;

        }
    });

    ui->listWidget->setAlternatingRowColors(true);
    connect(ui->listWidget, &QListWidget::itemDoubleClicked, this, &MainWindow::on_item_double_click);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::paintEvent(QPaintEvent *event){
    qVideoWidget->resize(ui->widget->size());

}

QString MainWindow::calculateTime(int time)
{
    int seconds = time/1000;
    int hour = seconds/3600;
    int min = (seconds-hour*3600)/60;
    int sec = seconds%60;

    QString qstr_time = QString("%1:%2:%3").arg(hour, 2, 10, QLatin1Char('0')).arg(min, 2, 10, QLatin1Char('0')).arg(sec, 2, 10, QLatin1Char('0'));

    return qstr_time;
}

void MainWindow::play()
{
    if(is_play==false){
        qMediaPlayer->play();
        ui->pushButton_play->setText(QString::fromLocal8Bit("暂停"));
        is_play = true;
    }else{
        qMediaPlayer->pause();
        ui->pushButton_play->setText(QString::fromLocal8Bit("播放"));
        is_play = false;
    }
}

void MainWindow::on_horizontalSlider_volumn_valueChanged(int value)
{
    qMediaPlayer->setVolume(value);
    ui->label_volumn->setText(QString::number(value)+"%");
}


void MainWindow::on_horizontalSlider_time_sliderReleased()
{
    qMediaPlayer->setPosition((qint64)(ui->horizontalSlider_time->value()));
}

void MainWindow::on_item_double_click()
{
    QString fileName = ui->listWidget->currentItem()->text();
    qMediaPlaylist->setCurrentIndex(ui->listWidget->currentIndex().row());
    if(is_play==false){
        ui->pushButton_play->setText(QString::fromLocal8Bit("暂停"));
        is_play = true;
    }
    qMediaPlayer->stop();
    qMediaPlayer->play();
}




void MainWindow::on_pushButton_list_clicked()
{
    QStringList qStringList = QFileDialog::getOpenFileNames(this,"play list directory","C:/Users/gzyit/Videos","allfiles(*.*);;"
                                                                                                               "Mp3(*.mp3);;"
                                                                                                               "Mp4(*.mp4);;");

    qMediaPlaylist->clear();
    ui->listWidget->clear();
    for(auto item:qStringList){
        qMediaPlaylist->addMedia(QUrl(item));
        ui->listWidget->addItem(item);
    }

}

void MainWindow::on_pushButton_prev_clicked()
{
    qMediaPlayer->stop();
    qMediaPlaylist->previous();
    qMediaPlayer->play();
}

void MainWindow::on_pushButton_play_clicked()
{
    play();
}

void MainWindow::on_pushButton_next_clicked()
{
    qMediaPlayer->stop();
    qMediaPlaylist->next();
    qMediaPlayer->play();
}

void MainWindow::on_pushButton_mode_clicked()
{
    static int mode = 0;
    mode = mode+1;
    if(mode>4)
        mode = 0;
    switch(mode){
    case 0:
        qMediaPlaylist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
        ui->pushButton_mode->setText(QString::fromLocal8Bit("单曲播放"));
        break;
    case 1:
        qMediaPlaylist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        ui->pushButton_mode->setText(QString::fromLocal8Bit("单曲循环"));
        break;
    case 2:
        qMediaPlaylist->setPlaybackMode(QMediaPlaylist::Sequential);
        ui->pushButton_mode->setText(QString::fromLocal8Bit("顺序播放"));
        break;
    case 3:
        qMediaPlaylist->setPlaybackMode(QMediaPlaylist::Loop);
        ui->pushButton_mode->setText(QString::fromLocal8Bit("循环播放"));
        break;
    case 4:
        qMediaPlaylist->setPlaybackMode(QMediaPlaylist::Random);
        ui->pushButton_mode->setText(QString::fromLocal8Bit("随机播放"));
        break;
    default:
        break;
    }
}

void MainWindow::on_pushButton_full_clicked()
{
    ui->widget->setWindowFlags(Qt::Window);
    ui->widget->showFullScreen();
}



