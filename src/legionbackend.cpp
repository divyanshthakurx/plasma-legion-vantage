#include "legionbackend.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QDebug>

namespace {
constexpr const char *kIdeapadDriver = "/sys/bus/platform/drivers/ideapad_acpi";
constexpr const char *kThinkpadDriver = "/sys/bus/platform/drivers/thinkpad_acpi";

// Try multiple well-known device IDs the Lenovo kernel drivers expose.
const QStringList kDeviceIdPrefixes = {
    QStringLiteral("VPC2004"),  // IdeaPad / Legion (most common)
    QStringLiteral("VPC2003"),
};

QString findFirstAvailable(const QString &dir, const QStringList &prefixes)
{
    QDir d(dir);
    if (!d.exists()) {
        return {};
    }
    const auto entries = d.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    for (const QString &entry : entries) {
        for (const QString &prefix : prefixes) {
            if (entry.startsWith(prefix)) {
                return d.absoluteFilePath(entry);
            }
        }
    }
    return {};
}
} // namespace

LegionBackend::LegionBackend(QObject *parent)
    : QObject(parent)
{
    discoverPaths();
    if (m_hardwareAvailable) {
        refresh();
    }
}

void LegionBackend::discoverPaths()
{
    // Look in ideapad_acpi first (covers IdeaPad/Legion), then thinkpad_acpi.
    QString deviceDir = findFirstAvailable(QString::fromLatin1(kIdeapadDriver), kDeviceIdPrefixes);
    if (deviceDir.isEmpty()) {
        deviceDir = findFirstAvailable(QString::fromLatin1(kThinkpadDriver), kDeviceIdPrefixes);
    }

    if (!deviceDir.isEmpty()) {
        const QString candidate = deviceDir + QStringLiteral("/conservation_mode");
        if (QFileInfo::exists(candidate)) {
            m_conservationModePath = candidate;
        }
    }

    m_hardwareAvailable = !m_conservationModePath.isEmpty();

    if (!m_hardwareAvailable) {
        m_lastError = QStringLiteral(
            "Lenovo sysfs nodes not found. This applet targets Lenovo IdeaPad/Legon/ThinkPad "
            "laptops with the ideapad_acpi or thinkpad_acpi kernel driver loaded.");
    } else {
        m_lastError.clear();
    }

    emit hardwareAvailableChanged();
    emit lastErrorChanged();
}

bool LegionBackend::hardwareAvailable() const
{
    return m_hardwareAvailable;
}

QString LegionBackend::conservationModePath() const
{
    return m_conservationModePath;
}

QString LegionBackend::lastError() const
{
    return m_lastError;
}

bool LegionBackend::conservationMode() const
{
    return m_conservationMode;
}

void LegionBackend::setConservationMode(bool enabled)
{
    if (!m_hardwareAvailable) {
        return;
    }
    if (!writeSysfs(m_conservationModePath, enabled ? QStringLiteral("1") : QStringLiteral("0"))) {
        m_lastError = QStringLiteral("Failed to write conservation_mode. "
                                     "Check that the 'plugdev' udev rule is installed and "
                                     "you are in the 'plugdev' group (log out/in).");
        emit lastErrorChanged();
        return;
    }
    // Re-read from sysfs to confirm and to catch any driver-side rejection.
    refresh();
}

void LegionBackend::refresh()
{
    if (!m_hardwareAvailable) {
        return;
    }

    QFile file(m_conservationModePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        m_lastError = QStringLiteral("Cannot read %1").arg(m_conservationModePath);
        emit lastErrorChanged();
        return;
    }

    bool ok = false;
    const int value = QTextStream(&file).readAll().trimmed().toInt(&ok);
    file.close();

    if (!ok) {
        m_lastError = QStringLiteral("Unexpected content in %1").arg(m_conservationModePath);
        emit lastErrorChanged();
        return;
    }

    const bool newState = (value != 0);
    if (newState != m_conservationMode) {
        m_conservationMode = newState;
        emit conservationModeChanged();
    }

    if (!m_lastError.isEmpty()) {
        m_lastError.clear();
        emit lastErrorChanged();
    }
}

bool LegionBackend::writeSysfs(const QString &path, const QString &value)
{
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "LegionBackend: cannot open" << path << "for writing:" << file.errorString();
        return false;
    }
    const qint64 written = file.write(value.toUtf8());
    if (written != value.toUtf8().size()) {
        qWarning() << "LegionBackend: short write to" << path;
        return false;
    }
    file.close();
    return true;
}
