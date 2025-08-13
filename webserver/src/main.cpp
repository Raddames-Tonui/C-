#include <json/json.h>
#include <drogon/drogon.h>
#include <libpq-fe.h>   // PostgreSQL C client library (libpq)

int main() {
    drogon::app().loadConfigFile("../config.json");

    drogon::app().registerHandler("/",
     [](const drogon::HttpRequestPtr&,
        std::function<void(const drogon::HttpResponsePtr&)>&& callback) {

         Json::Value json;
         json["message"] = "Welcome to Drogon";

         auto resp = drogon::HttpResponse::newHttpJsonResponse(json);
         callback(resp);
     });

    //   /pupils route
    drogon::app().registerHandler("/pupils",
        [](const drogon::HttpRequestPtr&,
           std::function<void(const drogon::HttpResponsePtr&)>&& callback) {

            // Connect to PostgreSQL
            const char *conninfo = "host=127.0.0.1 port=5432 dbname=online_exams user=admin password=admin";
            PGconn *conn = PQconnectdb(conninfo);

            if (PQstatus(conn) != CONNECTION_OK) {
                Json::Value json;
                json["error"] = PQerrorMessage(conn);
                PQfinish(conn);
                auto resp = drogon::HttpResponse::newHttpJsonResponse(json);
                callback(resp);
                return;
            }

            const char *sql =
                "SELECT concat(p.pupil_firstname, p.pupil_lastname), c.class_name "
                "FROM pupils p "
                "INNER JOIN classes c ON p.class_id = c.class_id "
                "ORDER BY pupil_firstname DESC;";

            PGresult *res = PQexec(conn, sql);

            if (PQresultStatus(res) != PGRES_TUPLES_OK) {
                Json::Value json;
                json["error"] = PQresultErrorMessage(res);
                PQclear(res);
                PQfinish(conn);
                auto resp = drogon::HttpResponse::newHttpJsonResponse(json);
                callback(resp);
                return;
            }

            Json::Value json;
            Json::Value pupils(Json::arrayValue);

            int nRows = PQntuples(res);
            for (int i = 0; i < nRows; ++i) {
                Json::Value pupil;
                pupil["firstname"] = PQgetvalue(res, i, 0);
                pupil["lastname"] = PQgetvalue(res, i, 1);
                pupil["class"] = PQgetvalue(res, i, 2);
                pupils.append(pupil);
            }
            json["pupils"] = pupils;

            PQclear(res);
            PQfinish(conn);

            auto resp = drogon::HttpResponse::newHttpJsonResponse(json);
            callback(resp);
        });

    drogon::app().run();
    return 0;
}
