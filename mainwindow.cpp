#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFont>
#include <QRect>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    r=20;
    d=r*2;

    start();
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    for(int i=1;i<=10;i++)
        painter.drawLine(d,d*i,d*9,d*i);
    painter.drawLine(d,d,d,d*10);
    painter.drawLine(d*9,d,d*9,d*10);
    for(int i=2;i<=8;i++)
    {
        painter.drawLine(d*i,d,d*i,d*5);
        painter.drawLine(d*i,d*6,d*i,d*10);
    }
    painter.drawLine(d*4,d,d*6,d*3);
    painter.drawLine(d*6,d,d*4,d*3);
    painter.drawLine(d*4,d*10,d*6,d*8);
    painter.drawLine(d*6,d*10,d*4,d*8);

    QRect rect;

    for(int i=0;i<32;i++)
    {
        if(s[i].dead)
            continue;

        rect=QRect(s[i].x*d-r,s[i].y*d-r,d,d);

        if(s[i].choose)
            painter.setBrush(Qt::gray);
        else
            painter.setBrush(Qt::white);

        painter.setPen(Qt::black);
        painter.drawEllipse(QPoint(s[i].x*d,s[i].y*d),r,r);
        if(s[i].side)
            painter.setPen(Qt::red);
        else
            painter.setPen(Qt::black);
        painter.setFont(QFont("楷体",r*1.2,1500,false));
        painter.drawText(rect,Qt::AlignHCenter|Qt::AlignVCenter,s[i].word);
    }
    if(s[4].dead)
        ui->label->setText(QString("Red WIN!"));
    if(s[27].dead)
        ui->label->setText(QString("Black WIN!"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::ifRed(int n)
{
    if(n>15)
        return true;
    else
        return false;
}

QPoint  MainWindow::getXY(QPoint pt)
{
    if(pt.x()<r||pt.y()<r||pt.x()>=d*9+r||pt.y()>=d*10+r)
        return QPoint(-1,-1);

    return QPoint(((pt.x()/r+1)/2)*d,((pt.y()/r+1)/2)*d);	//这是简化后的代码
}

int MainWindow::haveStone(QPoint pt)
{
    for(int i=0;i<32;i++)
    {
        if(s[i].dead)
            continue;
        if((s[i].x==pt.x()/d) && (s[i].y==pt.y()/d))
            return i;
        continue;
    }
    return -1;
}
void MainWindow::mouseReleaseEvent(QMouseEvent *ev)
{
    QPoint pt=ev->pos();
    pt=getXY(pt);
    int id=haveStone(pt);

    if(!s[getKingID(id)].dead)		//检测本方King是否Dead
        persionMove(id,pt);

    update();
}

void MainWindow::persionMove(int &id,QPoint &pt)
{
    if(select==-1)	//第一次点击
    {
        if(id!=-1)  //id!=-1 表示点击的位置有棋子
        {
            if(s[id].side==redTurn)	//如果side与redTurn相等，表示该本方下棋
            {
                s[id].choose=!s[id].choose;
                select=id;
                redTurn=!redTurn;
            }
        }
    }
    else  //第二次点击
    {
        if(id!=-1) 
        {
            if(s[select].side==s[id].side)
            {
                s[select].choose=!s[select].choose;
                s[id].choose=!s[id].choose;
                select=id;
            }
            else
            {
                if(canMove(select,pt))
                {
                    s[select].x=s[id].x;
                    s[select].y=s[id].y;
                    s[id].dead=true;
                    if(s[select].side)
                        ui->label->setText(QString("Black MOVE!"));
                    else
                        ui->label->setText(QString("Red MOVE!"));
                    resetting(select);	//重置函数
                }
                else
                {
                    resetting(select);
                    redTurn=!redTurn;
                }
            }
        }
        else            //if have no stone
        {
            if(canMove(select,pt))
            {

                s[select].x=pt.x()/d;
                s[select].y=pt.y()/d;

                if(s[select].side)
                    ui->label->setText(QString("Black MOVE!"));
                else
                    ui->label->setText(QString("Red MOVE!"));
                resetting(select);
            }
            else
            {
                resetting(select);
                redTurn=!redTurn;
            }
        }
    }
}

void MainWindow::resetting(int n)
{
    s[n].choose=false;
    select=-1;
}

bool MainWindow::king_RedAndBlack(int n,QPoint pt)
{
    int num=0;

    if(n==4)
    {
        num=numberOfstone(27,pt);
    }
    else
    {
        num=numberOfstone(4,pt);
    }

    if(num == -1 || num != 0)
        return true;
    return false;
}

int MainWindow::getKingID(int n)
{
    bool side=ifRed(n);
    if(side)
        return 27;
    else
        return 4;

    return -1;
}

void MainWindow::start()
{
    select=-1;
    redTurn=true;

    for(int i=0;i<32;i++)
    {
        s[i].word=intToStone(i);
        s[i].dead=false;
        s[i].side=ifRed(i);
        s[i].choose=false;
    }
    for(int i=0;i<9;i++)
    {
        s[i].x=i+1;
        s[i].y=1;
        s[i+23].x=i+1;
        s[i+23].y=10;
    }
    for(int i=0;i<2;i++)
    {
        s[i+9].x=6*i+2;
        s[i+9].y=3;
        s[i+21].x=6*i+2;
        s[i+21].y=8;
    }
    for(int i=0;i<5;i++)
    {
        s[i+11].x=2*i+1;
        s[i+11].y=4;
        s[i+16].x=2*i+1;
        s[i+16].y=7;
    }
}

int MainWindow::max(int x, int y)
{
    if(x>y)
        return x;
    else
        return y;
}

int MainWindow::min(int x, int y)
{
    if(x>y)
        return y;
    else
        return x;
}

int MainWindow::len(int x, int y)
{
    return max(x,y)-min(x,y);
}

int MainWindow::numberOfstone(int n, QPoint p)
{
    int num=0;
    if(s[n].x!=p.x()/d && s[n].y!=p.y()/d)
        num=-1;

    if(s[n].x==p.x()/d)
    {
        int MIN=min(s[n].y,p.y()/d);
        int MAX=max(s[n].y,p.y()/d);
        for(int i=MIN+1;i<MAX;i++)
        {
            if(haveStone(QPoint(s[n].x*d,i*d))==-1)
                continue;
            num++;
        }
    }
    if(s[n].y==p.y()/d)
    {
        int MIN=min(s[n].x,p.x()/d);
        int MAX=max(s[n].x,p.x()/d);
        for(int i=MIN+1;i<MAX;i++)
        {
            if(haveStone(QPoint(i*d,s[n].y*d))==-1)
                continue;
            num++;
        }
    }
    return num;
}

int MainWindow::getCenterXY(int x, int y)
{
    return (x+y)/2;
}

bool MainWindow::canMove(int n,QPoint p)
{
    if(s[n].choose)
    {
        int N,xN,yN;
        xN=len(s[n].x,p.x()/d);
        yN=len(s[n].y,p.y()/d);
        N=xN+10*yN;

        switch(n)
        {
        case 27:case 4:
            return KingMove(n,p,N);
        case 26:case 28:case 3:case 5:
            return AdvisorMove(n,p,N);
        case 25:case 29:case 2:case 6:
            return BishopMove(n,p,N);
        case 24:case 30:case 1:case 7:
            return KnightMove(n,p,N);
        case 23:case 31:case 0:case 8:
            return RookMove(n,p);
        case 21:case 22:case 9:case 10:
            return CannonMove(n,p);
        case 16:case 17:case 18:case 19:case 20:
        case 11:case 12:case 13:case 14:case 15:
            return PawnMove(n,p,N);
        default:
            return false;
        }
    }
    return false;
}

bool MainWindow::KingMove(int n, QPoint p,int N)
{
    if(N==1 || N==10)
    {
        if(king_RedAndBlack(n,p))
        {
            if(p.x()/d>=4 && p.x()/d<=6)
            {
                if(n==27)
                {
                    if(p.y()/d>=8)
                        return true;
                }
                else
                {
                    if(p.y()/d<=3)
                        return true;
                }
            }
        }
    }
    return false;
}

bool MainWindow::KnightMove(int n, QPoint p,int N)
{
    if(N==21)
    {
        if(haveStone(QPoint(s[n].x*d,getCenterXY(s[n].y*d,p.y())))==-1)
            return true;
    }
    if(N==12)
    {
        if(haveStone(QPoint(getCenterXY(s[n].x*d,p.x()),s[n].y*d))==-1)
            return true;
    }
    return false;
}

bool MainWindow::RookMove(int n, QPoint p)
{
    if(numberOfstone(n,p)==0)
        return true;
    return false;
}

bool MainWindow::AdvisorMove(int n, QPoint p,int N)
{
    if(N==11 && p.x()/d<=6 && p.x()/d>=4)
    {
        if(s[n].side && p.y()/d>=8)
            return true;
        if(!s[n].side && p.y()/d<=3)
            return true;
    }
    return false;
}

bool MainWindow::BishopMove(int n, QPoint p,int N)
{   
    if(N==22)
    {
        QPoint ps;
        int x=getCenterXY(s[n].x*d,p.x());
        int y=getCenterXY(s[n].y*d,p.y());
        ps=QPoint(x,y);
        if(s[n].side && p.y()/d>=6)
        {
            if(haveStone(ps)==-1)
                return true;
        }
        if(!s[n].side && p.y()/d<=5)
        {
            if(haveStone(ps)==-1)
                return true;
        }
    }
    return false;
}

bool MainWindow::CannonMove(int n, QPoint p)
{
    if(numberOfstone(n,p)!=-1)
    {
        int ident=haveStone(p);
        if(ident==-1)
        {
            if(numberOfstone(n,p)==0)
                return true;
        }
        else
        {
            if(numberOfstone(n,p)==1)
                return true;
        }
    }
    return false;
}

bool MainWindow::PawnMove(int n, QPoint p,int N)
{
    if(s[n].side)
    {
        if(N==1 && s[n].y<6)
            return true;
        if(N==10 && s[n].y>p.y()/d)
            return true;
    }
    else
    {
        if(N==1 && s[n].y>5)
            return true;
        if(N==10 && s[n].y<p.y()/d)
            return true;
    }

    return false;
}

QString MainWindow::intToStone(int n)
{
    switch(n)
    {
    case 27:
        return "帅";
    case 26:case 28:
        return "仕";
    case 25:case 29:
        return "相";
    case 24:case 30:case 1:case 7:
        return "馬";
    case 23:case 31:case 0:case 8:
        return "車";
    case 21:case 22:case 9:case 10:
        return "炮";
    case 16:case 17:case 18:case 19:case 20:
        return "兵";
    case 4:
        return "将";
    case 3:case 5:
        return "士";
    case 2:case 6:
        return "象";
    case 11:case 12:case 13:case 14:case 15:
        return "卒";
    default:
        return "";
    }
}

void MainWindow::on_pushButton_clicked()
{
    start();
    ui->label->setText(QString("Red MOVE!"));
    update();
}
