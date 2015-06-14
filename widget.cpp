#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->openbt->setEnabled(false);
    ui->sendbt->setEnabled(false);
    connect(ui->modbt,SIGNAL(clicked()),this,SLOT(Modaction()));
    connect(ui->openbt,SIGNAL(clicked()),this,SLOT(Openaction()));
    connect(ui->sendbt,SIGNAL(clicked()),this,SLOT(Sendaction()));
    connect(ui->quitbt,SIGNAL(clicked()),qApp,SLOT(quit()));
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
            QSerialPort serial;
            serial.setPort(info);
            if(serial.open(QIODevice::ReadWrite))
            {
                ui->comboBox->addItem(info.portName());
                serial.close();
            }
        //    ui->openbt->setEnabled(true);
    }
    setLayout(ui->horizontalLayout);
}

Widget::~Widget()
{
    delete ui;
}
void Widget::Openaction()
{
    myport=new QSerialPort();
    myport->setPortName(ui->comboBox->currentText());
    myport->open(QIODevice::ReadWrite);
    myport->setBaudRate(115200);
    myport->setDataBits(QSerialPort::Data8);
    myport->setParity(QSerialPort::NoParity);
    myport->setStopBits(QSerialPort::OneStop);
    myport->setFlowControl(QSerialPort::NoFlowControl);
    ui->comboBox->setEnabled(false);
    ui->sendbt->setEnabled(true);
  //  connect(myport,SIGNAL(readyRead()),this,SLOT(readData()));
    qDebug()<<"Open Serial";
    ui->openbt->setEnabled(false);
}
void Widget::Sendaction()
{
    qDebug()<<"Send Data";
    myport->write(data);
}
void Widget::Modaction()
{
    QString sss=ui->lineEdit->text();
    QImage image(64,64,QImage::Format_Mono);
    QPainter painter(&image);
    QRgb backcolor=qRgb(255,255,255);
    image.fill(backcolor);
    QFont font;
    font.setFamily("SimSun");
    font.setPixelSize(50);
    font.setWeight(50);
    font.setItalic(false);
    font.setUnderline(false);
  //  font.setBold(false);
    painter.setFont(font);
    painter.drawText(image.rect(),Qt::AlignCenter|Qt::AlignTop,sss);
    QPixmap pix;
    pix=pix.fromImage(image);
    ui->label->setPixmap(pix);
   // w.resize(64,64);
   // QByteArray data;
    for(int i=0;i<128;i++)
    {
        data[i*4]=0xff-*(image.bits()+i*4);
        data[i*4+1]=0xff-*(image.bits()+i*4+1);
        data[i*4+2]=0xff-*(image.bits()+i*4+2);
        data[i*4+3]=0xff-*(image.bits()+i*4+3);

    }
    qDebug()<<data.size();
    QByteArray hh=data.toHex();
    QString str(hh);
    QFile file("data.txt");
    if (file.open(QIODevice::WriteOnly))
     {
        QTextStream out(&file);
        qDebug()<<str.size();
        out<<str.toLatin1();
        file.close();
     }
    ui->openbt->setEnabled(true);
}
