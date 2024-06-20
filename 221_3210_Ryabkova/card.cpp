#include "card.h"
#include "ui_card.h"
#include <QRandomGenerator>

card::card(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::card)
    , m_number(0)
{
    ui->setupUi(this);
    // int m_number = QRandomGenerator::global()->bounded(-1000, 1000);
    // ui->labelNumber->setText(QString::number(m_number));
    connect(ui->buttonShow, &QPushButton::clicked, this, &card::on_buttonShow_clicked);

}

card::~card()
{
    delete ui;
}

void card::on_buttonShow_clicked()
{
    int m_number = QRandomGenerator::global()->bounded(-1000, 1000);
    ui->labelNumber->setText(QString::number(m_number));
    emit numberGenerated(m_number);
}

