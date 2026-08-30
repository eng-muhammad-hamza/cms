#ifndef NAVIGATIONCONTROLLER_H
#define NAVIGATIONCONTROLLER_H

#include <QObject>
#include <cm-lib_global.h>
#include <models/client.h>
#include <controllers/INavigationController.h>

namespace cm {
namespace controllers {

class CMLIB_EXPORT NavigationController : public INavigationController {
    Q_OBJECT
public:
    explicit NavigationController(QObject* _parent = nullptr) : INavigationController(_parent) {}
};
}
}

#endif // NAVIGATIONCONTROLLER_H
