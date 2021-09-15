#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

char typeStr[20][20] = { "None", "MessageBoxA", "MessageBoxW",
"CreateFile", "WriteFile", "ReadFile", "HeapCreate",
"HeapDestroy", "HeapFree", "RegCreateKeyEx", "RegSetValueEx",
"RegGetValue", "RegCloseKey", "RegOpenKeyEx", "RegDeleteValue",
"socket", "bind", "send", "recv" };

info recvInfo;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUI() {
    ui->infoButton->setIcon(QIcon(":/icons/icons/safe.svg"));
    connect(&threadA, SIGNAL(newInfo(QString, int)), this, SLOT(on_ThreadA_newInfo(QString, int)));
    connect(&threadA, SIGNAL(newProcessModules(QString)), this, SLOT(on_ThreadA_newProcessModules(QString)));
    connect(&threadA, SIGNAL(newProcessPriority(QString)), this, SLOT(on_ThreadA_newProcessPriority(QString)));
    connect(&threadA, SIGNAL(newProcessID(QString)), this, SLOT(on_ThreadA_newProcessID(QString)));
    connect(&threadA, SIGNAL(newProcessName(QString)), this, SLOT(on_ThreadA_newProcessName(QString)));
    connect(&threadA, SIGNAL(newInfo()), this, SLOT(on_ThreadA_newInfo()));
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if (threadA.isRunning()) {
        threadA.stopThread();
        threadA.wait();
    }
    event->accept();
}

void MainWindow::on_openTargetFileButton_pressed()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("open wanted file"), "./", tr("Wanted files(*.txt *.exe);;All files (*.*)"));

    if (fileName.isEmpty())
    {
        MessageBoxA(NULL, "Can't open the empty file!!!", "warning!", 2);
        return;
    }
    else
    {
        ui->targetFileText->setText(fileName);
    }
}

void MainWindow::on_startButton_pressed()
{
    QByteArray temp = ui->targetFileText->toPlainText().toLatin1();
    threadA.init(temp.data());
    threadA.start();
}

void MainWindow::on_cleanButton_pressed()
{
    ui->treeInfo->clear();
    ui->info->clear();
    ui->processModules->clear();
    ui->processID->clear();
    ui->processName->clear();
    ui->processPriority->clear();
    ui->targetFileText->clear();
    if (threadA.isRunning()) {
        threadA.stopThread();
        threadA.wait();
    }
}

void MainWindow::on_ThreadA_newInfo() {
    QTreeWidgetItem* item = new QTreeWidgetItem();
    char temp[128] = "";
    sprintf(temp, "%d-%d-%d %-02d:%-02d  (%-d.%-ds)",
        recvInfo.st.wYear, recvInfo.st.wMonth, recvInfo.st.wDay,
        recvInfo.st.wHour, recvInfo.st.wMinute, recvInfo.st.wSecond,
        recvInfo.st.wMilliseconds);
    item->setData(0, 0, typeStr[recvInfo.type]);
    item->setData(1, 0, temp);
    for (int i = 0; i < recvInfo.argNum; i++) {
        QTreeWidgetItem* item2 = new QTreeWidgetItem();
        item2->setData(0, 0, recvInfo.argName[i]);
        item2->setData(1, 0, recvInfo.argValue[i]);
        item->addChild(item2);
    }
    ui->treeInfo->addTopLevelItem(item);
}

void MainWindow::on_ThreadA_newProcessName(QString str) {
    ui->processName->setText(str);
}

void MainWindow::on_ThreadA_newProcessID(QString str) {
    ui->processID->setText(str);
}

void MainWindow::on_ThreadA_newProcessPriority(QString str) {
    ui->processPriority->setText(str);
}

void MainWindow::on_ThreadA_newProcessModules(QString str) {
    ui->processModules->setText(str);
}

void MainWindow::on_ThreadA_newInfo(QString str, int status) {
    ui->info->append(str);
    if (status == 2) {
        ui->infoButton->setIcon(QIcon(":/icons/icons/error.svg"));
    }
    else if (status == 1) {
        ui->infoButton->setIcon(QIcon(":/icons/icons/warning.svg"));
    }
    else {
        ui->infoButton->setIcon(QIcon(":/icons/icons/safe.svg"));
    }
}

void MainWindow::on_output_pressed()
{
    // writeLog.txt路径 E:\\TestInitialNullForStudent\\InjectDll\\Debug\\writeLog.txt
    STARTUPINFOA startupInfo = { 0 };
    PROCESS_INFORMATION  processInformation = { 0 };
    BOOL bSuccess = CreateProcessA("C:\\Program\40Files\40(x86)\\Notepad++\\notepad++.exe", NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &startupInfo, &processInformation);
}

void MainWindow::on_messageBoxButton_pressed()
{
    // MessageBox.exe路径
    qDebug()<<"123";
    QByteArray temp = "E:/TestInitialNullForStudent/InjectDll/Debug/MessageBox.exe";
    threadA.init(temp.data());
    threadA.start();
}

void MainWindow::on_heapButton_pressed()
{
    // Heap.exe路径
    QByteArray temp = "E:/TestInitialNullForStudent/InjectDll/Debug/Heap.exe";
    threadA.init(temp.data());
    threadA.start();
}

void MainWindow::on_fileButton_pressed()
{
    // File.exe路径
    QByteArray temp = "E:/TestInitialNullForStudent/InjectDll/Debug/File.exe";
    threadA.init(temp.data());
    threadA.start();
}

void MainWindow::on_registryButton_pressed()
{
    // Resgistry.exe路径
    QByteArray temp = "E:/TestInitialNullForStudent/InjectDll/Debug/Registry.exe";
    threadA.init(temp.data());
    threadA.start();
}

void MainWindow::on_socketButton_pressed()
{
    // Socket.exe路径
    QByteArray temp = "E:/TestInitialNullForStudent/InjectDll/Debug/Server.exe";
    threadA.init(temp.data());
    threadA.start();
}

void MainWindow::on_dangerButton_pressed()
{
    // Danger.exe路径
    QByteArray temp = "E:/TestInitialNullForStudent/InjectDll/Debug/Danger.exe";
    threadA.init(temp.data());
    threadA.start();
}
