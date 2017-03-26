#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QPainter>
#include <QPoint>
#include <QLabel>
#include <QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //Define the function
    explicit MainWindow(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);
    void mouseReleaseEvent(QMouseEvent *ev);
    ~MainWindow();

    bool ifRed(int n);
    QPoint getXY(QPoint pt);   //Return the ident of stone,else return -1.
    QString intToStone(int n);
    int haveStone(QPoint pt);
    void persionMove(int &id,QPoint &pt);
    void resetting(int n);
    void start(void);
    bool king_RedAndBlack(int n,QPoint pt);
    int getKingID(int n);

    bool canMove(int n,QPoint p);
    bool KingMove(int n,QPoint p,int N);
    bool KnightMove(int n,QPoint p,int N);
    bool RookMove(int n,QPoint p);
    bool AdvisorMove(int n,QPoint p,int N);
    bool BishopMove(int n,QPoint p,int N);
    bool CannonMove(int n,QPoint p);
    bool PawnMove(int n,QPoint p,int N);

    int max(int x,int y);
    int min(int x,int y);
    int len(int x,int y);
    int numberOfstone(int n,QPoint p);
    int getCenterXY(int x,int y);

    //Define the member value
    int r;
    int d;
    int select;
    bool redTurn;

    typedef struct{
        int x,y;
        bool side,dead,choose;
        QString word;
    }Stone;

    Stone s[32];

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
