#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QThread>
#include <QProcess>
#include <QCloseEvent>
#include <string>
#include <unordered_set>
#include <thread>
#include <Windows.h>
#include "Psapi.h"

#pragma comment(lib,"User32.lib")

#define NONE 0
#define MESSAGEBOXA 1
#define MESSAGEBOXW 2
#define CREATEFILE 3
#define WRITEFILE 4
#define READFILE 5
#define HEAPCREATE 6
#define HEAPDESTROY 7
#define HEAPFREE 8
#define REGCREATEKEYEX 9
#define REGSETVALUEEX 10
#define REGGETVALUE 11
#define REGCLOSEKEY 12
#define REGOPENKEYEX 13
#define REGDELETEVALUE 14
#define ASOCKET 15
#define BIND 16
#define SEND 17
#define RECV 18

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


struct info {
    int type, argNum;
    SYSTEMTIME st;
    char argName[10][50] = { 0 };
    char argValue[10][50] = { 0 };
};

class myThreadA :public QThread {
    Q_OBJECT
private:
    bool running;
    char filePath[256], fileName[128];
    unordered_set<int> heapSet;
    unordered_set<string> folderSet;

protected:
    void run();

public:
    void init(char * path);
    void getFileName(char *filePath, char *fileName);
    void stopThread();
    int GetProcessPriority(HANDLE hProcess);
    void checkFunc();
    void createFileCheck();
    void getLastFolder(char* filePath, string & folder);

signals:
    void newValue(QString str);
    void newInfo();
    void newProcessName(QString str);
    void newProcessID(QString str);
    void newProcessPriority(QString str);
    void newProcessModules(QString str);
    void newInfo(QString str, int status);
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    myThreadA threadA;

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_openTargetFileButton_pressed();

    void on_startButton_pressed();

    void on_cleanButton_pressed();

    void on_ThreadA_newInfo();

    void on_ThreadA_newProcessName(QString str);

    void on_ThreadA_newProcessID(QString str);

    void on_ThreadA_newProcessPriority(QString str);

    void on_ThreadA_newProcessModules(QString str);

    void on_ThreadA_newInfo(QString str, int status);

    void on_output_pressed();

    void on_messageBoxButton_pressed();

    void on_heapButton_pressed();

    void on_fileButton_pressed();

    void on_registryButton_pressed();

    void on_socketButton_pressed();

    void on_dangerButton_pressed();


public:
    MainWindow(QWidget *parent = nullptr);
    void initUI();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
