OpenEXR Support for gThumb
==========================

This implements a basic support for OpenEXR on gThumb, the GNOME image viewer.

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