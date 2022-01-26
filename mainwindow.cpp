#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QDebug>
#include <QtMath>
#include <string>
#include <tuple>
#include <QTextEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->valueA, &QLineEdit::textChanged,this, MainWindow::QuadraticEquationCalculation);
    connect(ui->valueB, &QLineEdit::textChanged,this, MainWindow::QuadraticEquationCalculation);
    connect(ui->valueC, &QLineEdit::textChanged,this, MainWindow::QuadraticEquationCalculation);

    connect(ui->valueDimensionA, &QLineEdit::textChanged,this, MainWindow::CalculationAngleTriangle);
    connect(ui->valueDimensionB, &QLineEdit::textChanged,this, MainWindow::CalculationAngleTriangle);
    connect(ui->valueAgle, &QLineEdit::textChanged,this, MainWindow::CalculationAngleTriangle);
}
MainWindow::~MainWindow()
{
    delete ui;
}
//первое задание
bool ChackVallue(QLineEdit *q )
{
    if(q->text().size() != 0)
        return true;
    return false;
}

double CalcelateDiscriminant(qint32 a, qint32 b, qint32 c )
 {
     return qPow(static_cast<double>(b),2)-4*a*c;
 }

void OutVal(Ui::MainWindow *ui,QString &x1, QString &x2)
{
    ui->calcValX1->setText("X1 = " + x1);
    ui->calcValX2->setText("X2 = " + x2);
}

void MainWindow::QuadraticEquationCalculation(const QString &arg1)
{
    qDebug()<< arg1.toInt();
    if(ChackVallue(ui->valueA) && ChackVallue(ui->valueB) && ChackVallue(ui->valueC))
    {
        int _a = ui->valueA->text().toInt();
        int _b = ui->valueB->text().toInt();
        int _c = ui->valueC->text().toInt();

        if (_a == 0)
        {
            QString x1 = QString::number( (double)(-1.0)*(_c/_b));
            QString x2 = QString::number(0);
            OutVal(ui,x1,x2);
            return;
        }
        auto d = CalcelateDiscriminant(_a,_b,_c);
         qDebug()<< d;
        QString x1,x2;

        if( d >= 0)
        {
            x1 = QString::number((-1* _b - qSqrt(d)) / (2*_a));
            x2 = QString::number((-1* _b + qSqrt(d)) / (2*_a));
        }
        else
        {
            x1 = "Нет корей";
            x2 =" ";
        }
        OutVal(ui,x1,x2);

    }


}
//конец первого задания

// второе задание

void MainWindow:: CalculationAngleTriangle(const QString &arg1)
{
    if(ChackVallue(ui->valueDimensionA) && ChackVallue(ui->valueDimensionB) && ChackVallue(ui->valueAgle))
    {
        double angle = ui->valueAgle->text().toDouble();
        double a = ui->valueDimensionA->text().toDouble();
        double b = ui->valueDimensionB->text().toDouble();
        double pi = qAsin(1.0)*2;
        double rad = ui->degrees->isChecked()?static_cast<double>( angle) * pi /180.0:1.0;
        double pow_a = qPow(a,2);
        double pow_b = qPow(b,2);
        qDebug() << pow_a << pow_b << rad << qCos(rad);
        double _angle = 2*a*b*qCos(rad);
        double c = pow_a+pow_b - _angle;
        qDebug()<< angle;
        ui->valueDimensionC->setText("Сторона С =" + QString::number( qSqrt(c) ));


    }

}
//конец второго задания

//третье задание

void MainWindow::on_copyButton_clicked()
{
    if (ui->plainTextEdit2->size().isEmpty())
        ui->plainTextEdit2->setPlainText( ui->plainTextEdit1->toPlainText());
    else
    {
        QString temp = ui->plainTextEdit2->toPlainText();
        temp += ui->plainTextEdit1->toPlainText();
        ui->plainTextEdit2->clear();
        ui->plainTextEdit2->setPlainText(temp);
    }
}


void MainWindow::on_moveButton_clicked()
{
     ui->plainTextEdit2->clear();
     ui->plainTextEdit2->setPlainText( ui->plainTextEdit1->toPlainText());
     ui->plainTextEdit1->clear();
}


void MainWindow::on_pushButton_clicked()
{
     QString html = "<font color='red'>Hello</font>";

    QTextEdit *txt = new QTextEdit();
    txt->setHtml(html);
    ui->plainTextEdit1->setPlainText(txt->toHtml());
}
