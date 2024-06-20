#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "card.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void handleCardButtonClick();

    void resetGame();

    void showScoreMessage();


private:
    Ui::MainWindow *ui;
    card *m_cards[9];
    card *m_currentCard = nullptr;
    int m_score = 0;
    int m_visibleCount = 0;
};
#endif // MAINWINDOW_H
