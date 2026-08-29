#ifndef LEGIONHELPER_H
#define LEGIONHELPER_H

#include <QObject>
#include <QString>
#include <QDBusContext>

class LegionHelper : public QObject, protected QDBusContext
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.kde.legionvantage.helper")

public:
    explicit LegionHelper(QObject *parent = nullptr);

public slots:
    // Read current state
    bool getConservationMode();
    
    // Write new state
    bool setConservationMode(bool enable);

private:
    QString findDevicePath();
    QString m_devicePath;
};

#endif // LEGIONHELPER_H