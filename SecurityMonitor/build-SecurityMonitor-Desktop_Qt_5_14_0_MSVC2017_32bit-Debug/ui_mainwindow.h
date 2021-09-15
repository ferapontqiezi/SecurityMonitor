/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout;
    QPushButton *openTargetFileButton;
    QPushButton *startButton;
    QTextEdit *targetFileText;
    QPushButton *cleanButton;
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_3;
    QLabel *label_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *processName;
    QLabel *processPriority;
    QLabel *processID;
    QLabel *label_4;
    QTextEdit *processModules;
    QPushButton *infoButton;
    QTextEdit *info;
    QTreeWidget *treeInfo;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_5;
    QPushButton *output;
    QPushButton *messageBoxButton;
    QPushButton *heapButton;
    QPushButton *fileButton;
    QPushButton *registryButton;
    QPushButton *socketButton;
    QPushButton *dangerButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1186, 784);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/icons/SecurityMonitor.svg"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setIconSize(QSize(30, 30));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        openTargetFileButton = new QPushButton(centralwidget);
        openTargetFileButton->setObjectName(QString::fromUtf8("openTargetFileButton"));
        QFont font;
        font.setFamily(QString::fromUtf8("Times New Roman"));
        font.setPointSize(11);
        font.setBold(false);
        font.setWeight(50);
        openTargetFileButton->setFont(font);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/icons/OPEN.svg"), QSize(), QIcon::Normal, QIcon::Off);
        openTargetFileButton->setIcon(icon1);

        horizontalLayout->addWidget(openTargetFileButton);

        startButton = new QPushButton(centralwidget);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Times New Roman"));
        font1.setPointSize(12);
        font1.setBold(false);
        font1.setWeight(50);
        startButton->setFont(font1);
        startButton->setContextMenuPolicy(Qt::DefaultContextMenu);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/icons/start.svg"), QSize(), QIcon::Normal, QIcon::Off);
        startButton->setIcon(icon2);
        startButton->setIconSize(QSize(16, 16));

        horizontalLayout->addWidget(startButton);

        targetFileText = new QTextEdit(centralwidget);
        targetFileText->setObjectName(QString::fromUtf8("targetFileText"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(targetFileText->sizePolicy().hasHeightForWidth());
        targetFileText->setSizePolicy(sizePolicy);
        QFont font2;
        font2.setFamily(QString::fromUtf8("Times New Roman"));
        font2.setPointSize(12);
        targetFileText->setFont(font2);

        horizontalLayout->addWidget(targetFileText);

        cleanButton = new QPushButton(centralwidget);
        cleanButton->setObjectName(QString::fromUtf8("cleanButton"));
        cleanButton->setFont(font2);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/icons/clean.svg"), QSize(), QIcon::Normal, QIcon::Off);
        cleanButton->setIcon(icon3);
        cleanButton->setIconSize(QSize(18, 18));

        horizontalLayout->addWidget(cleanButton);


        verticalLayout_4->addLayout(horizontalLayout);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));

        verticalLayout_4->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(10);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font2);

        verticalLayout->addWidget(label);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font2);

        verticalLayout->addWidget(label_3);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font2);

        verticalLayout->addWidget(label_2);


        horizontalLayout_2->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        processName = new QLabel(centralwidget);
        processName->setObjectName(QString::fromUtf8("processName"));
        processName->setFont(font2);

        verticalLayout_2->addWidget(processName);

        processPriority = new QLabel(centralwidget);
        processPriority->setObjectName(QString::fromUtf8("processPriority"));
        processPriority->setFont(font2);

        verticalLayout_2->addWidget(processPriority);

        processID = new QLabel(centralwidget);
        processID->setObjectName(QString::fromUtf8("processID"));
        processID->setFont(font2);

        verticalLayout_2->addWidget(processID);


        horizontalLayout_2->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout_2);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font2);

        verticalLayout_3->addWidget(label_4);

        processModules = new QTextEdit(centralwidget);
        processModules->setObjectName(QString::fromUtf8("processModules"));
        processModules->setFont(font2);

        verticalLayout_3->addWidget(processModules);

        infoButton = new QPushButton(centralwidget);
        infoButton->setObjectName(QString::fromUtf8("infoButton"));
        infoButton->setFont(font2);

        verticalLayout_3->addWidget(infoButton);

        info = new QTextEdit(centralwidget);
        info->setObjectName(QString::fromUtf8("info"));
        info->setFont(font2);

        verticalLayout_3->addWidget(info);


        horizontalLayout_3->addLayout(verticalLayout_3);


        horizontalLayout_4->addLayout(horizontalLayout_3);

        treeInfo = new QTreeWidget(centralwidget);
        treeInfo->setObjectName(QString::fromUtf8("treeInfo"));
        treeInfo->setFont(font2);

        horizontalLayout_4->addWidget(treeInfo);


        verticalLayout_4->addLayout(horizontalLayout_4);


        horizontalLayout_6->addLayout(verticalLayout_4);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_5 = new QVBoxLayout(groupBox);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        output = new QPushButton(groupBox);
        output->setObjectName(QString::fromUtf8("output"));
        output->setFont(font2);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/icons/start (1).svg"), QSize(), QIcon::Normal, QIcon::Off);
        output->setIcon(icon4);
        output->setIconSize(QSize(18, 18));

        verticalLayout_5->addWidget(output);

        messageBoxButton = new QPushButton(groupBox);
        messageBoxButton->setObjectName(QString::fromUtf8("messageBoxButton"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Times New Roman"));
        font3.setPointSize(10);
        messageBoxButton->setFont(font3);
        messageBoxButton->setIcon(icon4);
        messageBoxButton->setIconSize(QSize(18, 18));

        verticalLayout_5->addWidget(messageBoxButton);

        heapButton = new QPushButton(groupBox);
        heapButton->setObjectName(QString::fromUtf8("heapButton"));
        heapButton->setFont(font2);
        heapButton->setIcon(icon4);
        heapButton->setIconSize(QSize(18, 18));

        verticalLayout_5->addWidget(heapButton);

        fileButton = new QPushButton(groupBox);
        fileButton->setObjectName(QString::fromUtf8("fileButton"));
        fileButton->setFont(font2);
        fileButton->setIcon(icon4);
        fileButton->setIconSize(QSize(18, 18));

        verticalLayout_5->addWidget(fileButton);

        registryButton = new QPushButton(groupBox);
        registryButton->setObjectName(QString::fromUtf8("registryButton"));
        registryButton->setFont(font2);
        registryButton->setIcon(icon4);
        registryButton->setIconSize(QSize(18, 18));

        verticalLayout_5->addWidget(registryButton);

        socketButton = new QPushButton(groupBox);
        socketButton->setObjectName(QString::fromUtf8("socketButton"));
        socketButton->setFont(font2);
        socketButton->setIcon(icon4);
        socketButton->setIconSize(QSize(18, 18));

        verticalLayout_5->addWidget(socketButton);

        dangerButton = new QPushButton(groupBox);
        dangerButton->setObjectName(QString::fromUtf8("dangerButton"));
        dangerButton->setFont(font2);
        dangerButton->setIcon(icon4);
        dangerButton->setIconSize(QSize(18, 18));

        verticalLayout_5->addWidget(dangerButton);


        horizontalLayout_6->addWidget(groupBox);


        gridLayout->addLayout(horizontalLayout_6, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1186, 29));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);
        QObject::connect(cleanButton, SIGNAL(pressed()), treeInfo, SLOT(clear()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "SecurityMonitor", nullptr));
        openTargetFileButton->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\207\344\273\266", nullptr));
        startButton->setText(QCoreApplication::translate("MainWindow", "\345\220\257\345\212\250", nullptr));
        cleanButton->setText(QCoreApplication::translate("MainWindow", "\345\244\215\344\275\215", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\350\277\233\347\250\213\345\220\215\347\247\260\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\350\277\233\347\250\213\347\255\211\347\272\247\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\350\277\233\347\250\213ID: ", nullptr));
        processName->setText(QString());
        processPriority->setText(QString());
        processID->setText(QString());
        label_4->setText(QCoreApplication::translate("MainWindow", "\350\277\233\347\250\213\346\250\241\345\235\227\357\274\232 ", nullptr));
        infoButton->setText(QCoreApplication::translate("MainWindow", "\345\256\211\345\205\250\344\277\241\346\201\257", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = treeInfo->headerItem();
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("MainWindow", "\345\261\236\346\200\247", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("MainWindow", "API                                                                   ", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "FuncBox", nullptr));
        output->setText(QCoreApplication::translate("MainWindow", "\346\227\245\345\277\227", nullptr));
        messageBoxButton->setText(QCoreApplication::translate("MainWindow", "MessageBox", nullptr));
        heapButton->setText(QCoreApplication::translate("MainWindow", "Heap", nullptr));
        fileButton->setText(QCoreApplication::translate("MainWindow", "File", nullptr));
        registryButton->setText(QCoreApplication::translate("MainWindow", "Registry", nullptr));
        socketButton->setText(QCoreApplication::translate("MainWindow", "Socket", nullptr));
        dangerButton->setText(QCoreApplication::translate("MainWindow", "Danger", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
