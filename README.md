OpenEXR Support for gThumb
==========================

This implements a basic support for OpenEXR on gThumb, the GNOME image viewer.


Package
=======


Arch Linux
----------

An AUR is available here: https://aur.archlinux.org/packages/gthumb-openexr-extension/

If using yay, you can install it with (after sync):
```
yay -Sy
yay -S gthumb-openexr-extension
```

Finally, see the 'Usage' section for activating and using the extension.


Ubuntu 16.04 LTS & 20.04 LTS
----------------------------

A ppa is available here:
https://launchpad.net/~alban-f/+archive/ubuntu/gthumb-openexr-extension

You need to add it to your repositories:
```
sudo add-apt-repository ppa:alban-f/gthumb-openexr-extension
sudo apt-get update
```

Then, install the extension:
```
sudo apt install gthumb-openexr-extension
```

Finally, see the 'Usage' section for activating and using the extension.


Usage
=====

To use the extension, you need to activate it in gThumb.  Go to the
top left menu, then to *Preferences*.

![1](https://user-images.githubusercontent.com/7930348/30781607-973502e8-a122-11e7-86e1-cd080a8b6b32.png)

Open the *Extensions* tab.

![2](https://user-images.githubusercontent.com/7930348/30781609-998478da-a122-11e7-89e5-099934c04f16.png)

Then activate *OpenEXR format support*.

![3](https://user-images.githubusercontent.com/7930348/30781612-9ae9e9c6-a122-11e7-9c06-e8da3a114571.png)

After restarting gThumb, you should be able to display OpenEXR images.

Manual installation
===================

Dependencies
------------

### Ubuntu 16.04 LTS

You need to install these dependencies to compile and install the extension:
* gthumb
* gthumb-dev
* gnome-common
* libglib2.0-dev
* build-essential
* libgtk-3-dev
* libgconf2-dev
* libopenexr-dev
* cmake

```
sudo apt install \
     gthumb \
     gthumb-dev \
     gnome-common \
     libglib2.0-dev \
     build-essential \
     libgtk-3-dev \
     libgconf2-dev \
     libopenexr-dev \
     cmake
```

### Compilation

In order to compile and install the extension, do:

```
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr
make
sudo make install
```
