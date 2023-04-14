#include "../include/dragdroplist.h"

#include <QDropEvent>
#include <QMimeData>
#include <QFileInfo>




DragDropList::DragDropList(QListWidget *parent):
    QListWidget(parent)
{
    setAcceptDrops(true);
    setFont(QFont("MV Boli", 12));

    setAutoFillBackground(true);
}




QListWidgetItem* getItem(const QString &path)
{
    QListWidgetItem *item;

    if (path.endsWith(".txt"))
        item = new QListWidgetItem(QIcon("images/txtFile.png"), QFileInfo(path).fileName());
    else if (path.endsWith(".docx"))
        item = new QListWidgetItem(QIcon("images/docxFile.jpg"), QFileInfo(path).fileName());
    else
        item = nullptr;

    if(item)
        item->setToolTip(path);

    return item;
}




void DragDropList::add(const QStringList &list)
{
    if(list.empty()) return;

    for(auto &i : list) {
        if(!fileHistory.contains(i)) {

            auto item = getItem(i);

            if (item){
                addItem(item);
                filePath << i;
                fileHistory << i;
            }
        }
    }
}

void DragDropList::add(const QList<QUrl> &list)
{
    if(list.empty()) return;

    for(auto &i : list){
        if(!fileHistory.contains(i.toLocalFile())) {

            auto item = getItem(i.toString().remove(0, 8));

            if(item){
                addItem(item);
                fileHistory << i.toLocalFile();
                filePath << i.toLocalFile();
            }
        }
    }
}

void DragDropList::remove()
{
    int row = currentRow();

    if (row != -1){
        delete takeItem(row);
        fileHistory.remove(filePath[row]);
        filePath.removeAt(row);
    }
}





//  DRAG AND DROP:

void DragDropList::dragEnterEvent(QDragEnterEvent* event)
 {
    event->acceptProposedAction();
    setPalette(Qt::blue);
    //setStyleSheet("background-image:url(../images/blue.jpg)");
 }

void DragDropList::dragMoveEvent(QDragMoveEvent* event)
 {
    event->acceptProposedAction();
 }

void DragDropList::dragLeaveEvent(QDragLeaveEvent* event)
 {
    setPalette(Qt::white);
    event->accept();
 }

void DragDropList::dropEvent(QDropEvent* event)
 {
    setPalette(Qt::white);
    add(event->mimeData()->urls());
 }
