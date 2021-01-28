#include <QtTest>

#include "../../Game/handlers/objectmanager.h"
#include "../../Game/handlers/gameeventhandler.h"

class ObjectManagerTests : public QObject
{
    Q_OBJECT

public:
    ObjectManagerTests();
    ~ObjectManagerTests();

private:
    std::shared_ptr<Student::ObjectManager> objmanager_;
    std::shared_ptr<Student::GameEventHandler> GEhandler_;

private slots:
    void addTilesTest();
    void getTiletest();
};

ObjectManagerTests::ObjectManagerTests()
{
    objmanager_ = std::make_shared<Student::ObjectManager>();
    GEhandler_ = std::make_shared<Student::GameEventHandler>();

}

ObjectManagerTests::~ObjectManagerTests()
{

}

void ObjectManagerTests::addTilesTest()
{
    std::vector<std::shared_ptr<Course::TileBase> > tiles;
    tiles.push_back(std::make_shared<Course::TileBase>(Course::Coordinate(1,1), GEhandler_, objmanager_));
    tiles.push_back(std::make_shared<Course::TileBase>(Course::Coordinate(2,1), GEhandler_, objmanager_));
    objmanager_->addTiles(tiles);
    auto tile = std::make_shared<Course::TileBase>(Course::Coordinate(3,1), GEhandler_, objmanager_);
    objmanager_->addTile(tile);

    std::vector<Course::Coordinate> coordinates;
    coordinates.push_back(Course::Coordinate(1,1));
    coordinates.push_back(Course::Coordinate(2,1));
    coordinates.push_back(Course::Coordinate(3,1));

    auto tiles_ = objmanager_->getTiles(coordinates);
    QVERIFY(tiles_.size() == 3);
    QVERIFY(tiles_[2] == tile);

}

void ObjectManagerTests::getTiletest()
{
    QVERIFY(objmanager_->getTile(3) == nullptr);
    QVERIFY(objmanager_->getTile(Course::Coordinate(5,5)) == nullptr);
    auto tile = objmanager_->getTile(Course::Coordinate(1,1));
    QVERIFY(tile != nullptr);
    QVERIFY(objmanager_->getTile(tile->ID) == tile);


}




QTEST_APPLESS_MAIN(ObjectManagerTests)

#include "tst_objectmanagertests.moc"
