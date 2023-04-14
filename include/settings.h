#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>



namespace Ui {
class Settings;
}



class Settings : public QDialog
{
    Q_OBJECT

public:

    explicit Settings(QDialog *parent = nullptr);
    virtual ~Settings();

    void setDefaultSettings();
    void saveSettings();

    QString getSavePath() const;
    bool isMultiThered() const;


private slots:

    void on_browse_pb_clicked();
    void on_defaultPath_chb_clicked(bool checked);


private:

    Ui::Settings *ui;
};

#endif // SETTINGS_H
