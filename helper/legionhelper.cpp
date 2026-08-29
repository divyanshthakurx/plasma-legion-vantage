#include "legionhelper.h"
#include <QDir>
#include <QFile>
#include <QTextStream>

LegionHelper::LegionHelper(QObject *parent) : QObject(parent) {
    QDir dir(QStringLiteral("/sys/bus/platform/drivers/ideapad_acpi/"));
    QStringList subDirs = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    
    for (const QString &subDir : subDirs) {
        if (subDir.startsWith(QStringLiteral("VPC2004"))) {
            m_devicePath = dir.absoluteFilePath(subDir);
            break;
        }
    }
}

bool LegionHelper::setConservationMode(bool enable) {
    if (m_devicePath.isEmpty()) return false;
    
    QFile file(m_devicePath + QStringLiteral("/conservation_mode"));
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << (enable ? QStringLiteral("1") : QStringLiteral("0"));
        file.close();
        return true;
    }
    return false;
}