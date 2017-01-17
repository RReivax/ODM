#ifndef DATA_ID_H
#define DATA_ID_H

typedef struct data_id{
    int id;
    char* data;
    data_id(int nid, char *ndata) : id(nid), data(ndata) {}
    data_id():id(-1), data(NULL){}
} data_id;


#endif // DATA_ID_H
