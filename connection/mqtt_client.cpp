#include "mqtt_client.h"
#include <fstream>

MqttClient::MqttClient(std::string_view client_id, bool clean_session) : logging_(false) {
    mosquitto_lib_init();
    mosq_ = mosquitto_new(client_id.data(), clean_session, this);

    mosquitto_connect_callback_set(mosq_, OnConnect);
    mosquitto_disconnect_callback_set(mosq_, OnDisconnect);
    mosquitto_publish_callback_set(mosq_, OnPublish);
    mosquitto_log_callback_set(mosq_, OnLogging);
    mosquitto_message_callback_set(mosq_, OnMessage);
}

MqttClient::~MqttClient() {
    mosquitto_destroy(mosq_);
    mosquitto_lib_cleanup();
}

bool MqttClient::LoadFile(std::string_view path, std::string &file) {
    std::ifstream ifs(path.data());
    if (!ifs) {
        return false;
    }
    std::string content((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
    file = content;
    return true;
}

std::string MqttClient::GetEndpoint() const { return host_ + ":" + std::to_string(port_); }

int MqttClient::Connect(std::string_view host, int port, int keep_alive) {
    host_ = host;
    port_ = port;
    mosquitto_loop_start(mosq_);
    return mosquitto_connect_async(mosq_, host.data(), port, keep_alive);
}

void MqttClient::Disconnect() { mosquitto_disconnect(mosq_); }

bool MqttClient::IsConnected() const { return connected_; }

int MqttClient::Publish(int *mid, std::string_view topic, std::string_view payload, int qos) {
    if (!connected_) {
        return MOSQ_ERR_NO_CONN;
    }

    return mosquitto_publish(mosq_, mid, topic.data(), payload.size(), payload.data(), qos, false);
}

int MqttClient::Subscribe(int *mid, std::string_view topic, int qos) {
    if (!connected_) {
        return MOSQ_ERR_NO_CONN;
    }

    return mosquitto_subscribe(mosq_, mid, topic.data(), qos);
}

int MqttClient::Unsubscribe(int *mid, std::string_view topic) {
    if (!connected_) {
        return MOSQ_ERR_NO_CONN;
    }

    return mosquitto_unsubscribe(mosq_, mid, topic.data());
}

int MqttClient::SetUsernamePassword(std::string_view username, std::string_view password) {
    return mosquitto_username_pw_set(mosq_, username.data(), password.data());
}

int MqttClient::SetWill(std::string_view topic, std::string_view payload, int qos, bool retain) {
    return mosquitto_will_set(mosq_, topic.data(), payload.size(), payload.data(), qos, retain);
}


int MqttClient::SetTLS(std::string_view cert_file, std::string_view key_file, std::string_view ca_file) {
    std::string cert_file_str;
    std::string key_file_str;
    std::string ca_file_str;
    if (!LoadFile(cert_file, cert_file_str)) {
        return MOSQ_ERR_INVAL;
    }
    if (!LoadFile(key_file, key_file_str)) {
        return MOSQ_ERR_INVAL;
    }
    if (!LoadFile(ca_file, ca_file_str)) {
        return MOSQ_ERR_INVAL;
    }
    return mosquitto_tls_set(mosq_, ca_file_str.data(), nullptr, cert_file_str.data(), key_file_str.data(), nullptr);
}

void MqttClient::SetMessageCallback(MessageCallback &&fn) { message_fn_ = fn; }

void MqttClient::SetConnectCallback(ConnectCallback &&fn) { connect_fn_ = fn; }

void MqttClient::SetDisconnectCallback(DisconnectCallback &&fn) { disconnect_fn_ = fn; }

void MqttClient::SetPublishCallback(PublishCallback &&fn) { publish_fn_ = fn; }

void MqttClient::OnConnect(struct mosquitto *mosq, void *obj, int rc) {
    auto self        = static_cast<MqttClient *>(obj);
    self->connected_ = true;

    if (self->connect_fn_) {
        self->connect_fn_(rc);
    }
}

void MqttClient::OnDisconnect(struct mosquitto *mosq, void *obj, int rc) {
    auto self        = static_cast<MqttClient *>(obj);
    self->connected_ = false;

    if (self->disconnect_fn_) {
        self->disconnect_fn_(rc);
    }
}

void MqttClient::OnMessage(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message) {
    auto self = static_cast<MqttClient *>(obj);
    if (self->message_fn_) {
        auto topic   = std::string_view(message->topic);
        auto payload = std::string_view(static_cast<const char *>(message->payload), message->payloadlen);
        self->message_fn_(topic, payload);
    }
}

void MqttClient::OnPublish(struct mosquitto *mosq, void *obj, int mid) {
    auto self = static_cast<MqttClient *>(obj);
    if (self->publish_fn_) {
        self->publish_fn_(mid);
    }
}

void MqttClient::OnLogging(struct mosquitto *mosq, void *obj, int level, const char *str) {
    auto self = static_cast<MqttClient *>(obj);
    if (self->logging_) {
        printf("mosquitto[%s] %d %s\n", self->GetEndpoint().c_str(), level, str);
    }
}
