#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->setWindowIcon(QIcon(":new/prefix1/R-C.ico"));

    this->setWindowFlags(Qt::WindowCloseButtonHint);

    ui->setupUi(this);
    QCheckBox* checkBox = new QCheckBox(this);
    checkBox->setCheckState(Qt::Unchecked);
    checkBox->setGeometry(10, 0, 300, 75);
    checkBox->setText(tr("自启动以防止设置发生更改（Ctrl+A）"));
    checkBox->setToolTip(tr("绝大多数情况不会复发，非必要不勾选"));
    checkBox->setShortcut(Qt::CTRL + Qt::Key_A);
    connect(checkBox, SIGNAL(stateChanged(int)), this, SLOT(onClickCheckbox(int)));

    QLabel* label = new QLabel(this);
    QImage jpg("lock.jpg");
    QImage scalimg = jpg.scaled(225, 225, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    label->setPixmap(QPixmap::fromImage(scalimg));
    label->setGeometry(300, 0, this->width(), this->height());

    QPushButton* button1 = new QPushButton(this);
    button1->setText(tr("一键禁止（Ctrl+B）"));
    button1->setShortcut(Qt::CTRL + Qt::Key_B);
    button1->setGeometry(10, 60, 300, 125);
    button1->resize(150, 40);
    connect(button1, SIGNAL(clicked()), this, SLOT(onClickButton1()));

    QPushButton* button2 = new QPushButton(this);
    button2->setText(tr("退出（Ctrl+E）"));
    button2->setShortcut(Qt::CTRL + Qt::Key_E);
    button2->setGeometry(10, 120, 300, 125);
    button2->resize(150, 40);
    connect(button2, SIGNAL(clicked()), this, SLOT(onClickButton2()));

    QPushButton* button3 = new QPushButton(this);
    button3->setText(tr("帮助（Ctrl+H）"));
    button3->setShortcut(Qt::CTRL + Qt::Key_H);
    button3->setGeometry(10, 180, 300, 125);
    button3->resize(150, 40);
    connect(button3, SIGNAL(clicked()), this, SLOT(onClickButton3()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onClickButton1() {
    QSettings *set = new QSettings("HKEY_LOCAL_MACHINE\\SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate\\AU", QSettings::NativeFormat);
    set->setValue("NoAutoUpdate", 1);
    delete set;

    /*char *szSubKey = "SOFTWARE\\Policies\\Microsoft\\Windows";
    HKEY hKey;
    RegOpenKeyExA(HKEY_LOCAL_MACHINE, szSubKey, 0, KEY_ALL_ACCESS, &hKey);
    RegCreateKeyA(hKey, "WindowsUpdate", &hKey );
    RegCloseKey(hKey);

    char *sz1 = "SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate";
    RegOpenKeyExA(HKEY_LOCAL_MACHINE, sz1, 0, KEY_ALL_ACCESS, &hKey);
    RegCreateKeyA(hKey, "AU", &hKey );
    //RegSetValueExA(hKey, "NoAutoUpdate", 0, REG_SZ, (BYTE *)pathName, strlen(pathName));
    RegCloseKey(hKey);

    char *sz2 = "SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate\\AU";
    RegOpenKeyExA(HKEY_LOCAL_MACHINE, sz2, 0, KEY_ALL_ACCESS, &hKey);
    DWORD d = 1;
    RegSetValueExA(hKey, "NoAutoUpdate", 0, REG_DWORD, (BYTE*)&d, sizeof(DWORD));
    RegCloseKey(hKey);*/

    QMessageBox::StandardButton re;
    re = QMessageBox::information(this, tr("完成"), tr("自动更新已禁用！\n点击确定重新启动以使设置生效，或点击取消手动重启。"), QMessageBox::Ok | QMessageBox::Cancel);
    if(re == QMessageBox::Ok) {
        system("shutdown -r -t 3");
        exit(0);
    } else {
        exit(0);
    }

    return;
}

void MainWindow::onClickButton2() {
    exit(0);
}

void MainWindow::onClickButton3() {
    ShellExecuteA(NULL, "open", "help.html", NULL, NULL, SW_SHOWNORMAL);
    return;
}

void MainWindow::onClickCheckbox(int argc) {
    char pathName[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, pathName);
    sprintf(pathName, "%s\\", pathName);
    strcat(pathName, "FreezeLockCmd.exe");
    QString c("\"");
    if(argc == Qt::Checked) {
        QSettings *set = new QSettings("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
        QSettings *set0 = new QSettings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
        set->setValue("NoAutoUpdate", c + pathName + c);
        set0->setValue("NoAutoUpdate", c + pathName + c);
        delete set;
        delete set0;
    } else if(argc == Qt::Unchecked) {
        //std::cout<<0<<std::endl;
        QSettings *set = new QSettings("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
        QSettings *set0 = new QSettings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
        set->remove("NoAutoUpdate");
        set0->remove("NoAutoUpdate");
        delete set;
        delete set0;
    }
    return;
}

