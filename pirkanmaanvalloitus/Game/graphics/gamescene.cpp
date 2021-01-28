#include "gamescene.h"

namespace Student {


GameScene::GameScene(QWidget* parent, int width, int height, std::shared_ptr<Student::ObjectManager> objmanager,
                     std::shared_ptr<Student::GameEventHandler> GEhandler):
    QGraphicsScene(parent),
    width_(width),
    height_(height),
    handler_(GEhandler),
    objmanager_(objmanager)


{

    setScene();
}


void GameScene::setScene()
{
    if (boundRect_ != nullptr ){
        QGraphicsScene::removeItem(boundRect_);
    }
    //point 0,0 top middle
    QRect scenerect = QRect( -width_/2 * scale_x_ + 32, 0, width_ * scale_x_, height_ * scale_y_);
    addRect(scenerect, QPen(Qt::NoPen));
    setSceneRect(scenerect);
    boundRect_ = itemAt(scenerect.topLeft(), QTransform());
    // Draw on the bottom of all items
    boundRect_->setZValue(-1);
    
}

void GameScene::resize(int width, int height)
{
    width_ = width;
    height_ = height;
    setScene();
}

bool GameScene::event(QEvent *event)
{
    if(event->type() == QEvent::GraphicsSceneMousePress){

        QGraphicsSceneMouseEvent* mouse_event = dynamic_cast<QGraphicsSceneMouseEvent*>(event);
        QPointF point = mouse_event->scenePos();
        QGraphicsItem* pressed = itemAt(point, QTransform());
        QList<QGraphicsItem*> itemlist = items(point);

        if(pressed == nullptr){
            return 0;
        }

        else if ( pressed == boundRect_){
            return 1;
        }

        else if(pressed->type() == MapitemID){
            auto objAtMouse = static_cast<Student::MapItem*>(pressed)->getGameObject();
            std::string msg = "klikattu kohtaa: x:" + std::to_string(point.rx()) + " y:" + std::to_string(point.ry());
            emit sendMessage(msg);
            QPoint coord = objAtMouse->getCoordinate().asQpoint();
            QPoint pos = static_cast<Student::MapItem*>(pressed)->getPos();
            emit highlightPos(pos, coord);
            return 1;      
        }
        else return 0;
    }

    else if(event->type() == QEvent::GraphicsSceneMouseMove){
        QGraphicsSceneMouseEvent* mouse_event = dynamic_cast<QGraphicsSceneMouseEvent*>(event);
        QPointF point = mouse_event->scenePos();

        emit sendMousePos(point);
        return 1;
    }
    else return QGraphicsScene::event(event);
}

void GameScene::emitMessage(std::string msg)
{
    emit sendMessage(msg);

}




} //namespace
