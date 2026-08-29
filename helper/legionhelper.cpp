#include "legionhelper.h"
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QDebug>

LegionHelper::LegionHelper(QObject *parent) : QObject(parent) {
    m_devicePath = findDevicePath();
}

QString LegionHelper::findDevicePath() {
    QDir dir("/sys/bus/platform/drivers/ideapad_acpi/");
    QStringList subDirs = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    
    for (const QString &subDir : subDirs) {
        if (subDir.startsWith("VPC2004")) {
            return dir.absoluteFilePath(subDir);
        }
    }
    return QString(); // Fallback if module isn't loaded
}

bool LegionHelper::getConservationMode() {
    if (m_devicePath.isEmpty()) return false;
    
    QFile file(m_devicePath + "/conservation_mode");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString val = in.readLine().trimmed();
        file.close();
        return (val == "1");
    }
    return false;
}

bool LegionHelper::setConservationMode(bool enable) {
    if (m_devicePath.isEmpty()) return false;
    
    // In a full implementation, you would trigger Polkit verification here
    // For now, we write directly assuming the helper was started with permissions.
    QFile file(m_devicePath + "/conservation_mode");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << (enable ? "1" : "0");
        file.close();
        return true;
    }
    return false;
}