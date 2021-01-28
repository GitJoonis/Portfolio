#include <QtTest>

// add necessary includes here

class ObjectManagerTest : public QObject
{
    Q_OBJECT

public:
    ObjectManagerTest();
    ~ObjectManagerTest();

private slots:
    void test_case1();

};

ObjectManagerTest::ObjectManagerTest()
{

}

ObjectManagerTest::~ObjectManagerTest()
{

}

void ObjectManagerTest::test_case1()
{

}

QTEST_APPLESS_MAIN(ObjectManagerTest)

#include "tst_objectmanagertest.moc"
