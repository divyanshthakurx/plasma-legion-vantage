#include <QCoreApplication>
#include <QDBusConnection>
#include "legionhelper.h"

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    LegionHelper helper;
    
    QDBusConnection dbus = QDBusConnection::sessionBus();
    dbus.registerObject(QStringLiteral("/LegionHelper"), &helper, QDBusConnection::ExportAllSlots);
    dbus.registerService(QStringLiteral("org.kde.legionvantage.helper"));

    return app.exec();
}