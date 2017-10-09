#!/bin/sh
srcdir=`dirname $0`

gthumb_version=($(gthumb -v | awk '{print $2}' | cut -d. -f1-2))
if [[ "$gthumb_version" == "3.4" ]]; then
	cp config/configure_3-4.ac configure.ac
elif [[ "$gthumb_version" == "3.5" ]]; then
	cp config/configure_3-5.ac configure.ac
else
	echo "Your version of gThumb is not supported yet"
fi

[ -z "$srcdir" ] && srcdir=.

PKG_NAME="gthumb-openexr-viewer"

if [ ! -f "$srcdir/configure.ac" ]; then
 echo "$srcdir doesn't look like source directory for $PKG_NAME" >&2
 exit 1
fi

which gnome-autogen.sh || {
	echo "You need to install gnome-common from GNOME Git"
	exit 1
}


. gnome-autogen.sh "$@"
