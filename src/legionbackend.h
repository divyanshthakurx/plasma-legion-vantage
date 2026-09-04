#ifndef LEGIONBACKEND_H
#define LEGIONBACKEND_H

#include <QObject>
#include <QString>
#include <QtQml/qqmlregistration.h>

/**
 * LegionBackend — user-space bridge to Lenovo laptop hardware.
 *
 * Reads and writes sysfs files exposed by the ideapad_acpi,
 * thinkpad_acpi, and ACPI platform_profile drivers. Hardware access
 * is gated by the udev rule in udev/99-lenovo-legion.rules (plugdev
 * group); this class performs no privilege escalation and runs in
 * the Plasma applet's own process.
 *
 * All methods are safe to call on non-Lenovo hardware: they return
 * sensible defaults and emit a hardwareAvailable property so the UI
 * can show an explanatory message instead of silently failing.
 */
class LegionBackend : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

    Q_PROPERTY(bool hardwareAvailable READ hardwareAvailable NOTIFY hardwareAvailableChanged)
    Q_PROPERTY(bool conservationMode READ conservationMode WRITE setConservationMode NOTIFY conservationModeChanged)
    Q_PROPERTY(QString conservationModePath READ conservationModePath CONSTANT)
    Q_PROPERTY(QString lastError READ lastError NOTIFY lastErrorChanged)

public:
    explicit LegionBackend(QObject *parent = nullptr);

    bool hardwareAvailable() const;
    bool conservationMode() const;
    QString conservationModePath() const;
    QString lastError() const;

    void setConservationMode(bool enabled);

    Q_INVOKABLE void refresh();

signals:
    void hardwareAvailableChanged();
    void conservationModeChanged();
    void lastErrorChanged();

private:
    void discoverPaths();
    bool writeSysfs(const QString &path, const QString &value);

    QString m_conservationModePath;
    bool m_hardwareAvailable = false;
    bool m_conservationMode = false;
    QString m_lastError;
};

#endif
