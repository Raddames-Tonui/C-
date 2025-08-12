#include <drogon/drogon.h>
#include <json/json.h> // Drogon uses Json::Value

int main() {
    drogon::app()
        .addListener("0.0.0.0", 9090)
        .registerHandler("/",
            [](const drogon::HttpRequestPtr&,
               std::function<void(const drogon::HttpResponsePtr&)>&& callback) {
                // Create JSON object
                Json::Value json;
                json["message"] = "Hello World this is Raddames";

                // Create response
                auto resp = drogon::HttpResponse::newHttpJsonResponse(json);
                callback(resp);
            })
        .run();

    return 0;
}
