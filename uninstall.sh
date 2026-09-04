#!/usr/bin/env bash
# Remove plasma-legion-vantage system-wide.
set -euo pipefail

UDEV_DEST="/etc/udev/rules.d/99-lenovo-legion.rules"

if [[ -f "$UDEV_DEST" ]]; then
    echo ">> Removing udev rules"
    sudo rm -f "$UDEV_DEST"
    sudo udevadm control --reload-rules
    sudo udevadm trigger
fi

if command -v kpackagetool6 >/dev/null; then
    echo ">> Removing Plasmoid"
    kpackagetool6 -r org.kde.legionvantage || true
fi

cat <<EOF

================================================================
  Uninstallation complete.

  Note: your user remains in the 'plugdev' group. Remove manually if desired:
    sudo gpasswd -d \$USER plugdev
================================================================
EOF
