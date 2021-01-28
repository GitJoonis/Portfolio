#include "mapitem.h"
namespace Student{



MapItem::MapItem(const std::shared_ptr<Course::GameObject> &obj, int width, int height)
{
    itembrushes["Grassland"] = "://images/isometric_grassv2.png";
    itembrushes["Water"] = "://images/isometric_waterv3.png";
    itembrushes["Forest"] = "://images/isometric_treev2.png";
    itembrushes["Stone"] = "://images/isometric_stonev2.png";
    itembrushes["Sand"] = "://images/sand.png";
    itembrushes["House"] = "://images/isometric_housev2.png";
    itembrushes["HeadQuarters"] = "://images/castle.png";
    itembrushes["Bridge"] = "://images/bridge.png";
    itembrushes["Farmer"] = "://images/farmer.png";
    itembrushes["Miner"] = "://images/miner.png";
    itembrushes["Market"] = "://images/market.png";
    itembrushes["Farm"] = "://images/farmreadyv2.png";
    obj_ = obj;
    width_ = width;
    height_ = height;
    coord_ = obj_->getCoordinatePtr()->asQpoint();

    prepareGeometryChange();
    position_ = toIsometric();
    setTransformOriginPoint(coord_);
    setZValue(1);

}

QPainterPath MapItem::shape() const
{
    QPainterPath path;
    QPolygon boundingPoly;
    int x = position_.x();
    int y = position_.y();
    boundingPoly << QPoint(x+32,y);
    boundingPoly << QPoint(x+64,y+16);
    boundingPoly << QPoint(x+32,y+32);
    boundingPoly << QPoint(x,y+16);
    boundingPoly << QPoint(x+32,y);
    path.addPolygon(boundingPoly);
    return path;
}

QRectF MapItem::boundingRect() const
{
    return shape().boundingRect();
}

void MapItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED( option ) Q_UNUSED( widget )
    std::string type = obj_->getType();
    QString filename = QString::fromStdString(itembrushes.at(type));
    QPixmap pic = QPixmap(filename);
    painter->setPen(Qt::NoPen);
    painter->drawPath(shape());

    //different shape than other items, so different y coordinate for drawing
    if(type == "Forest" || type == "House" || type == "HeadQuarters" || type == "Market" || type == "Farm"){
        painter->drawPixmap(QPoint(position_.rx(), position_.ry() - 41), pic);
    }

    else painter->drawPixmap(position_, pic);
}

bool MapItem::isSameItem(std::shared_ptr<Course::GameObject> obj)
{
    return obj_ == obj;
}

std::shared_ptr<Course::GameObject> MapItem::getGameObject()
{
    return obj_;
}


QPoint MapItem::toIsometric()
{
    int i_x = (coord_.x() - coord_.y())*width_/2;
    int i_y = (coord_.x() + coord_.y())*height_/2;
    return QPoint(i_x, i_y);
}

QPoint MapItem::getPos()
{
    return position_;
}

int MapItem::type() const
{
    return UserType + 1;
}



} //namespace
