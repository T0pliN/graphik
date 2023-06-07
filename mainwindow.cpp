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

    double xmin = -10, xmax = 10;
    double ymin = -10, ymax = 10;
    double x, y;
    int xg, yg;
    int xgmin = 0, xgmax = pm.width();
    int ygmin = 0, ygmax = pm.height();
    if (ui->lineEdit_2->text() != "") {
        xmin = ui->lineEdit_2->text().toDouble();
    }
    if (ui->lineEdit_3->text() != "") {
        xmax = ui->lineEdit_3->text().toDouble();
    }


    double ans = 0;
    /* x = xmin;
      QString stro = ui->lineEdit_1->text();
                 //stro.replace("x","(" + QString::number(x) + ")");  Эти три строчки должны были считать ymin и ymax,
                 //calc(stro.toStdString(), ans);                     основываясь на первом значении ans. Но график не
                 //ui->label_6->setText(QString::number(ans));        строился, и ошибку я найти не успел.
    ymin = ans;
    ymax = ans;
    while (x <= xmax) {
        QString stri = stro;
        stri.replace("x","(x)");                 Эта часть кода должна считать ymin и ymax  на заданном отрезке иксов.
        stri.replace("x",QString::number(x));    Но по причине, которую я не успел выяснить, тангенс в этом коде
        calc(stri.toStdString(), ans);           строится неправильно. Поэтому я решил сделать эту часть кода
        y = ans;                                 комментарием.
        if (y > ymax) ymax = y;
        if (y < ymin) ymin = y;
        x+= 0.001;
    } */

    if (ui->lineEdit_5->text() != "") {
        ymax = ui->lineEdit_5->text().toDouble();
    }

    if (ui->lineEdit_4->text() != "") {
        ymin = ui->lineEdit_4->text().toDouble();
    }

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

    ans = 0;
    x = xmin;
    QString s1 = ui->lineEdit_1->text();
    s1.replace("x","(" + QString::number(xmin) + ")");
    int er = calc(s1.toStdString(), ans);
    int est;
    if (er == 0) {
        path.moveTo(x0 + kx * xmin, y0 + ky * ans);
    } else {
        est = -1;
    }

    while (x <= xmax && ymin != ymax && xmin != xmax) {
        QString str = ui->lineEdit_1->text();
        str.replace("x","(" + QString::number(x) + ")");
        er = calc(str.toStdString(), ans);
        if (er == 0) {
        y = ans;
        xg = x0 + kx * x;
        yg = y0 + ky * y;
        if (est == -1){
            path.moveTo(xg, yg);
            est = 1;
        } else {
            if (y > ymax || y < ymin) {
                path.moveTo(xg,yg);
            } else {
                path.lineTo(xg,yg);
            }
        }
        }
        x += stepx;
    }

    painter.drawPath(path);
    ui->label->setPixmap(pm);
    painter.end();
}
