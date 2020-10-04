#!/bin/bash

function prepare_34 {
    cp config/configure_3-4.ac configure.ac
    cp config/openexr_viewer.extension_3-4.in.in src/openexr_viewer.extension.in.in
}

function prepare_35 {
    cp config/configure_3-5.ac configure.ac
    cp config/openexr_viewer.extension_3-5.in.in src/openexr_viewer.extension.in.in
}

function prepare_36 {
    cp config/configure_3-6.ac configure.ac
    cp config/openexr_viewer.extension_3-6.in.in src/openexr_viewer.extension.in.in
}

function prepare_37 {
    cp config/configure_3-7.ac configure.ac
    cp config/openexr_viewer.extension_3-7.in.in src/openexr_viewer.extension.in.in
}

function prepare_38 {
    cp config/configure_3-8.ac configure.ac
    cp config/openexr_viewer.extension_3-8.in.in src/openexr_viewer.extension.in.in
}

function prepare_39 {
    cp config/configure_3-9.ac configure.ac
    cp config/openexr_viewer.extension_3-9.in.in src/openexr_viewer.extension.in.in
}

function prepare_310 {
    cp config/configure_3-10.ac configure.ac
    cp config/openexr_viewer.extension_3-10.in.in src/openexr_viewer.extension.in.in
}

srcdir=`dirname $0`

source /etc/os-release

if [[ "$NAME" == "Ubuntu" ]]; then
    if [[ "$VERSION_ID" == "16.04" ]]; then
	prepare_34
    elif [[ "$VERSION_ID" == "18.04" ]]; then
	prepare_36
    elif [[ "$VERSION_ID" == "20.04" ]]; then
	prepare_38
    fi
else
    gthumb_version=($(gthumb -v | awk '{print $2}' | cut -d. -f1-2))
    if [[ "$gthumb_version" == "3.4" ]]; then
	prepare_34
    elif [[ "$gthumb_version" == "3.5" ]]; then
	prepare_35
    elif [[ "$gthumb_version" == "3.6" ]]; then
	prepare_36
    elif [[ "$gthumb_version" == "3.7" ]]; then
	prepare_37
    elif [[ "$gthumb_version" == "3.8" ]]; then
	prepare_38
    elif [[ "$gthumb_version" == "3.9" ]]; then
	prepare_39
    elif [[ "$gthumb_version" == "3.10" ]]; then
	prepare_310
    else
	echo "Your version of gThumb is not supported yet"
    fi
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
