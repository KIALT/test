#include "taos_client.h"

TAOSClient::TAOSClient(const TAOSOption &option) : option_(option), taos_(nullptr) { taos_init(); }

TAOSClient::~TAOSClient() {
    if (connected_) {
        Close();
    }
    taos_cleanup();
}

bool TAOSClient::Connect() {
    taos_ = taos_connect(option_.host.c_str(), option_.user.c_str(), option_.password.c_str(), nullptr, option_.port);
    connected_ = taos_ != nullptr;
    return connected_;
}

bool TAOSClient::IsConnected() const { return connected_; }

void TAOSClient::Close() {
    taos_close(taos_);
    connected_ = false;
}

TAOSResult TAOSClient::Query(std::string_view sql) { return TAOSResult(taos_query(taos_, sql.data())); }

void TAOSClient::Execute(std::string_view sql) {
    TAOS_RES *res = taos_query(taos_, sql.data());
    taos_free_result(res);
}

int TAOSClient::SelectDB(std::string_view db) { return taos_select_db(taos_, db.data()); }

TAOSResult TAOSClient::Insert(std::string_view tb, std::string_view cols, std::string_view values) {
    char sql[BUFSIZ];
    snprintf(sql, sizeof(sql), "insert into %s (%s) values (%s)", tb.data(), cols.data(), values.data());
    return TAOSResult(taos_query(taos_, sql));
}

TAOSResult TAOSClient::Update(std::string_view tb, std::string_view cols, std::string_view values) {
    char sql[BUFSIZ];
    snprintf(sql, sizeof(sql), "update %s set %s = %s", tb.data(), cols.data(), values.data());
    return TAOSResult(taos_query(taos_, sql));
}

TAOSResult TAOSClient::Delete(std::string_view tb, std::string_view cols, std::string_view values) {
    char sql[BUFSIZ];
    snprintf(sql, sizeof(sql), "delete from %s where %s = %s", tb.data(), cols.data(), values.data());
    return TAOSResult(taos_query(taos_, sql));
}

TAOSResult TAOSClient::Select(std::string_view tb, std::string_view cols, std::string_view values) {
    char sql[BUFSIZ];
    snprintf(sql, sizeof(sql), "select %s from %s where %s = %s", cols.data(), tb.data(), cols.data(), values.data());
    return TAOSResult(taos_query(taos_, sql));
}