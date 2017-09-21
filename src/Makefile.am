extensiondir = $(EXTENSION_DIR)
extension_LTLIBRARIES = libopenexr_viewer.la

libopenexr_viewer_la_SOURCES = \
	main.c	\
	ExrLoader.cpp

libopenexr_viewer_la_CFLAGS = $(EXTENSION_CFLAGS) -DEXTENSION_LOCALEDIR=\"$(datadir)/locale\" 
libopenexr_viewer_la_LDFLAGS = $(EXTENSION_LIBTOOL_FLAGS)
libopenexr_viewer_la_LIBADD = $(EXTENSION_LIBS)

extensioninidir = $(EXTENSION_DIR)
extensionini_in_files = openexr_viewer.extension.in.in
extensionini_DATA = $(extensionini_in_files:.extension.in.in=.extension)

@GTHUMB_EXTENSION_IN_RULE@
@GTHUMB_EXTENSION_RULE@

EXTRA_DIST = $(extensionini_in_files) 

DISTCLEANFILES = $(extensionini_DATA)

-include $(top_srcdir)/git.mk
