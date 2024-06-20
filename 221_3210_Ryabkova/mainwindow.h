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

    void on_buttonClear_clicked();

    void updateScore(int number);

private:
    Ui::MainWindow *ui;
    int m_score;
    card *m_cards[9];
};
#endif // MAINWINDOW_H
