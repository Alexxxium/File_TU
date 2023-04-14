#include "../include/settings.h"
#include "ui_settings.h"

#include <QFileDialog>
#include <QTextStream>




Settings::Settings(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);


    QDir().mkdir("settings");

    QFile file("settings/settings.txt");

    QTextStream out(&file);

    if(file.exists()) {
        file.open(QIODevice::ReadOnly);

        QString multiThered = out.readLine().simplified(),
                defaultPath = out.readLine().simplified(),
                currentPath = out.readLine().simplified();


        if (multiThered == "0")
            ui->multThread_chb->setChecked(false);
        else if(multiThered != "")
            ui->multThread_chb->setChecked(true);
        else
            setDefaultSettings();


        if (defaultPath == "0")
            ui->defaultPath_chb->setChecked(false);

        else if(defaultPath != ""){
            ui->defaultPath_chb->setChecked(true);
            ui->pathLine_led->setEnabled(false);
            ui->browse_pb->setEnabled(false);
        }
        else
            setDefaultSettings();

        if (currentPath != "")
            ui->pathLine_led->setText(currentPath);
        else
            setDefaultSettings();
    }
    else
        setDefaultSettings();

    setWindowIcon(QIcon("images/settings.png"));

    file.close();
}

Settings::~Settings()
{
    saveSettings();
    delete ui;
}




void Settings::setDefaultSettings()
{
    QDir().mkdir("settings");

    QFile file("settings//settings.txt");
    QTextStream out(&file);

    file.open(QIODevice::WriteOnly);

    QString defaultDir = QDir::homePath() + "/TU files";

    out << "0\n" << "1\n" << defaultDir;

    ui->multThread_chb->setChecked(false);
    ui->defaultPath_chb->setChecked(true);
    ui->pathLine_led->setEnabled(false);
    ui->browse_pb->setEnabled(false);
    ui->pathLine_led->setText(defaultDir);

    file.close();
}

void Settings::saveSettings()
{
    QDir().mkdir("settings");

    bool multiThread_st = ui->multThread_chb->isChecked(),
         defaultPath_st = ui->defaultPath_chb->isChecked();

    QString savePath = ui->pathLine_led->text();

    QFile file("settings/settings.txt");
    QTextStream out(&file);

    file.remove();

    file.open(QIODevice::WriteOnly);

    out << multiThread_st << '\n' << defaultPath_st << '\n' << savePath << '\n';

    file.close();
}


// Getters
QString Settings::getSavePath() const
{
    return ui->pathLine_led->text();
}

bool Settings::isMultiThered() const
{
    return ui->multThread_chb->isChecked();
}



// Slots:

void Settings::on_browse_pb_clicked()
{
    QString str = QFileDialog::getExistingDirectory(0, "Chouse directory", "");

    ui->pathLine_led->setText(str);
}


void Settings::on_defaultPath_chb_clicked(bool checked)
{
    if(checked){
        ui->pathLine_led->setText(QDir::homePath() + "/TU files");
        ui->pathLine_led->setEnabled(false);
        ui->browse_pb->setEnabled(false);
    }
    else {
        ui->pathLine_led->setEnabled(true);
        ui->browse_pb->setEnabled(true);
    }
}
