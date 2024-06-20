#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_visibleCount(0)
    , m_score(0)
{
    ui->setupUi(this);

    for (int i = 0; i < 9; ++i) {
        m_cards[i] = new card(this);
        ui->gridLayout_3->addWidget(m_cards[i], i / 3, i % 3);
        connect(m_cards[i], &card::cardButtonClicked, this, &MainWindow::handleCardButtonClick);
    }

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);
    connect(ui->buttonClear, &QPushButton::clicked, this, &MainWindow::resetGame);

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
            ui->EditPin->clear();

    } else {
        ui->labelPin->setText("Неверный пинкод");
        ui->labelPin->setStyleSheet("color:red;");
        ui->EditPin->setText("");
    }
}

void MainWindow::handleCardButtonClick()
{
    card *clickedCard = qobject_cast<card*>(sender());
    if (!clickedCard)
        return;

    for (int i = 0; i < 9; ++i) {
        if (m_cards[i] == clickedCard) {
            m_cards[i]->showValue();
            m_currentCard = m_cards[i];
            ++m_visibleCount;
            // qDebug() << "visible counter " << m_visibleCount;
        }
    }

    m_score += clickedCard->cardValue();

    ui->labelScore->setText(QString::number(m_score));

    if (m_visibleCount == 3) {
        showScoreMessage();
    }
}


void MainWindow::resetGame()
{
    m_score = 0;
    for (int i = 0; i < 9; ++i) {
        m_cards[i]->hideNumber();
        m_cards[i]->generateNumber();
    }
    ui->labelScore->clear();
    m_visibleCount = 0;
}

void MainWindow::showScoreMessage()
{
    QString info_message = "Набранная сумма: " + QString::number(m_score);
    QMessageBox::information(this, "Результат", info_message);
    resetGame();
}

