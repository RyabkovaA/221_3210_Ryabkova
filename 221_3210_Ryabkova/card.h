#ifndef CARD_H
#define CARD_H

#include <QWidget>

namespace Ui {
class card;
}

class card : public QWidget
{
    Q_OBJECT

public:
    explicit card(QWidget *parent = nullptr);
    ~card();

signals:
    void numberGenerated(int number);

private slots:
    void on_buttonShow_clicked();

private:
    Ui::card *ui;
    int m_number;
};

#endif // CARD_H
