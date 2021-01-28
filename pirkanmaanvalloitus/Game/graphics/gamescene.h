#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "QGraphicsScene"
#include "QGraphicsView"
#include "core/gameobject.h"
#include <QEvent>
#include <QDebug>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include "graphics/mapitem.h"
#include <math.h>
#include <QTransform>
#include "handlers/gameeventhandler.h"
#include "handlers/objectmanager.h"
#include <math.h>
#include <QList>
#include "handlers/gameeventhandler.h"


namespace Student{


class GameScene : public QGraphicsScene
{
    Q_OBJECT

public:
    /*
     * \brief GameScene represent the gamescene of the mainwindow
     * \param width scene width
     * \param height scene height
     * \param objmanager Objectmanager
     * \param GEhandler GameEventhandler
     */
    GameScene(QWidget* parent = nullptr,
              int width = 10,
              int height = 10,
              std::shared_ptr<Student::ObjectManager> objmanager = nullptr,
              std::shared_ptr<Student::GameEventHandler> GEhandler = nullptr);

    // default constructor
    ~GameScene() = default;

    /*
     * \brief sets the scene for the mainwindow
     */
    void setScene();
    /*
     * \brief resizes the scene
     * \param width scene width to change to
     * \param height scene height to change to
     */
    void resize(int width, int height);
    /*!
     * \brief event handles all the different mouse events inside the gamescene
     * \return truth value, whether or not the event was succesful
     */
    virtual bool event(QEvent* event) override;

    /*
     * \brief emitMessage is used to emit a message to the main window
     * \param msg message to be sended
     */
    void emitMessage(std::string msg);

signals:
    void sendMousePos(QPointF&);
    void highlightPos(QPoint&, QPoint&);
    void sendMessage(std::string&);


private:
    //qt reserves id's until 65536 so this magic number is used to identify MapItem class
    const int MapitemID = 65537;
    QGraphicsItem* boundRect_ = nullptr;
    int width_ = 0;
    int height_ = 0;
    std::shared_ptr<Student::GameEventHandler> handler_ = nullptr;
    std::shared_ptr<Student::ObjectManager> objmanager_ = nullptr;
    int scale_x_ = 64;
    int scale_y_ = 32;


};
}
#endif // GAMESCENE_H
