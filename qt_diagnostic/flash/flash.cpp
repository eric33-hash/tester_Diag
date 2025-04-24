#include "flash.h"
#include <QDateTime>
#include <unistd.h>
#include <QDebug>
#include <QFile>
//#include <QSslCertificate>

#define GETTIME_OUTPUT(payload,size,flag)   \
{                                      \
    QDateTime currentTime = QDateTime::currentDateTime();  \
    QString outPutTime = "[" + currentTime.toString("yyyy-MM-dd hh:mm:ss") + "] ";  \
    emit emitString(outPutTime + flag + uint8ArrayToHexString(payload,size)); \
}  \

flash::flash(struct DiagnosticSeqence dataflow,QObject *parent) : QObject(parent)
{
    mDataflow = dataflow;
    initialCRC32Value = 0xFFFFFFFF;
}

void flash::setFlashSeq(struct DiagnosticSeqence dataflow)
{
    mDataflow.sequence = cJSON_Duplicate(cJSON_GetObjectItem(dataflow.sequence,"sequences"),1);
}
//"verifyCertificateBidirectional;29 02 01;69 02",
flash::sequencelist flash::stringToSeq(const QString &seq)
{
     int enumIndex = flash::staticMetaObject.indexOfEnumerator("sequencelist");
     QMetaEnum metaEnum = flash::staticMetaObject.enumerator(enumIndex);
     return static_cast<sequencelist>(metaEnum.keyToValue(qPrintable(seq)));
}

QString flash::uint8ArrayToHexString(const uint8_t* array, int length) {
    QString hexStr;
    for (int i = 0; i < length; ++i) {
        hexStr += QString("%1 ").arg(array[i], 2, 16, QChar('0'));
    }
    return hexStr;
}

uint8_t flash::int_to_bcd_bytes(int num)
{
    unsigned char bcd = 0;
    int digit, position = 0;

    while (num > 0)
    {
        digit = num % 10;
        bcd |= digit << (position * 4);
        num /= 10;
        position++;
    }
    return bcd;
}

