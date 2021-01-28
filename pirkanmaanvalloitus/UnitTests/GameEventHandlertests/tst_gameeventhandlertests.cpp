#include <QtTest>
#include "../../Game/handlers/gameeventhandler.h"

class GameEventHandlerTests : public QObject
{
    Q_OBJECT

public:
    GameEventHandlerTests();
    ~GameEventHandlerTests();
private:
    const ResourceMap test_pos = {
        {Course::NONE, 50},
        {Course::MONEY, 50},
        {Course::FOOD, 50},
        {Course::WOOD, 50},
        {Course::STONE, 50},
        {Course::ORE, 50}
    };
    const ResourceMap test_short = {
        {Course::NONE, 5},
        {Course::MONEY, 5},
        {Course::FOOD, 5}
    };

    const ResourceMap test_neg = {
        {Course::NONE, -500},
        {Course::MONEY, 60},
        {Course::FOOD, -100},
        {Course::WOOD, -200},
        {Course::STONE, 0},
        {Course::ORE, -1000}
    };

    const ResourceMap test_neg_small = {
        {Course::NONE, -25},
        {Course::MONEY, -25},
        {Course::FOOD, -25},
        {Course::WOOD, -25},
        {Course::STONE, -25},
        {Course::ORE, -25}
    };

private slots:
    void testModifyResource();
    void testModifyResources();


};

GameEventHandlerTests::GameEventHandlerTests()
{

}

GameEventHandlerTests::~GameEventHandlerTests()
{

}

void GameEventHandlerTests::testModifyResource()
{

    Student::GameEventHandler GEhandler;
    std::shared_ptr<Course::PlayerBase> player = std::make_shared<Course::PlayerBase>("player");
    GEhandler.modifyResource(player, Course::FOOD, 50);
    int modified_resources = GEhandler.getResource(Course::FOOD);
    QCOMPARE(modified_resources, 50);

    GEhandler.modifyResource(player, Course::STONE, 50);
    modified_resources = GEhandler.getResource(Course::STONE);
    QCOMPARE(modified_resources, 50);

    GEhandler.modifyResource(player, Course::MONEY, 50);
    modified_resources = GEhandler.getResource(Course::MONEY);
    QCOMPARE(modified_resources, 50);

    GEhandler.modifyResource(player, Course::WOOD, 50);
    modified_resources = GEhandler.getResource(Course::WOOD);
    QCOMPARE(modified_resources, 50);

    GEhandler.modifyResource(player, Course::ORE, 50);
    modified_resources = GEhandler.getResource(Course::ORE);
    QCOMPARE(modified_resources, 50);

    QCOMPARE(GEhandler.modifyResource(player, Course::FOOD, -51), false);
    modified_resources = GEhandler.getResource(Course::FOOD);
    QCOMPARE(modified_resources, 50);

    QCOMPARE(GEhandler.modifyResource(player, Course::FOOD, -50), true);
    modified_resources = GEhandler.getResource(Course::FOOD);
    QCOMPARE(modified_resources, 0);



}

void GameEventHandlerTests::testModifyResources()
{
    Student::GameEventHandler GEhandler;
    std::shared_ptr<Course::PlayerBase> player = std::make_shared<Course::PlayerBase>("player");
    GEhandler.modifyResources(player,test_pos);

    int modified_resources = GEhandler.getResource(Course::FOOD);
    QCOMPARE(modified_resources, 50);

    modified_resources = GEhandler.getResource(Course::STONE);
    QCOMPARE(modified_resources, 50);

    modified_resources = GEhandler.getResource(Course::MONEY);
    QCOMPARE(modified_resources, 50);

    modified_resources = GEhandler.getResource(Course::WOOD);
    QCOMPARE(modified_resources, 50);

    modified_resources = GEhandler.getResource(Course::ORE);
    QCOMPARE(modified_resources, 50);

    QCOMPARE(GEhandler.modifyResources(player, test_neg), false);

    modified_resources = GEhandler.getResource(Course::FOOD);
    QCOMPARE(modified_resources, 50);

    modified_resources = GEhandler.getResource(Course::STONE);
    QCOMPARE(modified_resources, 50);

    modified_resources = GEhandler.getResource(Course::MONEY);
    QCOMPARE(modified_resources, 50);

    modified_resources = GEhandler.getResource(Course::WOOD);
    QCOMPARE(modified_resources, 50);

    modified_resources = GEhandler.getResource(Course::ORE);
    QCOMPARE(modified_resources, 50);

    QCOMPARE(GEhandler.modifyResources(player, test_neg_small), true);

    modified_resources = GEhandler.getResource(Course::FOOD);
    QCOMPARE(modified_resources, 25);

    modified_resources = GEhandler.getResource(Course::STONE);
    QCOMPARE(modified_resources, 25);

    modified_resources = GEhandler.getResource(Course::MONEY);
    QCOMPARE(modified_resources, 25);

    modified_resources = GEhandler.getResource(Course::WOOD);
    QCOMPARE(modified_resources, 25);

    modified_resources = GEhandler.getResource(Course::ORE);
    QCOMPARE(modified_resources, 25);


}

QTEST_APPLESS_MAIN(GameEventHandlerTests)

#include "tst_gameeventhandlertests.moc"
