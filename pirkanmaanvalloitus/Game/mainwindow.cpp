#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "settingwindow.hh"
#include "winwindow.h"
#include "losewindow.h"
#include <QDebug>
#include <QGraphicsRectItem>
#include <QPixmap>
#include <QGraphicsTextItem>
#include <QtGui>
#include <QLabel>
#include "graphics/map.h"

#include <math.h>
#include "tiles/grassland.h"
#include "core/coordinate.h"
#include "interfaces/iobjectmanager.h"
#include "handlers/objectmanager.h"
#include "handlers/gameeventhandler.h"
#include <QGraphicsPixmapItem>
#include "graphics/gamescene.h"


MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    GEhandler = std::make_shared<Student::GameEventHandler>();
    objmanager = std::make_shared<Student::ObjectManager>();
    gamescene = std::make_shared<Student::GameScene>(this, 10, 10, objmanager, GEhandler);
    gamescene_ptr = gamescene.get();
    bldhandler = std::make_shared<Student::BuildingHandler>(gamescene_ptr, objmanager, GEhandler);

    ui->setupUi(this);
    setWindowTitle("Pirkanmaan Valloitus");
    ui->graphicsView->setScene(dynamic_cast<QGraphicsScene*>(gamescene_ptr));
    ui->graphicsView->setBackgroundBrush(QBrush(QPixmap("://images/BG.png")));
    ui->graphicsView->setMouseTracking(true);
    ui->progressBar->setValue(0);

    Settingwindow *s = new Settingwindow;
    connect(s, SIGNAL(sendSettings(std::string, std::string)),this,SLOT(generateWorld(std::string, std::string)));
    s->exec();


    timer = new QTimer(this);

    victoryChecker = new QTimer(this);
    QObject::connect(victoryChecker,SIGNAL(timeout()),this, SLOT(victoryCheck()));
    victoryChecker->start(1000);

    defeatChecker = new QTimer(this);
    QObject::connect(defeatChecker,SIGNAL(timeout()),this, SLOT(defeatCheck()));
    defeatChecker->start(1000);


    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(tickhandler()));
    QObject::connect(ui->graphicsView->scene(), SIGNAL(sendMousePos(QPointF&)), this, SLOT(showCoord(QPointF&)));
    QObject::connect(ui->graphicsView->scene(), SIGNAL(highlightPos(QPoint&, QPoint&)), this, SLOT(addHighlight(QPoint&, QPoint&)));
    QObject::connect(ui->graphicsView->scene(),SIGNAL(sendMessage(std::string&)),this,SLOT(showInfo(std::string&)));
    timer->start(2000);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::generateWorld(std::string map_size, std::string player_name)
{
    player_ = player_name;
    owner_ = std::make_shared<Course::PlayerBase>(player_);
    gameMap = std::make_shared<Student::Map>(gamescene_ptr, map_size, objmanager, GEhandler);
    gameMap->InitializeMap();

    showResources();

}

    //tickhandler
void MainWindow::tickhandler(){
    ui->graphicsView->viewport()->update();
    GEhandler->modifyResources(owner_, Student::ConstResourceMaps::PASSIVE_COST);
    showResources();
    GEhandler->modifyResource(owner_, Course::STONE, objmanager->gatherResources(owner_, "Stone"));
    GEhandler->modifyResource(owner_, Course::WOOD, objmanager->gatherResources(owner_, "Forest"));

}

void MainWindow::victoryCheck(){
    if(objmanager->getProgress(owner_)>=95){
        qDebug()<< "voitto";
        timer->stop();
        victoryChecker->stop();
        WinWindow *w = new WinWindow;
        w->exec();

    }
}

void MainWindow::defeatCheck(){
    if(GEhandler->getResource(Course::BasicResource::FOOD)<=0){
        qDebug()<<"häviö";
        timer->stop();
        defeatChecker->stop();
        LoseWindow *l = new LoseWindow;
        l->exec();
    }
}

void MainWindow::showCoord(QPointF& point)
{
    ui->coordinateLabel->setText("x: " + QString::number(point.rx()) + " y: " + QString::number(point.ry()));
}


void MainWindow::addHighlight(QPoint& point, QPoint& coord)
{
    if(highlight_ == nullptr){
        QPixmap highlightPix = QPixmap("://images/redhighlight.png");
        highlight_ = new QGraphicsPixmapItem(highlightPix);
        highlight_->setZValue(1);
        gamescene_ptr->addItem(highlight_);
        highlight_->setPos(point);
    }
    else{
        highlight_->setPos(point);
    }
    coord_ = coord;
    ui->graphicsView->viewport()->update();

}

