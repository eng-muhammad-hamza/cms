#include "testsuite.h"

#include <QDebug>

namespace cm {

TestSuite::TestSuite(const QString &_testName)
    : QObject(), testName(_testName)
{
    qDebug() << "Creating Test" << testName;
    testList().push_back(this);
    qDebug() << testList().size() << " test recorded";
}

TestSuite::~TestSuite() {
    qDebug() << "Destroying Test";
}

std::vector<TestSuite*>& TestSuite::testList()
{
    static std::vector<TestSuite*> instance;
    return instance;
}

}
