#ifndef MENUEFORM_H
#define MENUEFORM_H

#include "mainwindow.h"
#include "editlangdialog.h"
#include "dragdroplist.h"



namespace Ui {
class MenueForm;
}



class MenueForm : public QWidget
{
    Q_OBJECT

public:

    explicit MenueForm(QWidget *parent = nullptr);
    ~MenueForm();

    void delSettingsBtn();

    void setSettingsPtr(Settings*);


private:

    Ui::MenueForm *ui;
    EditLangDialog *dialog;
    DragDropList *listWidget;
    Settings *settingsPtr;


private slots:

    void on_options_btn_clicked();
    void on_cancel_btn_clicked();
    void on_apply_btn_clicked();
    void on_addFile_btn_clicked();
    void on_removeFile_btn_clicked();
};

#endif // MENUEFORM_H
