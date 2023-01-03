#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event);
    QString calculateTime(int time);

private:
    Ui::MainWindow *ui;
    QMediaPlayer *qMediaPlayer = nullptr;
    QMediaPlaylist *qMediaPlaylist = nullptr;
    QVideoWidget *qVideoWidget = nullptr;
    bool is_play = false;
    void play();




private slots:
    void on_horizontalSlider_volumn_valueChanged(int value);
    void on_horizontalSlider_time_sliderReleased();
    void on_item_double_click();
    void on_pushButton_list_clicked();
    void on_pushButton_prev_clicked();
    void on_pushButton_play_clicked();
    void on_pushButton_next_clicked();
    void on_pushButton_mode_clicked();
    void on_pushButton_full_clicked();



    void on_horizontalSlider_speed_valueChanged(int value);
};
#endif // MAINWINDOW_H
