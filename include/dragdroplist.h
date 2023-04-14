#ifndef DRAGDROPLIST_H
#define DRAGDROPLIST_H

#include <QListWidget>



class DragDropList: public QListWidget
{

public:

    explicit DragDropList(QListWidget *parent = nullptr);
    ~DragDropList() = default;

    void add(const QStringList&);
    void add(const QList<QUrl>&);

    void remove(/* current row */);

    bool isEmpty() { return count() == 0 ? true : false; }

    const QStringList& getPaths() const { return filePath; }

private:

    QSet<QString> fileHistory;
    QStringList filePath;


    // Drag and drop

    void dragEnterEvent(QDragEnterEvent* event);
    void dragMoveEvent(QDragMoveEvent* event);
    void dragLeaveEvent(QDragLeaveEvent* event);
    void dropEvent(QDropEvent* event);
};

#endif // DRAGDROPLIST_H
