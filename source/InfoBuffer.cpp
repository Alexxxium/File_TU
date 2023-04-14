#include "../include/InfoBuffer.h"




InfoBuffer::InfoBuffer(const QStringList &lt, int rw, bool chk):
    checked(chk),
    row(rw),
    list(std::move(lt))
{
}

InfoBuffer::InfoBuffer(const InfoBuffer *buff):
    checked(buff->checked),
    row(buff->row),
    list(buff->list)
{
}

void InfoBuffer::operator = (const InfoBuffer *buff)
{
    if (this == buff) return;

    checked = buff->checked;
    row = buff->row;
    list = buff->list;
}

void InfoBuffer::setInfo(const QStringList& lt, int rw, bool chk)
{
    checked = chk;
    row = rw;
    list = lt;
}

void InfoBuffer::clear() { setInfo(); }
