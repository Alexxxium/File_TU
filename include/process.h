#ifndef PROCESS_H
#define PROCESS_H

#include "dragdroplist.h"

#include <QVector>
#include <QProcess>




class Process
{

private:

    bool multi;

    QString application;
    QList<QStringList> argvs;

    QVector<QProcess*> rubish;
    DragDropList *items;

    void waitAll();
    void setStatusColor(const int, bool st = true);

public:

    explicit Process(const QString&, const QList<QStringList>&, DragDropList*, const bool mlt = true);
    ~Process();

    void startProcess(const QStringList&);
    void startAllProcesses();
};

#endif // PROCESS_H
