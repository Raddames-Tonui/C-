#include <drogon/drogon.h>
#include <json/json.h>
#include <drogon/orm/Exception.h> // DrogonDbException

using namespace drogon;
using namespace drogon::orm;

int main() {
    // Load settings from config.json (DB & server config)
    app().loadConfigFile("config.json");

    // Route: Hello World in JSON
    app().registerHandler("/",
        [](const HttpRequestPtr&,
           std::function<void(const HttpResponsePtr&)>&& callback) {
            Json::Value json;
            json["message"] = "Hello World this is Raddames";
            auto resp = HttpResponse::newHttpJsonResponse(json);
            callback(resp);
        });

    // Route: Test database connection
    app().registerHandler("/dbtest",
        [](const HttpRequestPtr&,
           std::function<void(const HttpResponsePtr&)>&& callback) {
            auto client = app().getDbClient("postgresql");
            client->execSqlAsync(
                "SELECT NOW();",
                [callback](const Result &r) {
                    Json::Value json;
                    json["status"] = "success";
                    json["db_time"] = r[0]["now"].as<std::string>();
                    auto resp = HttpResponse::newHttpJsonResponse(json);
                    callback(resp);
                },
                [callback](const DrogonDbException &e) {
                    Json::Value json;
                    json["status"] = "error";
                    json["message"] = e.base().what();
                    auto resp = HttpResponse::newHttpJsonResponse(json);
                    resp->setStatusCode(k500InternalServerError);
                    callback(resp);
                }
            );
        });

    // Start Drogon server
    app().run();
}
