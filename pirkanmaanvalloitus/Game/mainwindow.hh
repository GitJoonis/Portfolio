#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QPainter>
#include <QImage>
#include <QGraphicsPixmapItem>
#include <QLayout>
#include <Qt>
#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <map>
#include <vector>
#include "handlers/objectmanager.h"
#include "interfaces/igameeventhandler.h"
#include "graphics/simplegamescene.h"
#include "graphics/simplemapitem.h"
#include "graphics/gamescene.h"
#include "graphics/map.h"
#include <QGraphicsPixmapItem>
#include "buildings/farm.h"
#include "buildings/headquarters.h"
#include "buildings/house.h"
#include "handlers/buildinghandler.h"
#include "buildings/bridge.h"
#include "buildings/market.h"
#include "core/basicresources.h"
#include "core/resourcemaps.h"
#include <QList>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


public slots:
    /*
     * \brief generateWorld is used to give information for the Map class
     * \param map_size
     * \param player_name
     */
    void generateWorld(std::string map_size, std::string player_name);
    /*!
     * \brief showCoord is used to show the coordinates of mouse in game area
     * \param point gives the coordinates as a QPoint
     */
    void showCoord(QPointF& point);

    /*
     * \brief addHighlight is used to highlight clicked tiles
     * \param point coordinates as a QPoint
     * \param coord isometric coordinates as a QPoint
     */
    void addHighlight(QPoint& point, QPoint& coord);

    /*
     * \brief showResources is used to update the resources in the game window
     */
    void showResources();

    /*
     * \brief showInfo is used to show messages in the game window
     * \param msg message to be shown
     */
    void showInfo(std::string& msg);

signals:



private slots:
    /*
     * \brief tickhandler is used to update resources every game tick
     */
    void tickhandler();

    void victoryCheck();

    void defeatCheck();

    void on_houseSelectionButton_clicked();

    void on_deleteBuildingButton_clicked();

    void on_hqSelectionButton_clicked();

    void on_bridgeSelectionButton_clicked();

    void on_marketSelectionButton_clicked();

    void on_farmSelectionButton_clicked();

    void on_sellButton_clicked();

    void on_buyButton_clicked();

private:
    QPoint coord_;
    QGraphicsPixmapItem* highlight_ = nullptr;
    Ui::MainWindow *ui;
    QGraphicsScene* scene;
    QGraphicsItem* item;
    std::string player_;
    Course::ResourceMap resources_;
    std::shared_ptr<Course::PlayerBase> owner_ = nullptr;
    std::shared_ptr<Student::GameEventHandler> GEhandler = nullptr;
    std::shared_ptr<Student::ObjectManager> objmanager = nullptr;
    std::shared_ptr<Student::GameScene> gamescene = nullptr;
    std::shared_ptr<Student::BuildingHandler> bldhandler = nullptr;
    Student::GameScene* gamescene_ptr = nullptr;
    std::shared_ptr<Student::Map> gameMap = nullptr;
    QTimer *timer;
    QTimer *victoryChecker;
    QTimer *defeatChecker;


};

#endif // MAINWINDOW_HH
