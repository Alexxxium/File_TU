#include "../include/menueform.h"
#include "../include/process.h"
#include "ui_menueform.h"


#include <QFileDialog>
#include <QMessageBox>



extern QWidget *g_currMenu;
extern QStringList g_langList;




MenueForm::MenueForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenueForm),
    dialog(nullptr),
    settingsPtr(nullptr)
{
    ui->setupUi(this);

    ui->nativLang_cb->addItems(std::move(g_langList));
    ui->exodusLang_cb->addItems(std::move(g_langList));

    listWidget = new DragDropList();                // Временно, для удобства (не забыть бы удалить)
    delete ui->listWidget;

    ui->filesLayout->addWidget(listWidget);


    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("dataBase/Languages.db");
    QSqlQuery query(db);

    db.open();

    query.exec("SELECT * FROM currentSettings");
    query.next();

    ui->nativLang_cb->setCurrentIndex(query.value(0).toInt());
    ui->exodusLang_cb->setCurrentIndex(query.value(1).toInt());

    db.close();
}

MenueForm::~MenueForm()
{
    delete dialog;

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("dataBase/Languages.db");

    db.open();
    QSqlQuery query(db);

    QString index1 = QString::number(ui->nativLang_cb->currentIndex());
    QString index2 = QString::number(ui->exodusLang_cb->currentIndex());

    query.exec("UPDATE currentSettings SET "
           "nativ_lang = " + index1 + ", "
           "final_lang = " + index2);

    db.close();


    delete ui;
}





// Delete "options" button
void MenueForm::delSettingsBtn()
{
    delete ui->options_btn;
    ui->options_btn = nullptr;
    delete dialog;
    dialog = nullptr;
}

// Add referens to "Settings"
void MenueForm::setSettingsPtr(Settings *ptr)
{
    settingsPtr = ptr;
}

QStringList getKeys(const QStringList &list)
{
    QStringList result;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("dataBase/Languages.db");

    db.open();

    QSqlQuery query(db);

    for(const auto &i : list){
        query.exec("SELECT key FROM langs WHERE lang = \"" + i + "\"");
        query.next();
        result << query.value(0).toString();
        query.clear();
    }

    db.close();

    return result;
}



// Slots:

void MenueForm::on_options_btn_clicked()
{
    if(!dialog)
        dialog = new EditLangDialog;

    dialog->setterInfo(ui->nativLang_cb->currentText(), ui->exodusLang_cb->currentText());
    dialog->exec();
}



void MenueForm::on_apply_btn_clicked()
{
    if(listWidget->isEmpty()) return;

    QString save(settingsPtr->getSavePath());

    if(!QDir(save).exists()){
        QMessageBox msgBox;
        msgBox.setText("Save path: " + save + " does not exist!");
        msgBox.exec();
        return;
    }

    QList<QStringList> argvs;
    QStringList paths(listWidget->getPaths());
    QStringList langs = dialog ? dialog->getLangList() : QStringList();


    langs.push_front(ui->nativLang_cb->currentText());
    langs.push_back(ui->exodusLang_cb->currentText());

    QStringList args = getKeys(langs);
    args.push_front(save);

    for (auto &i : paths){
        args.push_front(i);
        argvs << args;
        args.pop_front();
    }


    bool multiFlag = settingsPtr->isMultiThered();

    Process proc("translateModule/TU.exe", argvs, listWidget, multiFlag);
    proc.startAllProcesses();


    ui->apply_btn->setEnabled(false);
    ui->addFile_btn->setEnabled(false);
    ui->removeFile_btn->setEnabled(false);
    listWidget->setEnabled(false);
}

void MenueForm::on_cancel_btn_clicked()
{
    g_currMenu = nullptr;
    this->~MenueForm();
}



void MenueForm::on_addFile_btn_clicked()
{
    QStringList list = QFileDialog::getOpenFileNames(0, "Chouse files", "", "*.txt *.docx");

    listWidget->add(list);
}

void MenueForm::on_removeFile_btn_clicked()
{
    listWidget->remove();
}
