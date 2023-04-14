#include "../include/editlangdialog.h"
#include "ui_editlangdialog.h"

#include <QSqlQuery>
#include <QSqlDatabase>
#include <QFile>


extern QStringList g_langList;




EditLangDialog::EditLangDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditLangDialog),
    globalBuff(new InfoBuffer),
    localBuff(new InfoBuffer)
{
    ui->setupUi(this);
    ui->listLang->addItems(std::move(g_langList));


    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("dataBase/Languages.db");

    db.open();

    QSqlQuery query(db);

    query.exec("SELECT checked, lang_list FROM currentSettings");
    query.next();

    bool check = query.value(0).toBool();
    QStringList langs = query.value(1).toString().split(" ");

    if(check){
        localBuff = new InfoBuffer;
        globalBuff->setInfo(QStringList({"French", "German"}), 0, true);
    }
    else {
        globalBuff->setInfo(langs, 0, check);
        localBuff = new InfoBuffer(globalBuff);
    }

    setWindowIcon(QIcon("images/settings.png"));
}

EditLangDialog::~EditLangDialog()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("dataBase/Languages.db");

    db.open();

    QSqlQuery query(db);

    QString check = globalBuff->checked ? "1" : "0";
    QString langs = globalBuff->getList().join(" ");

    if (langs.isEmpty()){
        langs = "French German";
        check = "1";
    }

    query.exec("UPDATE currentSettings SET "
               "checked = " + check + ", "
               "lang_list = " + "\"" + langs + "\"");


    delete localBuff;
    delete globalBuff;
    delete ui;
}




// Setter for buffer from information in dialog window
void EditLangDialog::setInfoBuffer(InfoBuffer *info)
{
    bool flag = ui->defSettings_chb->checkState();
    int index = ui->listLang->currentIndex();

    QStringList list;
    auto &ref = ui->listWidget;

    for(int i = 0; i < ref->count(); ++i)
        list << ref->item(i)->text();

    info->setInfo(list, index, flag);
}



// Setters for options dialog window
void EditLangDialog::setterInfo()
{
    ui->defSettings_chb->setChecked(globalBuff->checked);
    ui->listLang->setCurrentIndex(globalBuff->row);
    ui->listWidget->clear();
    ui->listWidget->addItems(globalBuff->list);

    if(ui->defSettings_chb->isChecked())
        setEnableStatus(false);
    else
        setEnableStatus(true);
}

void EditLangDialog::setterInfo(const QString &original, const QString &finaly)
{
    ui->originalLang_lb->setText(original);
    ui->originalLang_lb->setTextFormat(Qt::RichText);

    ui->finalyLang_lb->setText(finaly);
    ui->finalyLang_lb->setTextFormat(Qt::RichText);

    setterInfo();
}



// User interface on/off
void EditLangDialog::setEnableStatus(bool st)
{
    ui->listWidget->setEnabled(st);
    ui->removeItem_btn->setEnabled(st);
    ui->addItem_btn->setEnabled(st);
}






// Slots:

void EditLangDialog::on_apply_btn_clicked()
{
    setInfoBuffer(globalBuff);
    localBuff->clear();

    close();
}

void EditLangDialog::on_cancel_btn_clicked()
{
    localBuff->clear();

    setEnableStatus(!globalBuff->checked);

    close();
}

void EditLangDialog::on_addItem_btn_clicked()
{
    int index = ui->listLang->currentIndex();
    ui->listWidget->addItem(g_langList[index]);
}

void EditLangDialog::on_removeItem_btn_clicked()
{
    int currRow = ui->listWidget->currentRow();

    if(currRow != -1)
        delete ui->listWidget->takeItem(currRow);
}






void EditLangDialog::closeEvent(QCloseEvent *)
{
    on_cancel_btn_clicked();
}



void EditLangDialog::on_defSettings_chb_clicked(bool checked)
{
    if(checked) {
        setInfoBuffer(localBuff);
        ui->listWidget->clear();
        setEnableStatus(false);
        ui->listWidget->addItems(QStringList({"French", "German"}));
    }
    else {
        ui->listLang->setCurrentIndex(localBuff->row);
        ui->listWidget->clear();
        ui->listWidget->addItems(localBuff->list);
        setEnableStatus(true);
    }
}
