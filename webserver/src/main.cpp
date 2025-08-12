#include <drogon/drogon.h>

int main() {
    // Create Drogon HTTP app
    drogon::app()
        .addListener("0.0.0.0", 9090) // Bind to port 9090
        .registerHandler("/", // Route for root path
            [](const drogon::HttpRequestPtr&,
               std::function<void (const drogon::HttpResponsePtr&)>&& callback) {
                auto resp = drogon::HttpResponse::newHttpResponse();
                resp->setContentTypeCode(drogon::CT_TEXT_PLAIN);
                resp->setBody("Hello World this is Raddames");
                callback(resp);
            })
        .run(); // Start event loop

    return 0;
}
