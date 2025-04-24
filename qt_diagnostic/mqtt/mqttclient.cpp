#include "mqttclient.h"

mqttClient *mqttClient::mqtt = NULL;
mqttClient::mqttClient(QObject *parent) : QObject(parent)
{
    int err = 0;
    printf("mqtt publish init...\n");
    mosq = NULL;
    char buff[MSG_MAX_SIZE];

    //libmosquitto 库初始化
    err = mosquitto_lib_init();
    if (err < 0){
        printf("mosquitto lib int fail...");
    }

    //创建mosquitto客户端
    mosq = mosquitto_new(NULL,session,NULL);
    if (mosq == NULL){
        printf("create client failed...\n");
        err = -1;
        mosquitto_lib_cleanup();
    }

     mosquitto_message_callback_set(mosq, mqtt_message_callback);
     mosquitto_connect_callback_set(mosq, mqtt_connect_callback);

     mqtt = this;
     connect(this,&mqttClient::emitMqttMsgIn,this,[=](QString msg)
     {
         emit emitMqttMsg(msg);
     });
}

void mqttClient::mqtt_connect_callback(struct mosquitto *mosq, void *userdata, int result)
{
    int ret;
    if (!result){
        ret = mosquitto_subscribe(mosq, NULL, "versionInfoResp", 0);
        if(ret < 0){
            printf("Subscription failed\n");
        }else{
            printf("Subscription succeeded\n");
        }
    }else{
        printf("connect failed\n");
    }
}

void mqttClient::mqtt_message_callback(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message)
{
    if (message->payloadlen){
        emit mqtt->emitMqttMsgIn(QString("Topic:%1\nMessage:%2").arg(message->topic).arg((char *)message->payload));
        printf("%s %s \n", message->topic, (char *)message->payload);
    }else{
        printf("%s (null)\n",message->topic);
    }
}

bool mqttClient::connectMqtt()
{
    int err = 0;
    err = mosquitto_connect_async(mosq, HOST, PORT, KEEP_ALIVE);
    if (err < 0){
        printf("connect fail");
        mosquitto_destroy(mosq);
        return false;
    }

    //不阻塞，库函数中将自动创建线程实现
    err = mosquitto_loop_start(mosq);
    if(err != MOSQ_ERR_SUCCESS){
        printf("mosquitto loop error\n");
        mosquitto_disconnect(mosq);
        return false;
    }
    return true;
}

bool mqttClient::sendMqttMsg(QString topic,QString msgdata)
{
    int err = 0;
    err = mosquitto_publish(mosq,NULL,topic.toStdString().c_str(),msgdata.length(),msgdata.toStdString().c_str(),0,0);
    if(err != MOSQ_ERR_SUCCESS){
        printf("mosquitto sennd error\n");
    }
}

void mqttClient::disconnectMqtt()
{
    mosquitto_disconnect(mosq);
    mosquitto_loop_stop(mosq, true);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
}




