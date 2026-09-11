#include <QtTest/QtTest>
#include <QDebug>

#include <testsuite.h>

using namespace cm;

int main(int argc, char* argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    qDebug() << "Starting test suite...";
    qDebug() << "Accessing tests from " << &TestSuite::testList();
    qDebug() << TestSuite::testList().size() << " tests detected";

    int failedTestCount{0};

    for(TestSuite* i : TestSuite::testList()) {
        qDebug() << "Executing Test " << i->testName;
        QString filename{i->testName + ".xml"};
        int result = QTest::qExec(i,QStringList() << " " << "-o" << filename << "-junitxml");
        qDebug() << "Test Result " << result;
        if(result != 0) {
            failedTestCount++;
        }
    }
    qDebug() << "Test suite complete - " << QString::number(failedTestCount) << " failures detected.";
    return failedTestCount;
}
