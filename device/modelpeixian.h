#ifndef MODELPEIXIAN
#define MODELPEIXIAN
#include <QObject>
#include <QVector>
#include <QString>
class modelPeiXian : public QObject
{
public:
    //static QVector<QString> PeiXianJiaChang(int scanid, char Sort1, char Port1, char Sort2, char Port2, char AlmType);

    static QVector<QString> modelPeiXian::PeiXianJiaChang(int scanid, char Sort1, char Port1, char Sort2, char Port2, char AlmType)
    {
        QVector<QString> vector;
        vector.resize(6);
        vector.append(QString::number(scanid,10));
        vector.append(QString::number(Sort1,10));
        vector.append(QString::number(Port1,10));
        vector.append(QString::number(Sort2,10));
        vector.append(QString::number(Port2,10));
        vector.append(QString::number(AlmType,10));
        return vector;
    }



};

#endif // MODELPEIXIAN