void flash::testquenceList(LinkedList *flashNode)
{
   // praseHexFile();

    QStringList pathList;
    int seqSize = cJSON_GetArraySize(mDataflow.sequence);
    struct sendMsg *reqMsg = (struct sendMsg *)malloc(sizeof(struct sendMsg));
    struct sendMsg *respMsg = (struct sendMsg*)malloc(sizeof(struct sendMsg));
    uint8_t type = mDataflow.deviceType;
    long fileSize = 0;
    char* fileSend = mDataflow.file;
    QString path;
    FILE* file;
    uint32_t memoryaddr = mDataflow.Flashaddr;
    uint32_t memorysize = 0;
    unsigned int blocksize = 0;
    uint8_t sendData[MAX_BUFF_LEN];
    uint8_t respData[MAX_BUFF_LEN];
    bool isContinue = BOOL_FALSE;
    uint8_t seed[4] = {0x00};
    uint8_t key[4] = {0x00};
    uint8_t ChallengeServer[MAX_BUFF_LEN] = {0};
    uint8_t certificateServer[MAX_BUFF_LEN] = {0};
    uint8_t proofOfOwnershipServer[MAX_BUFF_LEN] = {0};
    uint16_t lengthOfChallengeServer = 0;
    uint16_t lengthOfCertificateServer = 0;
    uint64_t lengthOfProofOfOwnershipServer = 0;
    unsigned char rsa2048[256]={0};
    QString seqCommand;
    uint8_t R1[32] = {0X00};
    int pathIdx = 0;
    int flashIdx = 0;
    QString filename_link;
    for(int i = 0;i < seqSize;i++)
    {
        char *seq = cJSON_GetArrayItem(mDataflow.sequence,i)->valuestring;
        seqCommand = QString::fromUtf8(seq).split(';').at(0);
        QString seqRequest = QString::fromUtf8(seq).split(';').at(1);
        QString seqResp;
        memset(sendData,0x00,MAX_BUFF_LEN);
        memset(respData,0x00,MAX_BUFF_LEN);
        if(QString::fromUtf8(seq).split(';').size() == 3)
        {
            seqResp = QString::fromUtf8(seq).split(';').at(2);
        }
        reqMsg->isFunction = 0;
        switch (stringToSeq(seqCommand))
        {
            case phyRequest:
            {
                reqMsg->size = QByteArray::fromHex(seqRequest.toLatin1()).length();
                memcpy(&reqMsg->payload[0],QByteArray::fromHex(seqRequest.toLatin1()).data(),reqMsg->size);

                GETTIME_OUTPUT(reqMsg->payload,reqMsg->size,"TX ");

                if(sendAndReceiveMessage(type,&link_iso,reqMsg,respMsg) == Res_OK)
                {
                    uint8_t compareSize = QByteArray::fromHex(seqResp.toLatin1()).length();
                    memcpy(respData,QByteArray::fromHex(seqResp.toLatin1()).data(),compareSize);

                    GETTIME_OUTPUT(respMsg->payload,respMsg->size,"RX ");
                    if((compareSize != 0) && (checkResultUDS(respData,compareSize,respMsg) != Res_OK))
                    {
                        isContinue = BOOL_TRUE;
                        break;
                    }

                }
                else
                {

                    isContinue = BOOL_TRUE;
                    break;
                }
            }
                break;
            case readVersionASCII:
            {
                reqMsg->size = QByteArray::fromHex(seqRequest.toLatin1()).length();
                memcpy(&reqMsg->payload[0],QByteArray::fromHex(seqRequest.toLatin1()).data(),reqMsg->size);

                GETTIME_OUTPUT(reqMsg->payload,reqMsg->size,"TX ");

                if(sendAndReceiveMessage(type,&link_iso,reqMsg,respMsg) == Res_OK)
                {
                    uint8_t compareSize = QByteArray::fromHex(seqResp.toLatin1()).length();
                    memcpy(respData,QByteArray::fromHex(seqResp.toLatin1()).data(),compareSize);

                    GETTIME_OUTPUT(respMsg->payload,respMsg->size,"RX ");
                    if(checkResultUDS(respData,compareSize,respMsg) != Res_OK)
                    {
                        isContinue = BOOL_TRUE;
                        break;
                    }
                    QString asciiString;
                    for (int i = compareSize; i < respMsg->size; ++i)
                    {
                           asciiString.append(QChar(respMsg->payload[i]));
                    }
                    emit emitString(asciiString);
                }
                else
                {

                    isContinue = BOOL_TRUE;
                    break;
                }
            }
                break;
            case funRequest:
            {
                reqMsg->size = QByteArray::fromHex(seqRequest.toLatin1()).length();
                memcpy(sendData,QByteArray::fromHex(seqRequest.toLatin1()).data(),reqMsg->size);
                reqMsg->isFunction = 1;
                memcpy(reqMsg->payload,sendData,reqMsg->size);
                QDateTime currentTime = QDateTime::currentDateTime();
                QString outPutTime = "[" + currentTime.toString("yyyy-MM-dd hh:mm:ss") + "] ";
                emit emitString(outPutTime + "TX " + uint8ArrayToHexString(sendData,reqMsg->size));
                if(sendFuntionalMessage(type,&link_iso,reqMsg) != Res_OK)
                {
                    isContinue = BOOL_TRUE;
                    break;
                }
            }
                break;
            case waitTime:
            {
                long sleepTime = seqRequest.toLong(nullptr,10);
                usleep(sleepTime*1000);
            }
                break;
            case seeds:
            {
                reqMsg->size = QByteArray::fromHex(seqRequest.toLatin1()).length();
                memcpy(sendData,QByteArray::fromHex(seqRequest.toLatin1()).data(),QByteArray::fromHex(seqRequest.toLatin1()).length());
                reqMsg->isFunction = 0;
                memcpy(reqMsg->payload,sendData,reqMsg->size);

                QDateTime currentTime = QDateTime::currentDateTime();
                QString outPutTime = "[" + currentTime.toString("yyyy-MM-dd hh:mm:ss") + "] ";
                emit emitString(outPutTime + "TX " + uint8ArrayToHexString(reqMsg->payload,reqMsg->size));
                if(sendAndReceiveMessage(type,&link_iso,reqMsg,respMsg) == Res_OK)
                {
                    uint8_t compareSize = QByteArray::fromHex(seqResp.toLatin1()).length();
                    memcpy(respData,QByteArray::fromHex(seqResp.toLatin1()).data(),compareSize);
                    emit emitString(outPutTime +"RX "+ uint8ArrayToHexString(respMsg->payload,respMsg->size));
                    if(checkResultUDS(respData,compareSize,respMsg) != Res_OK)
                    {
                        isContinue = BOOL_TRUE;
                        break;
                    }
                    else
                    {
                        memcpy(seed,&respMsg->payload[2],4);
                        SecurityAccessAlgorithm(reqMsg->payload[1],seed,key);
                    }
                }
                else
                {
                    isContinue = BOOL_TRUE;
                    break;
                }
            }
                break;
            case keys:
            {
                reqMsg->size = QByteArray::fromHex(seqRequest.toLatin1()).length() + 4;
                memcpy(sendData,QByteArray::fromHex(seqRequest.toLatin1()).data(),QByteArray::fromHex(seqRequest.toLatin1()).length());
                reqMsg->isFunction = 0;
                memcpy(reqMsg->payload,sendData,2);
                memcpy(&reqMsg->payload[2],&key[0],4);
                QDateTime currentTime = QDateTime::currentDateTime();
                QString outPutTime = "[" + currentTime.toString("yyyy-MM-dd hh:mm:ss") + "] ";
                emit emitString(outPutTime + "TX " + uint8ArrayToHexString(reqMsg->payload,reqMsg->size));
                if(sendAndReceiveMessage(type,&link_iso,reqMsg,respMsg) == Res_OK)
                {
                    uint8_t compareSize = QByteArray::fromHex(seqResp.toLatin1()).length();
                    memcpy(respData,QByteArray::fromHex(seqResp.toLatin1()).data(),compareSize);
                    emit emitString(outPutTime+ "RX " + uint8ArrayToHexString(respMsg->payload,respMsg->size));
                    if(checkResultUDS(respData,compareSize,respMsg) != Res_OK)
                    {
                        isContinue = BOOL_TRUE;
                        break;
                    }
                }
                else
                {
                    isContinue = BOOL_TRUE;
                    break;
                }
            }
                break;
            case EraseFlash:
            {
                uint32_t eraseAddr = 0;
                uint32_t eraseSize = 0;
                uint32_t eraseEnd = 0;
                eraseAddr = flashNode->head->mfileStart;
                eraseEnd = flashNode->head->mfileEnd;

                eraseSize = eraseEnd - eraseAddr + 1;
                uint8_t memoryAddr[4];
                uint8_t memorySize[4];
                memoryAddr[0] = (eraseAddr & 0xFF000000) >> 24;
                memoryAddr[1] = (eraseAddr & 0x00FF0000) >> 16;
                memoryAddr[2] = (eraseAddr & 0x0000FF00) >> 8;
                memoryAddr[3] = (eraseAddr & 0x000000FF);

                memorySize[0] = (eraseSize & 0xFF000000) >> 24;
                memorySize[1] = (eraseSize & 0x00FF0000) >> 16;
                memorySize[2] = (eraseSize & 0x0000FF00) >> 8;
                memorySize[3] = (eraseSize & 0x000000FF);

                reqMsg->size = QByteArray::fromHex(seqRequest.toLatin1()).length();
                memcpy(sendData,QByteArray::fromHex(seqRequest.toLatin1()).data(),reqMsg->size);

                memcpy(reqMsg->payload,sendData,reqMsg->size);
                memcpy(reqMsg->payload +5,memoryAddr,4);
                memcpy(reqMsg->payload +9,memorySize,4);
                reqMsg->size += 8;
                GETTIME_OUTPUT(reqMsg->payload,reqMsg->size,"TX ");
                if(sendAndReceiveMessage(type,&link_iso,reqMsg,respMsg) == Res_OK)
                {
                    uint8_t compareSize = QByteArray::fromHex(seqResp.toLatin1()).length();
                    memcpy(respData,QByteArray::fromHex(seqResp.toLatin1()).data(),compareSize);
                    GETTIME_OUTPUT(respMsg->payload,respMsg->size,"RX ");
                    if(checkResultUDS(respData,compareSize,respMsg) != Res_OK)
                    {
                        isContinue = BOOL_TRUE;
                        break;
                    }
                }
                else
                {
                    isContinue = BOOL_TRUE;
                    break;
                }
            }
                break;
            case downloadRequest:
            {
                uint8_t memoryAddr[4];
                uint8_t memorySize[4];
                path = pathList.at(pathIdx);
                file = fopen(path.toStdString().c_str(), "rb");
                        if (file == NULL) {
                            printf("File not found.");
                //            return;
                        }
                        else
                        {
                            fseek(file, 0, SEEK_END);
                            fileSize = ftell(file);
                            qDebug() <<"filesize" << fileSize;
                            fclose(file);
                        }
                memoryAddr[0] = (memoryaddr & 0xFF000000) >> 24;
                memoryAddr[1] = (memoryaddr & 0x00FF0000) >> 16;
                memoryAddr[2] = (memoryaddr & 0x0000FF00) >> 8;
                memoryAddr[3] = (memoryaddr & 0x000000FF);

                memorySize[0] = (fileSize & 0xFF000000) >> 24;
                memorySize[1] = (fileSize & 0x00FF0000) >> 16;
                memorySize[2] = (fileSize & 0x0000FF00) >> 8;
                memorySize[3] = (fileSize & 0x000000FF);

                reqMsg->size = QByteArray::fromHex(seqRequest.toLatin1()).length();
                memcpy(sendData,QByteArray::fromHex(seqRequest.toLatin1()).data(),reqMsg->size);
                reqMsg->isFunction = 0;
                memcpy(reqMsg->payload,sendData,reqMsg->size);
                memcpy(reqMsg->payload +3,memoryAddr,4);
                memcpy(reqMsg->payload +7,memorySize,4);
                reqMsg->size += 8;
                QDateTime currentTime = QDateTime::currentDateTime();
                QString outPutTime = "[" + currentTime.toString("yyyy-MM-dd hh:mm:ss") + "] ";
                emit emitString(outPutTime + "TX " + uint8ArrayToHexString(reqMsg->payload,reqMsg->size));

                if(sendAndReceiveMessage(type,&link_iso,reqMsg,respMsg) == Res_OK)
                {
                    uint8_t compareSize = QByteArray::fromHex(seqResp.toLatin1()).length();
                    memcpy(respData,QByteArray::fromHex(seqResp.toLatin1()).data(),compareSize);
                    emit emitString(outPutTime +"RX "+ uint8ArrayToHexString(respMsg->payload,respMsg->size));
                    if(checkResultUDS(respData,compareSize,respMsg) != Res_OK)
                    {
                        isContinue = BOOL_TRUE;
                        break;
                    }
                    else
                    {
                        if(respMsg->size == 6)
                        {
                            blocksize = ((respMsg->payload[2] << 24) |(respMsg->payload[3] << 16) | (respMsg->payload[4] << 8) | respMsg->payload[5]);
                        }
                        else if(respMsg->size == 4)
                        {
                            blocksize = ((respMsg->payload[2] << 8) |(respMsg->payload[3]));
                        }
                    }
                }
                else
                {
                    isContinue = BOOL_TRUE;
                    break;
                }

            }
                break;
            case download:
            {
                path = pathList.at(pathIdx);
                file = fopen(path.toStdString().c_str(),"rb");
                if(file == NULL)
                {
                    emit emitString(QString::fromLocal8Bit(fileSend)+ "is null");
                    qDebug() << errno << QString::fromLocal8Bit(fileSend);
                    isContinue = BOOL_TRUE;
                    break ;
                }

                uint8_t readData[MAX_BUFF_LEN];
                int BlockCount = 0x01;
                readData[0] = 0x36;

                struct sendMsg *rxmsg;
                rxmsg = (struct sendMsg*)malloc(sizeof(struct sendMsg));
                size_t ret;
                uint32_t sendblock = blocksize -2;
                do
                {
                    readData[1] = BlockCount;
                    ret = fread(&readData[2],sizeof(uint8_t),sendblock,file);
                    struct sendMsg downloadData;
                    downloadData.isFunction=0;
                    downloadData.size = ret + 2;
                    if(ret == 0)
                    {
                        fclose(file);
                        break;
                    }
                    memcpy(downloadData.payload,readData,downloadData.size);


                    crc32_Caculate(&downloadData.payload[2],downloadData.size -2,&initialCRC32Value);
                    QDateTime currentTime = QDateTime::currentDateTime();
                    QString outPutTime = "[" + currentTime.toString("yyyy-MM-dd hh:mm:ss") + "] ";
                    emit emitString(outPutTime +"TX "+ uint8ArrayToHexString(downloadData.payload,10));
                    if(sendAndReceiveMessage(type,&link_iso,&downloadData,rxmsg) != Res_OK)
                    {
                        isContinue = BOOL_TRUE;
                        break;
                    }

                    currentTime = QDateTime::currentDateTime();
                    outPutTime = "[" + currentTime.toString("yyyy-MM-dd hh:mm:ss") + "] ";
                    emit emitString(outPutTime +"RX " + uint8ArrayToHexString(rxmsg->payload,rxmsg->size));
                    uint8_t downloadResp[2];
                    downloadResp[0] = 0x76;
                    downloadResp[1] = BlockCount;

                    if(checkResultUDS(downloadResp,2,rxmsg) != Res_OK)
                    {
                        isContinue = BOOL_TRUE;
                        break;
                    }

                    BlockCount++;
                    if(BlockCount > 0xFF)
                        BlockCount = 0x00;
                    if (ret < sendblock)
                    {
                        for(int i = 0;i< ret+2;i++)
                        {
                            qDebug("%02x ",downloadData.payload[i]);
                        }
                        break;
                    }
                } while (1);

            fclose(file);

            }
                break;
            case checkCRC:
            {
                uint8_t verifyintegrity[8] = {0x31,0x01,0x02,0x02};
                initialCRC32Value = (unsigned int)~initialCRC32Value;
                verifyintegrity[4] = (initialCRC32Value & 0xFF000000) >> 24;
                verifyintegrity[5] = (initialCRC32Value & 0x00FF0000) >> 16;
                verifyintegrity[6] = (initialCRC32Value & 0x0000FF00) >> 8;
                verifyintegrity[7] = (initialCRC32Value & 0x000000FF);

                struct sendMsg verifyintegrityRequest;
                verifyintegrityRequest.isFunction=0;
                verifyintegrityRequest.size = 8;

                memcpy(verifyintegrityRequest.payload ,verifyintegrity,verifyintegrityRequest.size);

                struct sendMsg *rxmsg;
                rxmsg = (struct sendMsg*)malloc(sizeof(struct sendMsg));

                GETTIME_OUTPUT(verifyintegrityRequest.payload,verifyintegrityRequest.size,"TX ");
               if(sendAndReceiveMessage(type,&link_iso,&verifyintegrityRequest,rxmsg) == Res_OK)
                {
                    verifyintegrity[0] += 0x40;

                    if(checkResultUDS(verifyintegrity,4,rxmsg) == Res_OK && rxmsg->payload[4] == 0x00)
                    {

                    }
                    else
                    {
                        isContinue = BOOL_TRUE;
                    }
                }

               GETTIME_OUTPUT(rxmsg->payload,rxmsg->size,"RX ");
               initialCRC32Value = 0xFFFFFFFF;
               pathIdx++;
            }
                break;
/***
//            case verifyCertificateBidirectional:
//            {
//                uint16_t certSize = 0;

//                uint8_t cer[4096] = {0x00};
//                reqMsg->size = QByteArray::fromHex(seqRequest.toLatin1()).length();
//                memcpy(sendData,QByteArray::fromHex(seqRequest.toLatin1()).data(),reqMsg->size);
//                reqMsg->isFunction = 0;
//                memcpy(reqMsg->payload,sendData,reqMsg->size);
//                x509 = new X509Cert();
//                certSize = x509->pem_to_cer(cer);
//                reqMsg->payload[3] = (certSize & 0xFF00) >> 8;
//                reqMsg->payload[4] = (certSize & 0xFF);
//                reqMsg->size += 2;
//                memcpy(&reqMsg->payload[reqMsg->size],cer,certSize);
//                reqMsg->size += certSize;
//                reqMsg->payload[reqMsg->size] = (SHA256_DIGEST_LENGTH & 0xFF00) >> 8;;
//                reqMsg->payload[reqMsg->size + 1] = (SHA256_DIGEST_LENGTH & 0xFF);;
//                reqMsg->size += 2;
//                QDateTime currentTime = QDateTime::currentDateTime();
//                x509->generateDRBG(currentTime.toString(),R1);
//                memcpy(&reqMsg->payload[reqMsg->size],R1,SHA256_DIGEST_LENGTH);

//                reqMsg->size += SHA256_DIGEST_LENGTH;
//                QString outPutTime = "[" + currentTime.toString("yyyy-MM-dd hh:mm:ss") + "] ";
//                emit emitString(outPutTime + uint8ArrayToHexString(reqMsg->payload,10) + "......");


//                respMsg->size = 0;
//                QString pem_file = "D:\\_02_project\\2.txt";
//                QFile file(pem_file);
//                    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
//                        qDebug() << "Unable to open file";
//                    }

//                    QTextStream in(&file);
//                    QString line;
//                    uint8_t ss[4096];
//                    int indx = 0;
//                    while (!in.atEnd()) {
//                        line = in.readLine();
//                        for (int i = 0; i < line.length(); i += 2)
//                        {
//                            QString byteString = line.mid(i, 2);
//                            respMsg->payload[respMsg->size] = byteString.toUInt(nullptr,16);
//                            respMsg->size++;
//                        }
//                    }

//                    file.close();

//                lengthOfChallengeServer = (((uint16_t)respMsg->payload[3] << 8) | respMsg->payload[4]);
//                memcpy(ChallengeServer,&respMsg->payload[5],lengthOfChallengeServer);
//                lengthOfCertificateServer = (((uint16_t)respMsg->payload[5 + lengthOfChallengeServer] << 8)| respMsg->payload[5 + lengthOfChallengeServer +1]);
//                memcpy(certificateServer,&respMsg->payload[5 + lengthOfChallengeServer +2],lengthOfCertificateServer);
//                lengthOfProofOfOwnershipServer =  (((uint16_t)respMsg->payload[5 + lengthOfChallengeServer +2 + lengthOfCertificateServer] << 8)| respMsg->payload[8 + lengthOfChallengeServer + lengthOfCertificateServer]);
//                memcpy(proofOfOwnershipServer,&respMsg->payload[8 + lengthOfChallengeServer + lengthOfCertificateServer + 1],lengthOfProofOfOwnershipServer);
//                if(x509->X509_verify_AutoX(const_cast<const unsigned char*>(certificateServer),lengthOfCertificateServer) == false)
//                {
//                    emit emitString("服务端证书验证失败------");
//                    isContinue = BOOL_TRUE;
//                    break;
//                }
//                uint8_t *data = (uint8_t *)malloc(sizeof (uint8_t) * 4096);
//                memcpy(data,ChallengeServer,lengthOfChallengeServer);
//                memcpy(data + lengthOfChallengeServer,certificateServer,lengthOfCertificateServer);
//                memcpy(data + lengthOfChallengeServer + lengthOfCertificateServer,R1,SHA256_DIGEST_LENGTH);
//                if(x509->Signature_verify_AutoX(data,lengthOfChallengeServer + lengthOfCertificateServer + SHA256_DIGEST_LENGTH,proofOfOwnershipServer,&lengthOfProofOfOwnershipServer))
//                {
//                    emit emitString("PO验证失败------");
//                    isContinue = BOOL_TRUE;
//                    break;
//                }
//                free(data);

















//                if(sendAndReceiveMessage(type,&link_iso,reqMsg,respMsg) == Res_OK)
//                {
//                    uint8_t compareSize = QByteArray::fromHex(seqResp.toLatin1()).length();
//                    memcpy(respData,QByteArray::fromHex(seqResp.toLatin1()).data(),compareSize);
//                    emit emitString(outPutTime + uint8ArrayToHexString(respMsg->payload,respMsg->size));
//                    if(checkResultUDS(respData,compareSize,respMsg) != Res_OK)
//                    {
//                        isContinue = BOOL_TRUE;
//                        break;
//                    }
//                    else
//                    {
//                        lengthOfChallengeServer = (((uint16_t)respMsg->payload[3] << 8) | respMsg->payload[4]);
//                        memcpy(ChallengeServer,&respMsg->payload[5],lengthOfChallengeServer);
//                        lengthOfCertificateServer = (((uint16_t)respMsg->payload[5 + lengthOfChallengeServer] << 8)| respMsg->payload[5 + lengthOfChallengeServer +1]);
//                        memcpy(certificateServer,&respMsg->payload[5 + lengthOfChallengeServer +2],lengthOfCertificateServer);
//                        lengthOfProofOfOwnershipServer =  (((uint16_t)respMsg->payload[8 + lengthOfChallengeServer + lengthOfCertificateServer] << 8)| respMsg->payload[8 + lengthOfChallengeServer + lengthOfCertificateServer + 1]);
//                        memcpy(proofOfOwnershipServer,&respMsg->payload[8 + lengthOfChallengeServer + lengthOfCertificateServer + 2],lengthOfProofOfOwnershipServer);
//                        if(x509->X509_verify_AutoX(const_cast<const unsigned char*>(certificateServer),lengthOfCertificateServer) == false)
//                        {
//                            emit emitString("服务端证书验证失败------");
//                            isContinue = BOOL_TRUE;
//                            break;
//                        }
//                        uint8_t *data = (uint8_t *)malloc(sizeof (uint8_t) * 4096);
//                        memcpy(data,ChallengeServer,lengthOfChallengeServer);
//                        memcpy(data + lengthOfChallengeServer,certificateServer,lengthOfCertificateServer);
//                        memcpy(data + lengthOfChallengeServer + lengthOfCertificateServer,R1,SHA256_DIGEST_LENGTH);
//                        if(x509->Signature_verify_AutoX(data,lengthOfChallengeServer + lengthOfCertificateServer + SHA256_DIGEST_LENGTH,proofOfOwnershipServer,&lengthOfProofOfOwnershipServer))
//                        {
//                            emit emitString("PO验证失败------");
//                            isContinue = BOOL_TRUE;
//                            break;
//                        }
//                        free(data);
//                    }
//                }
//                else
//                {
//                    isContinue = BOOL_TRUE;
//                    break;
//                }
//            }
//                break;
//            case ProofOfOwnership:
//            {
//                uint16_t certSize = 0;
//                reqMsg->size = QByteArray::fromHex(seqRequest.toLatin1()).length();
//                memcpy(sendData,QByteArray::fromHex(seqRequest.toLatin1()).data(),reqMsg->size);
//                reqMsg->isFunction = 0;
//                memcpy(reqMsg->payload,sendData,reqMsg->size);
//                uint8_t *data = (uint8_t *)malloc(sizeof (uint8_t) * (SHA256_DIGEST_LENGTH + SHA512_DIGEST_LENGTH));
//                memcpy(data,R1,SHA256_DIGEST_LENGTH);
//                uint8_t signature[4096];
//                uint64_t signLen;
//                memcpy(data +SHA256_DIGEST_LENGTH,ChallengeServer,lengthOfChallengeServer);
//                bool result = x509->Signature_generate_AutoX(data,SHA256_DIGEST_LENGTH + SHA512_DIGEST_LENGTH,signature,&signLen);
//                reqMsg->payload[2] = (signLen & 0xFF00) >> 8;
//                reqMsg->payload[3] = signLen & 0xFF;
//                memcpy(&reqMsg->payload[4],signature,signLen);
//                reqMsg->size += signLen;
//                memset(&reqMsg->payload[4 + signLen],0x00,2);
//                reqMsg->size += 4;
//                free(data);
//                QDateTime currentTime = QDateTime::currentDateTime();
//                QString outPutTime = "[" + currentTime.toString("yyyy-MM-dd hh:mm:ss") + "] ";
//                emit emitString(outPutTime + uint8ArrayToHexString(sendData,3));
//                if(sendAndReceiveMessage(type,&link_iso,reqMsg,respMsg) == Res_OK)
//                {
//                    uint8_t compareSize = QByteArray::fromHex(seqResp.toLatin1()).length();
//                    memcpy(respData,QByteArray::fromHex(seqResp.toLatin1()).data(),compareSize);
//                    emit emitString(outPutTime + uint8ArrayToHexString(respMsg->payload,respMsg->size));
//                    if(checkResultUDS(respData,compareSize,respMsg) != Res_OK)
//                    {
//                        isContinue = BOOL_TRUE;
//                        break;
//                    }
//                    else
//                    {

//                    }
//                }
//                else
//                {
//                    isContinue = BOOL_TRUE;
//                    break;
//                }

//            }
//                break;
#endif **/
            case downloadRequestHex:
            {
                reqMsg->isFunction = 0;
                reqMsg->size = QByteArray::fromHex(seqRequest.toLatin1()).length();
                memcpy(reqMsg->payload,QByteArray::fromHex(seqRequest.toLatin1()).data(),reqMsg->size);

                reqMsg->payload[reqMsg->size] = ((uint64_t)flashNode->head->mfileStart & 0xFF000000) >> 24;
                reqMsg->payload[++reqMsg->size] = ((uint64_t)flashNode->head->mfileStart & 0xFF0000) >> 16;
                reqMsg->payload[++reqMsg->size] = ((uint64_t)flashNode->head->mfileStart & 0xFF00) >> 8;
                reqMsg->payload[++reqMsg->size] = ((uint64_t)flashNode->head->mfileStart & 0xFF);
                ++reqMsg->size;
                reqMsg->payload[reqMsg->size] = ((uint64_t)flashNode->head->mfileSize & 0xFF000000) >> 24;
                reqMsg->payload[++reqMsg->size] = ((uint64_t)flashNode->head->mfileSize & 0xFF0000) >> 16;
                reqMsg->payload[++reqMsg->size] = ((uint64_t)flashNode->head->mfileSize & 0xFF00) >> 8;
                reqMsg->payload[++reqMsg->size] = ((uint64_t)flashNode->head->mfileSize & 0xFF);
                ++reqMsg->size;

                GETTIME_OUTPUT(reqMsg->payload,reqMsg->size,"TX ");
                if(sendAndReceiveMessage(type,&link_iso,reqMsg,respMsg) == Res_OK)
                {
                    uint8_t compareSize = QByteArray::fromHex(seqResp.toLatin1()).length();
                    memcpy(respData,QByteArray::fromHex(seqResp.toLatin1()).data(),compareSize);
                    GETTIME_OUTPUT(respMsg->payload,respMsg->size,"RX ");
                    if(checkResultUDS(respData,compareSize,respMsg) != Res_OK)
                    {
                        isContinue = BOOL_TRUE;
                        break;
                    }
                    else
                    {
                        if(respMsg->size == 6)
                        {
                            blocksize = ((respMsg->payload[2] << 24) |(respMsg->payload[3] << 16) | (respMsg->payload[4] << 8) | respMsg->payload[5]);
                        }
                        else if(respMsg->size == 4)
                        {
                            blocksize = ((respMsg->payload[2] << 8) |(respMsg->payload[3]));
                        }
//                        blocksize = 0x3EA;
                    }
                }
                else
                {
                    isContinue = BOOL_TRUE;
                    break;
                }

            }
                break;
            case downloadHex:
            {
                uint32_t downloadFileSize = flashNode->head->mfileSize;
                uint32_t downloadFileStartAddr = flashNode->head->mfileStart;
                uint8_t* readData;
                int BlockCount = 0x01;
                int blockIndex = 0;
                int blockNum = 0;
                struct sendMsg downloadData;
                struct sendMsg *rxmsg;
                rxmsg = (struct sendMsg*)malloc(sizeof(struct sendMsg));
                uint32_t sendblock = blocksize -2;
                blockNum = downloadFileSize / sendblock;
                readData = Hex2Binfile(flashNode->head->mfilename.toStdString().c_str(),downloadFileSize,downloadFileStartAddr);
                while (true) {
                    if(blockIndex < blockNum)
                    {
                        downloadData.payload[0] = 0x36;
                        downloadData.payload[1] = BlockCount;
                        downloadData.isFunction=0;
                        downloadData.size = sendblock + 2;

                    }
                    else
                    {
                        downloadData.payload[0] = 0x36;
                        downloadData.payload[1] = BlockCount;
                        downloadData.isFunction=0;
                        downloadData.size = downloadFileSize - blockIndex * sendblock + 2;
                        if(downloadFileSize - blockIndex * sendblock == 0)
                            break;
                    }
                    memcpy(&downloadData.payload[2],&readData[blockIndex * sendblock],downloadData.size - 2);

                    crc32_Caculate(&downloadData.payload[2],downloadData.size -2,&initialCRC32Value);
                    GETTIME_OUTPUT(downloadData.payload,10,"TX ");
                    emit emitDataSize(downloadData.size - 2);

                    if(sendAndReceiveMessage(type,&link_iso,&downloadData,rxmsg) != Res_OK)
                    {
                        GETTIME_OUTPUT(rxmsg->payload,rxmsg->size,"RX ");
                        isContinue = BOOL_TRUE;
                        break;
                    }
                    GETTIME_OUTPUT(rxmsg->payload,rxmsg->size,"RX ");

                    uint8_t downloadResp[2];
                    downloadResp[0] = 0x76;
                    downloadResp[1] = BlockCount;

                    if(checkResultUDS(downloadResp,2,rxmsg) != Res_OK)
                    {
                        isContinue = BOOL_TRUE;
                        break;
                    }

                    blockIndex++;
                    BlockCount++;
                    if(BlockCount > 0xFF)
                        BlockCount = 0x00;
                    if(blockIndex > blockNum)
                        break;
                }
            }
                break;
            case writeDate:
                {
                    reqMsg->size = QByteArray::fromHex(seqRequest.toLatin1()).length();
                    memcpy(&reqMsg->payload[0],QByteArray::fromHex(seqRequest.toLatin1()).data(),reqMsg->size);


                    int year = QDateTime::currentDateTime().date().year() - 2000;
                    int month = QDateTime::currentDateTime().date().month();
                    int day = QDateTime::currentDateTime().date().day();
                    reqMsg->payload[reqMsg->size++] = int_to_bcd_bytes(year);
                    reqMsg->payload[reqMsg->size++] = int_to_bcd_bytes(month);
                    reqMsg->payload[reqMsg->size++] = int_to_bcd_bytes(day);
                    memset(&reqMsg->payload[reqMsg->size],0x01,0x06);
                    reqMsg->size += 6;
                    GETTIME_OUTPUT(reqMsg->payload,reqMsg->size,"TX ");
                    if(sendAndReceiveMessage(type,&link_iso,reqMsg,respMsg) == Res_OK)
                    {
                        uint8_t compareSize = QByteArray::fromHex(seqResp.toLatin1()).length();
                        memcpy(respData,QByteArray::fromHex(seqResp.toLatin1()).data(),compareSize);

                        GETTIME_OUTPUT(respMsg->payload,respMsg->size,"RX ");
                        if(checkResultUDS(respData,compareSize,respMsg) != Res_OK)
                        {
                            isContinue = BOOL_TRUE;
                            break;
                        }

                    }
                    else
                    {

                        isContinue = BOOL_TRUE;
                        break;
                    }


                }
                break;
            case next:
                {
                    uint8_t insertIndex = i;
                    filename_link = flashNode->head->mfilename;
                    flashNode->deleteHead();
                    if(flashNode->head != NULL)
                    {
//                        if(filename_link.toUpper().contains("FLASHDRIVER"))
//                        {
//                            flashIdx++;
//                        }
//                        if(filename_link.toUpper().contains("FLASHDRIVER") && !flashNode->head->mfilename.toUpper().contains("FLASHDRIVER") && (flashIdx > 1))
//                        {
//                            cJSON *item_1 = cJSON_CreateString("writeDate;2E F1 5A;6E F1 5A");
//                            insertIndex++;
//                            cJSON_InsertItemInArray(mDataflow.sequence,insertIndex,item_1);
//                            seqSize ++;
//                            flashIdx = 0;
//                        }
//                        else if((flashIdx == 1) && filename_link.toUpper().contains("FLASHDRIVER")&& !flashNode->head->mfilename.toUpper().contains("FLASHDRIVER"))
//                        {
//                            cJSON *item_6 = cJSON_CreateString("checkCRC;31 01 02 02;71 01 02 02 00");
//                            insertIndex++;
//                            cJSON_InsertItemInArray(mDataflow.sequence,insertIndex,item_6);
//                            seqSize ++;
//                            cJSON *item_7 = cJSON_CreateString("next;");
//                            insertIndex++;
//                            cJSON_InsertItemInArray(mDataflow.sequence,insertIndex,item_7);
//                            seqSize ++;
//                            cJSON *item_1 = cJSON_CreateString("writeDate;2E F1 5A;6E F1 5A");
//                            insertIndex++;
//                            cJSON_InsertItemInArray(mDataflow.sequence,insertIndex,item_1);
//                            seqSize ++;
//                            flashIdx = 0;
//                        }
                        if(!flashNode->head->mfilename.toUpper().contains("FLASHDRIVER")) //app flash
                        {
                            if(filename_link != flashNode->head->mfilename)
                            {
                                cJSON *item_2 = cJSON_CreateString("EraseFlash;31 01 FF 00 44;71 01 FF 00 00");
                                insertIndex++;
                                cJSON_InsertItemInArray(mDataflow.sequence,insertIndex,item_2);
                                seqSize ++;
                            }

                            cJSON *item_3 = cJSON_CreateString("downloadRequestHex;34 00 44;74");
                            insertIndex++;
                            cJSON_InsertItemInArray(mDataflow.sequence,insertIndex,item_3);
                            seqSize ++;
                            cJSON *item_4 = cJSON_CreateString("downloadHex;36;76");
                            insertIndex++;
                            cJSON_InsertItemInArray(mDataflow.sequence,insertIndex,item_4);
                            seqSize ++;
                            cJSON *item_5 = cJSON_CreateString("phyRequest;37;77");
                            insertIndex++;
                            cJSON_InsertItemInArray(mDataflow.sequence,insertIndex,item_5);
                            seqSize ++;
                            if((flashNode->head->next != NULL && flashNode->head->mfilename != flashNode->head->next->mfilename) || (flashNode->head->next == NULL))
                            {
                                cJSON *item_6 = cJSON_CreateString("checkCRC;31 01 02 02;71 01 02 02 00");
                                insertIndex++;
                                cJSON_InsertItemInArray(mDataflow.sequence,insertIndex,item_6);
                                seqSize ++;
                            }

                            cJSON *item_7 = cJSON_CreateString("next;");
                            insertIndex++;
                            cJSON_InsertItemInArray(mDataflow.sequence,insertIndex,item_7);
                            seqSize ++;
                        }

                    }
                }
                break;
            case sendMsgData:
            {
                reqMsg->size = QByteArray::fromHex(seqRequest.toLatin1()).length();
                memcpy(&reqMsg->payload[0],QByteArray::fromHex(seqRequest.toLatin1()).data(),reqMsg->size);

                GETTIME_OUTPUT(reqMsg->payload,reqMsg->size,"TX ");

                if(sendAndReceiveMessage(type,&link_iso,reqMsg,respMsg) == Res_OK)
                {
                    uint8_t compareSize = QByteArray::fromHex(seqResp.toLatin1()).length();
                    memcpy(respData,QByteArray::fromHex(seqResp.toLatin1()).data(),compareSize);

                    GETTIME_OUTPUT(respMsg->payload,respMsg->size,"RX ");
                    if((compareSize != 0) && (checkResultUDS(respData,compareSize,respMsg) != Res_OK))
                    {
                        isContinue = BOOL_TRUE;
                        break;
                    }

                }
                else
                {
                    emit emitString(QString("未响应"));
                    break;
                }
            }
                break;
            default:
                break;
        }
        if(isContinue == BOOL_TRUE)
        {
            emit emitString("-------------------------Failed-------------------------");
            emitStop();
            //delete x509;

            return;
        }
    }

    emit emitString("-------------------------Succeed-------------------------");
    emitStop();
    return ;
}

void flash::praseHexFile()
{
    char *rpath = "D:\\_02_project\\xnav_s32k344.hex";
    char *wpath = "D:\\_02_project\\1.bin";
    Hex2Bin(rpath,wpath);
}
uint32_t flash::crc32_Caculate(uint8_t* ReqBuffer,uint16_t ReqBufferLen,uint32_t* crcValue)
{
    for(int i = 0;i < ReqBufferLen;i++)
    {
        *crcValue = crc_table[(*crcValue  ^ ReqBuffer[i]) & 0xff] ^ (*crcValue  >> 8);
    }
    return *crcValue;
}

void flash::initCANTP()
{
    struct can_iso_tp_init_t *init = NULL;
    init = (struct can_iso_tp_init_t *)malloc(sizeof(struct can_iso_tp_init_t));
    init_for_can_iso_tp(0,init,mDataflow.requestID,mDataflow.responseID,mDataflow.cantype);

    iso_can_tp_create(&link_iso,init);
}




