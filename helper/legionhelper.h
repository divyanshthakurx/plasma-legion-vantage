#ifndef LEGIONHELPER_H
#define LEGIONHELPER_H

#include <QObject>
#include <QString>

class LegionHelper : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.kde.legionvantage.helper")

public:
    explicit LegionHelper(QObject *parent = nullptr);

public Q_SLOTS:
    bool setConservationMode(bool enable);

private:
    QString m_devicePath;
};

#endif