#ifndef HTTPSCLIENT_H
#define HTTPSCLIENT_H

#include <QObject>
#include "curl/curl.h"
#include "json/include/cJSON.h"

class HttpsClient : public QObject
{
    Q_OBJECT
public:
    explicit HttpsClient(QObject *parent = nullptr);

    void destroyCURL();

    uint8_t postMethod(std::string vin,std::string vehicle_model,
                       std::string hw_device_sn,std::string ble_mac_address,
                       std::string public_key,std::string dk_security_unit_id,
                       std::string hw_device_provider_no);
signals:

private:
    CURL* m_curl;
};

#endif // HTTPSCLIENT_H
