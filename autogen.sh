#!/bin/bash
srcdir=`dirname $0`

gthumb_version=($(gthumb -v | awk '{print $2}' | cut -d. -f1-2))
if [[ "$gthumb_version" == "3.4" ]]; then
	cp config/configure_3-4.ac configure.ac
	cp config/openexr_viewer.extension_3-4.in.in src/openexr_viewer.extension.in.in
elif [[ "$gthumb_version" == "3.5" ]]; then
	cp config/configure_3-5.ac configure.ac
	cp config/openexr_viewer.extension_3-5.in.in src/openexr_viewer.extension.in.in
elif [[ "$gthumb_version" == "3.6" ]]; then
	cp config/configure_3-6.ac configure.ac
	cp config/openexr_viewer.extension_3-6.in.in src/openexr_viewer.extension.in.in
elif [[ "$gthumb_version" == "3.7" ]]; then
	cp config/configure_3-7.ac configure.ac
	cp config/openexr_viewer.extension_3-7.in.in src/openexr_viewer.extension.in.in
elif [[ "$gthumb_version" == "3.8" ]]; then
	cp config/configure_3-8.ac configure.ac
	cp config/openexr_viewer.extension_3-8.in.in src/openexr_viewer.extension.in.in
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
