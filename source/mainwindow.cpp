#include "ui_mainwindow.h"
#include "../include/menueform.h"

#include <QToolBar>





QWidget *g_currMenu = nullptr;
QStringList g_langList;




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currMenue(nullptr)
    , settings(nullptr)
{
    ui->setupUi(this);

    QIcon trnslt_Ic("images\\translate.png");
    QIcon castom_Ic("images\\castom_trans.png");
    QIcon rubish_Ic("images\\rubish.png");
    QIcon sttngs_Ic("images\\settings.png");

    QToolBar *bar = addToolBar("Panel");

    QAction *trnslt_act = bar->addAction(trnslt_Ic, "Translate file");
    QAction *castom_act = bar->addAction(castom_Ic, "Update file");
    bar->addSeparator();
    QAction *sttngs_act = bar->addAction(sttngs_Ic, "Settings");
    QAction *rubish_act = bar->addAction(rubish_Ic, "Delete");

    connect(trnslt_act, &QAction::triggered, this, &MainWindow::translateFile);
    connect(castom_act, &QAction::triggered, this, &MainWindow::updateFile);
    connect(sttngs_act, &QAction::triggered, this, &MainWindow::settingsDialog);
    connect(rubish_act, &QAction::triggered, this, &MainWindow::deleteMenu);

    settings = new Settings;


    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("dataBase/Languages.db");

    db.open();

    query = new QSqlQuery(db);
    query->exec("SELECT * FROM langs");

    while(query->next())
        g_langList << query->value(0).toString();


    query->exec("SELECT key FROM langs WHERE lang = \"English\"");
    query->next();

    db.close();


    statusBar()->showMessage("Ready");
}

MainWindow::~MainWindow()
{
    delete settings;
    delete currMenue;
    delete ui;
}




// Slots:

void MainWindow::translateFile()
{
    deleteMenu();

    MenueForm *menu = new MenueForm(this);

    menu->setSettingsPtr(settings);
    menu->delSettingsBtn();
    setCentralWidget(menu);

    g_currMenu = menu;

    statusBar()->showMessage("Translate files menu");
}

void MainWindow::updateFile()
{
    deleteMenu();

    MenueForm *menu = new MenueForm(this);

    menu->setSettingsPtr(settings);
    setCentralWidget(menu);

    g_currMenu = menu;

    statusBar()->showMessage("Uniqueness files menu");
}




void MainWindow::settingsDialog()
{
    settings->exec();
}

void MainWindow::deleteMenu()
{
    delete g_currMenu;
    g_currMenu = nullptr;

    statusBar()->showMessage("Ready");
}
