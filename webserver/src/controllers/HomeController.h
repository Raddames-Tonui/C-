#ifndef HOMECONTROLLER_H
#define HOMECONTROLLER_H

#include <drogon/HttpController.h>

class HomeController : public drogon::HttpController<HomeController> {
public:
    METHOD_LIST_BEGIN
    METHOD_ADD(HomeController::index, "/", Get);
    METHOD_LIST_END

    void index(const drogon::HttpRequestPtr &req,
               std::function<void(const drogon::HttpResponsePtr &)> &&callback);
};
#endif // HOMECONTROLLER_H
