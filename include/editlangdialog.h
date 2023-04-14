#ifndef EDITLANGDIALOG_H
#define EDITLANGDIALOG_H

#include <QDialog>

#include "InfoBuffer.h"



class MenuForm;

namespace Ui {
class EditLangDialog;
}



class EditLangDialog : public QDialog
{
    Q_OBJECT

public:

    explicit EditLangDialog(QWidget *parent = nullptr);
    ~EditLangDialog();

    void setterInfo(const QString&, const QString&);
    void setterInfo();

    void setInfoBuffer(InfoBuffer*);
    void setEnableStatus(bool);

    QStringList& getLangList() { return globalBuff->list; }


private:

    Ui::EditLangDialog *ui;

    InfoBuffer *globalBuff;
    InfoBuffer *localBuff;

    void closeEvent(QCloseEvent*) override;


private slots:

    void on_apply_btn_clicked();
    void on_cancel_btn_clicked();

    void on_addItem_btn_clicked();
    void on_removeItem_btn_clicked();
    void on_defSettings_chb_clicked(bool);
};

#endif // EDITLANGDIALOG_H
