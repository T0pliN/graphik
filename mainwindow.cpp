#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPainter"
#include "QPushButton"
#include "QPixmap"
#include "QtMath"
#include "QLabel"
#include "truepolka.h"
#include "QString"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(800, 600);
    button = new QPushButton(this);
    button->setGeometry(width() * 0.8625, height() * 0.0167, 100, 40);
    ui->label_3->setGeometry(width()*0.8625, height() * 0.33, width() * 0.05, height() * 0.05);
    ui->label_4->setGeometry(width()*0.8625, height() * 0.41, width() * 0.05, height() * 0.05);
    ui->label_5->setGeometry(width()*0.8625, height() * 0.5, width() * 0.05, height() * 0.05);
    ui->label_6->setGeometry(width()*0.8625, height() * 0.58, width() * 0.05, height() * 0.05);
    ui->lineEdit_2->setGeometry(width()*0.925, height()*0.33, width()*0.0625, height()*0.05);
    ui->lineEdit_3->setGeometry(width()*0.925, height()*0.41, width()*0.0625, height()*0.05);
    ui->lineEdit_4->setGeometry(width()*0.925, height()*0.5, width()*0.0625, height()*0.05);
    ui->lineEdit_5->setGeometry(width()*0.925, height()*0.58, width()*0.0625, height()*0.05);
    button->setText("Show Graphic");
    button->setStyleSheet("background: rgb(100, 255, 100)");
    connect(button, SIGNAL(clicked()), this, SLOT(buttonClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::buttonClicked()
{
    ui->label->setGeometry(width() * 0.0125, height() * 0.0997, width() * 0.8375, height() * 0.87);
    //ui->label_6->setGeometry(width()*0.8125, height() * 0.3333, width() * 0.9375, height() * 0.95);
    ui->label->setStyleSheet("color: rgb(50, 0, 70); background: rgb(100, 30, 60)");

    QPixmap pm(ui->label->width(), ui->label->height());
    QPainter painter;
    painter.begin(&pm);

    QPen pen;
    pen.setColor(0xffffff);
    pen.setWidth(2);
    pen.setCapStyle(Qt::RoundCap);
    painter.setPen(pen);
    pm.fill(Qt::black);

    //double xmin = ui->lineEdit_2->text().toDouble();
    //double xmax = ui->lineEdit_3->text().toDouble();
    //double ymin = ui->lineEdit_4->text().toDouble();
    //double ymax = ui->lineEdit_5->text().toDouble();
    double xmax = 10, xmin = -10;
    double ymin = -10, ymax = 10;

    int xgmin = 0, xgmax = pm.width();
    int ygmin = 0, ygmax = pm.height();

    double x, y;
    int xg, yg;
    double kx = (xgmax - xgmin) / (xmax-xmin), ky = (ygmin - ygmax)/(ymax-ymin);
    double x0 = xgmin - kx*xmin, y0 = ygmin - ky*ymax;

    pen.setColor(Qt::yellow);
    pen.setWidth(0.5);
    painter.setPen(pen);
    painter.drawLine(0, y0, pm.width(), y0);
    painter.drawLine(x0, 0, x0, pm.height());

    double stepx = (xmax - xmin)/(xgmax - xgmin);

    QPainterPath path;
    pen.setColor(Qt::red);
    pen.setWidth(3);
    painter.setPen(pen);
    x = xmin;

    double ans;
    QString s1 = ui->lineEdit_1->text();
    s1.replace("x","(" + QString::number(xmin) + ")");
    int pz = calc(s1.toStdString(), ans);

    path.moveTo(x0 + kx * xmin, y0 + ky * ans);

    while (x <= xmax) {
        QString str = ui->lineEdit_1->text();
        str.replace("x","(" + QString::number(x) + ")");
        pz = calc(str.toStdString(), ans);
        y = ans;
        xg = x0 + kx * x;
        yg = y0 + ky * y;
        path.lineTo(xg,yg);        
        x += stepx;
        while ((yg > ygmax || yg < ygmin) && x <= xmax) {
            QString str = ui->lineEdit_1->text();
            str.replace("x","(" + QString::number(x) + ")");
            pz = calc(str.toStdString(), ans);
            y = ans;
            xg = x0 + kx * x;
            yg = y0 + ky * y;
            path.moveTo(xg,yg);
            x += stepx;
        }
        /*while (pz = -1 && x <= xmax) {
            QString str = ui->lineEdit_1->text();
            str.replace("x","(" + QString::number(x) + ")");
            pz = calc(str.toStdString(), ans);
            y = ans;
            xg = int(x0 + kx * x);
            yg = int(y0 + ky * y);
            path.moveTo(xg,yg);
            x += stepx;
        }*/
    }
    painter.drawPath(path);
    ui->label->setPixmap(pm);
    painter.end();
}
