#include "httpsclient.h"
#include <iostream>
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

HttpsClient::HttpsClient(QObject *parent) : QObject(parent)
{
    curl_global_init(CURL_GLOBAL_DEFAULT);
    m_curl = curl_easy_init();
}

uint8_t HttpsClient::postMethod(std::string vin,std::string vehicle_model,
                                std::string hw_device_sn,std::string ble_mac_address,
                                std::string public_key,std::string dk_security_unit_id,
                                std::string hw_device_provider_no)
{
    CURLcode res;
    std::string readBuffer;
    if(m_curl) {
        curl_easy_setopt(m_curl, CURLOPT_URL, "https://test.tsp.autox.tech/api/vehicle");

        curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYPEER, 1L);
        curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYHOST, 2L);

        cJSON *root = cJSON_CreateObject();

        cJSON_AddStringToObject(root, "vin", vin.c_str());
        cJSON_AddStringToObject(root, "vehicle_model", vehicle_model.c_str());
        cJSON_AddStringToObject(root, "hw_device_sn", hw_device_sn.c_str());
        cJSON_AddStringToObject(root, "ble_mac_address", ble_mac_address.c_str());
        cJSON_AddStringToObject(root, "public_key", public_key.c_str());
        cJSON_AddStringToObject(root, "dk_security_unit_id", dk_security_unit_id.c_str());
        cJSON_AddStringToObject(root, "hw_device_provider_no", hw_device_provider_no.c_str());

        char *jsonData = cJSON_Print(root);

        curl_easy_setopt(m_curl, CURLOPT_POSTFIELDS, jsonData);

        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &readBuffer);

        curl_easy_setopt(m_curl, CURLOPT_SSLCERT, "D:\\_07_temp\\untitled\\cert\\AutoX_Client.crt"); // 客户端证书文件路径
        curl_easy_setopt(m_curl, CURLOPT_SSLKEY, "D:\\_07_temp\\untitled\\cert\\AutoX_Client.key");
         // 设置CA证书
        curl_easy_setopt(m_curl, CURLOPT_CAINFO, "D:\\_07_temp\\untitled\\cert\\ca-certificates.crt");

        // Perform the request
        res = curl_easy_perform(m_curl);
        if(res != CURLE_OK)
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        else
            std::cout << "Response: " << readBuffer << std::endl;
        cJSON_Delete(root);
        free(jsonData);
    }

     return res;
}

void HttpsClient::destroyCURL()
{
    curl_easy_cleanup(m_curl);
    curl_global_cleanup();
}
