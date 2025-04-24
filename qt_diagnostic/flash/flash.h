#ifndef FLASH_H
#define FLASH_H

#include <QObject>
#include <QMetaEnum>
#include <QCoreApplication>
#include "diagTP/diagio.h"
#include "json/include/cJSON.h"
#include "json/include/diagnosticConfig.h"
#include "json/include/parseJson.h"
#include "diagTP/vectorCan.h"
#include "hex/intelHex.h"
#include "Node/node.h"

#define RSA_KEY_BITS 2048
#define HASH_LEN SHA256_DIGEST_LENGTH
#define SALT_LEN 32

class flash : public QObject
{
    Q_OBJECT
public:

    enum sequencelist{
        phyRequest,
        funRequest,
        seeds,
        keys,
        EraseFlash,
        downloadRequest,
        download,
        checkCRC,
        waitTime,
        verifyCertificateBidirectional,
        ProofOfOwnership,
        downloadRequestHex,
        downloadHex,
        next,
        writeDate,
        readVersionASCII,
        sendMsgData
    };
    Q_ENUM(sequencelist)

    explicit flash(struct DiagnosticSeqence dataflow,QObject *parent = nullptr);

    void setFlashSeq(struct DiagnosticSeqence dataflow);

    sequencelist stringToSeq(const QString &seq);

    void testquenceList(LinkedList *pat);

    QString uint8ArrayToHexString(const uint8_t* array, int length);

    void initCANTP();

    uint32_t crc32_Caculate(uint8_t* ReqBuffer,uint16_t ReqBufferLen,uint32_t* crcValue);

    void praseHexFile();

    uint8_t int_to_bcd_bytes(int num);

signals:

    void emitString(QString str);

    void emitStop();

    void emitDataSize(int size);

private:
    struct DiagnosticSeqence mDataflow;

    uint32_t initialCRC32Value;

//    X509Cert *x509;

    unsigned char encoded[256]={0};

    unsigned int hash_len;

//    const EVP_MD *md;
};

#endif // FLASH_H
