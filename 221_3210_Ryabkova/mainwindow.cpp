#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if (ui->EditPin->text() == "1234") {
            ui->stackedWidget->setCurrentIndex(0);
            ui->EditPin->setText("");
    } else {
        ui->labelPin->setText("Неверный пинкод");
        ui->labelPin->setStyleSheet("color:red;");
        ui->EditPin->setText("");
    }
}

