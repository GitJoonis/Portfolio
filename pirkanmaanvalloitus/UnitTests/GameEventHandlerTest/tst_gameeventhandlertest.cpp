#include <QtTest>

#include "handlers/gameeventhandler.h"

class GameEventHandlerTest : public QObject
{
    Q_OBJECT

public:
    GameEventHandlerTest();
    ~GameEventHandlerTest();

private slots:
    void test_case1();

};

GameEventHandlerTest::GameEventHandlerTest()
{

}

GameEventHandlerTest::~GameEventHandlerTest()
{

}

void GameEventHandlerTest::test_case1()
{

}

QTEST_APPLESS_MAIN(GameEventHandlerTest)

#include "tst_gameeventhandlertest.moc"
