#ifndef MASTERCONTROLLERTESTS_H
#define MASTERCONTROLLERTESTS_H

#include <QtTest>

#include <controllers/mastercontroller.h>
#include <testsuite.h>

namespace cm{
namespace controllers{
class MasterControllerTests : public TestSuite
{
    Q_OBJECT
public:
    MasterControllerTests();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    void welcomeMessage_returnsCorrectMessage();

private:
    MasterController masterController;
};
}
}
#endif // MASTERCONTROLLERTESTS_H
