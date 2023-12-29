
#include <QSettings>
int main(int argc, char *argv[])
{
    QSettings *set = new QSettings("HKEY_LOCAL_MACHINE\\SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate\\AU", QSettings::NativeFormat);
    set->setValue("NoAutoUpdate", 1);
    delete set;
    return 0;
}
