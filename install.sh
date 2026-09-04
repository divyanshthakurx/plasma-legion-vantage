#!/usr/bin/env bash
# Install plasma-legion-vantage system-wide.
# - Installs udev rules for hardware access (no root helper required)
# - Adds the current user to the 'plugdev' group
# - Builds and installs the Plasmoid via kpackagetool6

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PACKAGE_DIR="$SCRIPT_DIR/package"
UDEV_SRC="$SCRIPT_DIR/udev/99-lenovo-legion.rules"
UDEV_DEST="/etc/udev/rules.d/99-lenovo-legion.rules"

# --- 1. udev rules ---
if [[ -f "$UDEV_SRC" ]]; then
    echo ">> Installing udev rules -> $UDEV_DEST"
    sudo install -m 0644 "$UDEV_SRC" "$UDEV_DEST"
    sudo udevadm control --reload-rules
    sudo udevadm trigger
else
    echo "!! udev rule not found at $UDEV_SRC" >&2
    exit 1
fi

# --- 2. plugdev group ---
if getent group plugdev >/dev/null; then
    echo ">> Adding user '$USER' to 'plugdev' group"
    sudo usermod -aG plugdev "$USER"
    echo "   (log out and back in for the group change to take effect)"
else
    echo "!! 'plugdev' group not found on this system" >&2
    echo "   Create it manually: sudo groupadd plugdev" >&2
fi

# --- 3. Build & install the Plasmoid ---
if command -v kpackagetool6 >/dev/null; then
    echo ">> Installing Plasmoid for the current user via kpackagetool6"
    kpackagetool6 -i "$PACKAGE_DIR"
else
    echo "!! kpackagetool6 not found. Install plasma6-sdk or equivalent." >&2
    exit 1
fi

cat <<EOF

================================================================
  Installation complete.

  Next steps:
    1. Log out and back in (so 'plugdev' group takes effect).
    2. Right-click your panel -> Add Widgets... -> search "Legion Vantage".
    3. Conservation mode is now available without a password prompt.

  To uninstall:
    sudo rm $UDEV_DEST
    sudo udevadm control --reload-rules
    kpackagetool6 -r org.kde.legionvantage
================================================================
EOF
