#ifndef INFOBUFFER_H
#define INFOBUFFER_H

#include <QStringList>



struct InfoBuffer
{

public:

    bool checked;
    int row;

    QStringList list;

////////////////////////////////////////////////////////////////////////////////////

    explicit InfoBuffer(const QStringList& lt = {}, int rw = 0, bool chk = true);

    ~InfoBuffer() = default;

    InfoBuffer(const InfoBuffer*);

    void operator = (const InfoBuffer*);

    void setInfo(const QStringList& lt = {}, int rw = 0, bool chk = true);

    QStringList& getList() { return list; }
    const QStringList& getList() const { return list; }

    void clear();
};

#endif // INFOBUFFER_H
