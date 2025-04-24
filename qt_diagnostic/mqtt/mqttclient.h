#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H

#include <QObject>
#include "mosquitto.h"
#define HOST "10.10.181.147"
#define PORT  1883
#define KEEP_ALIVE 60
#define MSG_MAX_SIZE  512


class mqttClient : public QObject
{
    Q_OBJECT
public:
    explicit mqttClient(QObject *parent = nullptr);

    bool connectMqtt();

    bool sendMqttMsg(QString topic,QString msgdata);

    void disconnectMqtt();

    static void mqtt_message_callback(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message);

    static void mqtt_connect_callback(struct mosquitto *mosq, void *userdata, int result);

signals:
    void emitMqttMsgIn(QString);

    void emitMqttMsg(QString);

private:
    bool session = true;

    struct mosquitto *mosq;

    static mqttClient *mqtt;
};

#endif // MQTTCLIENT_H
