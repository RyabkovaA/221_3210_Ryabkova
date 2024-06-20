#include "card.h"
#include "ui_card.h"
#include <QRandomGenerator>

card::card(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::card)
{
    ui->setupUi(this);

    generateNumber();

    // connect(ui->buttonShow, &QPushButton::clicked, this, &card::on_buttonShow_clicked);
    // m_number = QRandomGenerator::global()->bounded(-10, 10);
    // ui->labelNumber->setText(QString::number(m_number));
    // ui->labelNumber->setHidden(true);

}

card::~card()
{
    delete ui;
}


void card::on_buttonShow_clicked()
{
    emit cardButtonClicked();
}


void card::showValue()
{
    ui->labelNumber->setText(QString::number(m_number));
    ui->labelNumber->setHidden(false);
}

void card::hideNumber()
{
    ui->labelNumber->setHidden(true);
}

int card::cardValue() const
{
    return m_number;
}


void card::generateNumber()
{
    m_number = QRandomGenerator::global()->bounded(-10, 10);
}
