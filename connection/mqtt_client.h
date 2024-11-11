#pragma once

#include <functional>
#include <mosquitto.h>
#include <string>
#include <string_view>


class MqttClient
{
public:
    using ConnectCallback    = std::function<void(int rc)>;
    using DisconnectCallback = std::function<void(int rc)>;
    using MessageCallback    = std::function<void(std::string_view topic, std::string_view payload)>;
    using PublishCallback    = std::function<void(int mid)>;

    static constexpr int kQos0 = 0;  /* 最多一次 */
    static constexpr int kQos1 = 1;  /* 至少一次 */
    static constexpr int kQos2 = 2;  /* 恰好一次 */

    explicit MqttClient(std::string_view client_id, bool clean_session = true);
    ~MqttClient();

    MqttClient(const MqttClient&) = delete;
    MqttClient& operator=(const MqttClient&) = delete;
    MqttClient(MqttClient&&) noexcept;
    MqttClient& operator=(MqttClient&&) noexcept;

    int  Connect(std::string_view host, int port = 1883, int keep_alive = 60);
    void Disconnect();
    bool IsConnected() const;
    int  Publish(int *mid, std::string_view topic, std::string_view payload, int qos = kQos0);
    int  Subscribe(int *mid, std::string_view topic, int qos = kQos0);
    int  Unsubscribe(int *mid, std::string_view topic);
    int  SetUsernamePassword(std::string_view username, std::string_view password);
    int  SetWill(std::string_view topic, std::string_view payload, int qos = kQos0, bool retain = false);
    int  SetTLS(std::string_view cert_file, std::string_view key_file, std::string_view ca_file);
    void SetMessageCallback(MessageCallback &&fn);
    void SetConnectCallback(ConnectCallback &&fn);
    void SetDisconnectCallback(DisconnectCallback &&fn);
    void SetPublishCallback(PublishCallback &&fn);
    void SetLogging(bool enable);

    std::string GetEndpoint() const;


private:
    std::string       host_;
    int               port_;
    struct mosquitto *mosq_;
    bool              connected_;
    ConnectCallback   connect_fn_;
    DisconnectCallback disconnect_fn_;
    MessageCallback   message_fn_;
    PublishCallback   publish_fn_;
    bool              logging_;


    bool LoadFile(std::string_view path,std::string &file);
    static void OnConnect(struct mosquitto *mosq, void *obj, int rc);
    static void OnDisconnect(struct mosquitto *mosq, void *obj, int rc);
    static void OnMessage(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message);
    static void OnPublish(struct mosquitto *mosq, void *obj, int mid);
    static void OnLogging(struct mosquitto *mosq, void *obj, int level, const char *str);
};

