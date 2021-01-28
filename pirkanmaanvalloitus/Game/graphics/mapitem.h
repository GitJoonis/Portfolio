#ifndef MAPITEM_H
#define MAPITEM_H
#include <QGraphicsItem>
#include "core/gameobject.h"
#include <QPoint>
#include <QPainter>
#include <QGraphicsPixmapItem>
#include <map>
#include <QDebug>

namespace Student{

/*
 * \brief The MapItem class is a custom QGraphicsItem class that is used to represent tiles and buildings in the game
 */
class MapItem : public QGraphicsItem
{
public:

    MapItem(const std::shared_ptr<Course::GameObject> &obj, int width, int height);
    /*
      * \brief shape is used to describe the shape of the graphicsitem
      * \return shape as a QPainterPath
      */

     QPainterPath shape() const override;
     /*
      * \brief boundingRect is used to calculate the bounding rectangle of the graphicsitem
      * \return bounding rectangle as a QRect
      */
     QRectF boundingRect() const override;

     /*
      * \brief paint is used to paint the graphicsitem on the graphicsscene
      */
     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

     /*
      * \brief isSameItem returns truth value whether the given object is same object as the one represented by this graphicsitem
      * \param obj to be compared
      * \return truth value whether they were the same item
      */
     bool isSameItem(std::shared_ptr<Course::GameObject> obj);

     /*
      * \brief getGameObject
      * \return gameobject, that the graphicsitem represents
      */
     std::shared_ptr<Course::GameObject> getGameObject();

     /*
      * \brief toIsometric can be used to change cartesian coordinates into isometric coordinates
      * \return isometric coordinates as a QPoint
      */
     QPoint toIsometric();

     /*
      * \brief getPos returns the position of the graphicsitem
      * \return QPoint that contains the position
      */
     QPoint getPos();

     /*
      * \brief type number of the MapItem
      * \return type of the qgraphicsitem as an integer. MapItem always returns the same id.
      */
     int type() const override;


private:

    std::shared_ptr<Course::GameObject> obj_ = nullptr;
    int width_;
    int height_;
    QPoint coord_;
    QPoint position_;
    std::map<std::string, std::string> itembrushes;

};
}
#endif // MAPITEM_H
