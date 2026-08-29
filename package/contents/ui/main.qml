import QtQuick
import QtQuick.Layouts
import org.kde.plasma.plasmoid
import org.kde.kirigami as Kirigami
import org.kde.plasma.components as PlasmaComponents

PlasmoidItem {
    id: root

    // Tell Plasma to show the full UI by default when testing in the viewer
    preferredRepresentation: fullRepresentation

    compactRepresentation: Item {
        Kirigami.Icon {
            anchors.fill: parent
            source: "preferences-system-power-management"
        }
        
        // This makes the icon clickable when you put it in your real taskbar
        MouseArea {
            anchors.fill: parent
            onClicked: root.expanded = !root.expanded
        }
    }

    fullRepresentation: Item {
        Layout.preferredWidth: 350
        Layout.preferredHeight: 120

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: Kirigami.Units.largeSpacing

            PlasmaComponents.Label {
                text: "Legion Vantage"
                font.pixelSize: Kirigami.Theme.defaultFont.pixelSize * 1.5
                font.weight: Font.Bold
            }

            RowLayout {
                Layout.fillWidth: true
                
                Kirigami.Icon {
                    source: "battery-charging"
                    implicitWidth: Kirigami.Units.iconSizes.medium
                    implicitHeight: Kirigami.Units.iconSizes.medium
                }
                
                ColumnLayout {
                    Layout.fillWidth: true
                    PlasmaComponents.Label { text: "Conservation Mode" }
                    PlasmaComponents.Label {
                        text: "Limits charge to 80% to preserve battery."
                        font.pixelSize: 12
                        opacity: 0.7
                    }
                }

                PlasmaComponents.Switch {
                    id: conservationToggle
                    onCheckedChanged: {
                        console.log("Switch toggled:", checked)
                    }
                }
            }
            
            Item { Layout.fillHeight: true }
        }
    }
}