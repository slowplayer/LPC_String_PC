#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QtSerialPort>
#include <QByteArray>
#include <QDebug>
#include <QPainter>
#include <QFont>
#include <QRgb>
#include <QImage>
#include <QPixmap>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
private slots:
    void Openaction();
    void Sendaction();
    void Modaction();
private:
    Ui::Widget *ui;
    QSerialPort *myport;
    QByteArray data;
};

#endif // WIDGET_H
