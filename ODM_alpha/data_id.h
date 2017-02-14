#ifndef DATA_ID_H
#define DATA_ID_H
#include <QJsonObject>

namespace odm{
    typedef struct data_id{
        int id;
        QJsonObject data;
        data_id(int nid, QJsonObject ndata) : id(nid), data(ndata) {}
        data_id():id(-1), data(){}
    } data_id;
}

#endif // DATA_ID_H
