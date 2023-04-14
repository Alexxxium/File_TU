#include "../include/process.h"



Process::Process(const QString& appl, const QList<QStringList>& args, DragDropList* it, const bool mlt):
     multi(mlt), application(appl), argvs(args), items(it)
{
    rubish.reserve(argvs.size());
}

Process::~Process()
{
    for(auto &i : rubish)
        delete i;
}




void Process::startProcess(const QStringList &args)
{
    static int counter = 0;

    QProcess *proc = new QProcess;
    rubish << proc;

    proc->start(application, args);

    if(!multi){
        proc->waitForFinished();
        if(proc->exitCode() != 0)
            setStatusColor(counter++, false);
        else
            setStatusColor(counter++, true);
    }

}

void Process::startAllProcesses()
{
    for (auto &i : argvs)
        startProcess(i);

    if(multi)
        waitAll();
}



void Process::setStatusColor(const int index, bool st)
{
    if (st)
        items->item(index)->setBackground(Qt::green);
    else
        items->item(index)->setBackgroundColor(Qt::red);
}

void Process::waitAll()
{
    int count = 0;

    while (count != rubish.size()) {
        for(int i = 0; i < rubish.size(); ++i){
            if (rubish[i]->waitForFinished()){
                count++;
                if(rubish[i]->exitCode() != 0)
                    setStatusColor(i, false);
                else
                    setStatusColor(i, true);
                break;
            }
        }
    }
}




