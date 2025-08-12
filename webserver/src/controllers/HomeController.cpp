#include "HomeController.h"
#include <drogon/drogon.h>

void HomeController::index(const drogon::HttpRequestPtr &req,
                           std::function<void(const drogon::HttpResponsePtr &)> &&callback) {
    auto resp = drogon::HttpResponse::newHttpResponse();
    resp->setBody("C++ Home");
    resp->setContentTypeCode(drogon::CT_TEXT_HTML);
    callback(resp);
}
