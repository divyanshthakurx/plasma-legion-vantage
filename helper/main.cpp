#include <QCoreApplication>
#include <QDBusConnection>
#include "legionhelper.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    LegionHelper helper;
    
    // Register daemon on the session bus
    QDBusConnection dbus = QDBusConnection::sessionBus();
    dbus.registerObject("/LegionHelper", &helper, QDBusConnection::ExportAllSlots);
    dbus.registerService("org.kde.legionvantage.helper");

    return app.exec();
}