void MainWindow::showResources()
{
    ui->foodLabel->setNum(GEhandler->getResource(Course::BasicResource::FOOD));
    ui->moneyLabel->setNum(GEhandler->getResource(Course::BasicResource::MONEY));
    ui->woodLabel->setNum(GEhandler->getResource(Course::BasicResource::WOOD));
    ui->stoneLabel->setNum(GEhandler->getResource(Course::BasicResource::STONE));
}



void MainWindow::on_houseSelectionButton_clicked()
{
    if(highlight_ != nullptr){
        QPoint pos = highlight_->pos().toPoint()+QPoint(32,16);
        if(bldhandler->addHouse(pos, coord_, owner_)){
            showResources();
        }
    }
    else{
        gamescene_ptr->emitMessage("You must select a tile first");
    }
    ui->graphicsView->viewport()->update();
    ui->progressBar->setValue(objmanager->getProgress(owner_));
    showResources();

}

void MainWindow::on_deleteBuildingButton_clicked()
{
    if(highlight_ != nullptr){
        QPoint pos = highlight_->pos().toPoint()+QPoint(32,16);
        bldhandler->deleteBuilding(pos);
    }
    ui->graphicsView->viewport()->update();
}

void MainWindow::on_hqSelectionButton_clicked()
{

    if(highlight_ != nullptr){
        QPoint pos = highlight_->pos().toPoint()+QPoint(32,16);
        if(bldhandler->addHQ(pos, coord_, owner_)){
            showResources();
        }

    }
    else{
        gamescene_ptr->emitMessage("You must select a tile first");
    }
    ui->graphicsView->viewport()->update();
    ui->progressBar->setValue(objmanager->getProgress(owner_));
    showResources();

}



void MainWindow::on_bridgeSelectionButton_clicked()
{
    if(highlight_ != nullptr){
        QPoint pos = highlight_->pos().toPoint()+QPoint(32,16);
        if(bldhandler->addBridge(pos, coord_, owner_)){
            showResources();
        }
    }
    else{
        gamescene_ptr->emitMessage("You must select a tile first");
    }
    ui->graphicsView->viewport()->update();
    ui->progressBar->setValue(objmanager->getProgress(owner_));
    showResources();
}



void MainWindow::on_marketSelectionButton_clicked()
{
    if(highlight_ != nullptr){
        QPoint pos = highlight_->pos().toPoint()+QPoint(32,16);
        if(bldhandler->addMarket(pos, coord_, owner_)){
            ui->sellButton->setEnabled(true);
            ui->buyButton->setEnabled(true);
            showResources();
        }
    }
    else{
        gamescene_ptr->emitMessage("You must select a tile first");
    }
    ui->graphicsView->viewport()->update();
    ui->progressBar->setValue(objmanager->getProgress(owner_));
    showResources();
}

void MainWindow::showInfo(std::string& msg){
    QString str = QString::fromUtf8(msg.c_str());
    ui->infoboxlabel->setText(str);
}




void MainWindow::on_farmSelectionButton_clicked()
{
    if(highlight_ != nullptr){
        QPoint pos = highlight_->pos().toPoint()+QPoint(32,16);
        if(bldhandler->addFarm(pos, coord_, owner_)){
            showResources();
        }
    }
    else{
        gamescene_ptr->emitMessage("You must select a tile first");
    }
    ui->graphicsView->viewport()->update();
    ui->progressBar->setValue(objmanager->getProgress(owner_));
    showResources();
}


void MainWindow::on_sellButton_clicked()
{
    if(GEhandler->compareResources(Student::ConstResourceMaps::SELL_RESOURCES_COST)){
           GEhandler->modifyResources(owner_, Student::ConstResourceMaps::SELL_RESOURCES_COST);
    }
    else gamescene_ptr->emitMessage("Not enough resources");
    showResources();
}

void MainWindow::on_buyButton_clicked()
{
    if(GEhandler->compareResources(Student::ConstResourceMaps::BUY_RESOURCES_COST)){
           GEhandler->modifyResources(owner_, Student::ConstResourceMaps::BUY_RESOURCES_COST);
    }
    else gamescene_ptr->emitMessage("Not enough resources");
    showResources();
}
