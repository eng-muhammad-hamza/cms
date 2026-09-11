#include "mastercontrollertests.h"

namespace cm {
namespace controllers {

static MasterControllerTests instance;

MasterControllerTests::MasterControllerTests() : TestSuite("MasterControllerTests") {}

void MasterControllerTests::initTestCase() {}

void MasterControllerTests::init() {}

void MasterControllerTests::cleanup() {}

void MasterControllerTests::cleanupTestCase() {}

void MasterControllerTests::welcomeMessage_returnsCorrectMessage() {
    QCOMPARE(masterController.welcomeMessage(),QString("Hello Boy!"));
}

}
}

