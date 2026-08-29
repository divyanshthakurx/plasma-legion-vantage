#include <QCoreApplication>
#include <QDBusConnection>
#include <QDebug>
#include "legionhelper.h"

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    LegionHelper helper;
    
    // FIX: Moved to systemBus so it can write to root /sys/ files
    QDBusConnection dbus = QDBusConnection::systemBus();
    
    if (!dbus.registerObject(QStringLiteral("/LegionHelper"), &helper, QDBusConnection::ExportAllSlots)) {
        qWarning() << "Failed to register DBus object";
    }
    if (!dbus.registerService(QStringLiteral("org.kde.legionvantage.helper"))) {
        qWarning() << "Failed to register DBus service";
    }

    return app.exec();
}