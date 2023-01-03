#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QPaintEvent>
#include <QWidget>

namespace Ui {
class VideoWidget;
}

class VideoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VideoWidget(QWidget *parent = nullptr);
    ~VideoWidget();

private:
    Ui::VideoWidget *ui;
    bool is_full_screen = false;



    // QWidget interface
protected:
    virtual void keyReleaseEvent(QKeyEvent *event);

    // QWidget interface
protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
};

#endif // VIDEOWIDGET_H
