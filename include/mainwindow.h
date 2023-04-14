#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "settings.h"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:

    QSqlDatabase db;
    QSqlQuery *query;

    Ui::MainWindow *ui;
    QWidget *currMenue;
    Settings *settings;


private slots:

    void translateFile();
    void updateFile();
    void deleteMenu();
    void settingsDialog();
};

#endif // MAINWINDOW_H
