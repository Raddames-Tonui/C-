#include <drogon/drogon.h>
#include <json/json.h>

int main() {
    drogon::app().loadConfigFile("../config.json");

    drogon::app().registerHandler("/",
        [](const drogon::HttpRequestPtr&,
           std::function<void(const drogon::HttpResponsePtr&)>&& callback) {
            Json::Value json;
            json["message"] = "Hello World this is Raddames";

            auto resp = drogon::HttpResponse::newHttpJsonResponse(json);
            callback(resp);
        });

    // Run app
    drogon::app().run();

    return 0;
}
