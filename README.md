OpenEXR Support for gThumb
==========================

This implements a basic support for OpenEXR on gThumb, the GNOME image viewer.

Dependencies
============

Ubuntu 16.04LTS
---------------
You need to install these dependencies to compile and install the extension:
* gthumb
* gthumb-dev
* gnome-common
* libglib2.0-dev
* build-essential
* gnome-doc-utils
* libgtk-3-dev
* libgconf2-dev
* libopenexr-dev

'''
sudo apt install gthumb gthumb-dev gnome-common libglib2.0-dev build-essential gnome-doc-utils libgtk-3-dev libgconf2-dev libopenexr-dev
'''

Compilation
===========

In order to compile and install the extension, do:

```
./autogen.sh --prefix=/usr
make
sudo make install
```

Usage
=====
To use the extension, you need to activate it in gThumb.
Go to the top left menu, then to *Preferences* and on *Extensions*, activate *OpenEXR format support*.
After restarting gThumb, you should be able to display OpenEXR images.