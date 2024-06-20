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
    for (int i = 0; i < 9; ++i) {
        delete m_cards[i];
    }
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if (ui->EditPin->text() == "1234") {
            ui->stackedWidget->setCurrentIndex(0);
            ui->EditPin->setText("");
            for (int i = 0; i < 9; ++i) {
                m_cards[i] = new card(this);
                ui->gridLayout_3->addWidget(m_cards[i], i / 3, i % 3);
            }

            connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);
    } else {
        ui->labelPin->setText("Неверный пинкод");
        ui->labelPin->setStyleSheet("color:red;");
        ui->EditPin->setText("");
    }
}


void MainWindow::on_buttonClear_clicked()
{

}


void MainWindow::updateScore(int number)
{
    m_score += number;
    ui->labelScore->setText(QString::number(m_score));
}

