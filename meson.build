project('openexr_viewer', ['c', 'cpp'],
  license : 'GPL2+',
  version : '3.10.0',
  meson_version : '>=0.43'
)

gthumb_name = 'gthumb'

glib_version = '>=2.54.0'
gtk_version = '>=3.16'
exiv2_version = '>=0.21'
clutter_version = '>=1.12.0'
clutter_gtk_version = '>=1.0.0'
gstreamer_version = '>=1.0.0'
libraw_version = '>=0.14'
libsoup_version = '>=2.42'
libsecret_version = '>=0.11'
libbrasero_version = '>=3.2.0'
libchamplain_version = '>=0.12.0'
librsvg_version = '>=2.34.0'
libwebp_version = '>=0.2.0'
libjson_glib_version = '>=0.15.0'
webkit2_version = '>=1.10.0'
lcms2_version = '>=2.6'
colord_version = '>=1.3'
openexr_version = '>=2.4'

version_array = meson.project_version().split('.')
api_version = '.'.join([version_array[0], version_array[1]])

gnome = import('gnome')
i18n = import('i18n')
gettext_package = meson.project_name()
c_comp = meson.get_compiler('c')
cpp_comp = meson.get_compiler('cpp')
prefix = get_option('prefix')
datadir = join_paths(prefix, get_option('datadir'))
pkgdatadir = join_paths(datadir, gthumb_name)
pkgincludedir = join_paths(prefix, get_option('includedir'), gthumb_name)
pkglibdir = join_paths(prefix, get_option('libdir'), gthumb_name)
po_dir = join_paths(meson.source_root(), 'po')
extensions_install_dir = join_paths(pkglibdir, 'extensions')
ui_install_dir = join_paths(pkgdatadir, 'ui')
icons_install_dir = join_paths(pkgdatadir, 'icons')

if get_option('run-in-place')
  ui_data_dir = join_paths(meson.source_root(), 'data', 'ui')
  icons_data_dir = join_paths(meson.source_root(), 'data', 'icons', 'private')
  extensions_ui_data_dir = join_paths(meson.source_root(), 'extensions')
  extensions_data_dir = join_paths(meson.build_root(), 'extensions')
  contact_sheet_data_dir = join_paths(meson.source_root(), 'extensions', 'contact_sheet', 'data')
  webalbum_data_dir = join_paths(meson.source_root(), 'extensions', 'webalbums', 'data')
else
  ui_data_dir = ui_install_dir
  icons_data_dir = icons_install_dir
  extensions_ui_data_dir = ui_data_dir
  extensions_data_dir = extensions_install_dir
  contact_sheet_data_dir = pkgdatadir
  webalbum_data_dir = pkgdatadir
endif

# meson.add_install_script('postinstall.py')


config_data = configuration_data()
config_data.set_quoted('GETTEXT_PACKAGE', gettext_package)
config_data.set_quoted('PACKAGE_NAME', meson.project_name())
config_data.set_quoted('PACKAGE_VERSION', meson.project_version())
config_data.set_quoted('GTHUMB_API_VERSION', api_version)
config_data.set_quoted('GTHUMB_LOCALEDIR', join_paths(prefix, get_option('localedir')))
config_data.set_quoted('GTHUMB_UI_DIR', ui_data_dir)
config_data.set_quoted('GTHUMB_ICON_DIR', icons_data_dir)
config_data.set_quoted('GTHUMB_EXTENSIONS_UI_DIR', extensions_ui_data_dir)
config_data.set_quoted('GTHUMB_EXTENSIONS_DIR', extensions_data_dir)
config_data.set_quoted('CONTACT_SHEET_DATADIR', contact_sheet_data_dir)
config_data.set_quoted('WEBALBUM_DATADIR', webalbum_data_dir)

libz_dep = dependency('zlib')
libm_dep = c_comp.find_library('m')
libjpeg_dep = c_comp.find_library('jpeg')
if libjpeg_dep.found()
  jpeg_deps = [ libm_dep, libz_dep, libjpeg_dep ]
endif

use_exiv2 = false
use_clutter = false
use_gstreamer = false
use_libchamplain = false
use_lcms2 = false
use_colord = false
use_libtiff = false
use_libwebp = false
use_libraw = false
use_librsvg = false
with_webservices = false
use_libsecret = false
use_libbrasero = false

# C/C++ args

c_args = []
cpp_args = []
if get_option('buildtype').contains('debug')
  warn_deprecated = get_option('warn-deprecated')
  test_c_args = [
    '-Wall',
    '-Wcast-align',
    '-Wtype-limits',
    '-Wclobbered',
    '-Wempty-body',
    '-Wignored-qualifiers',
    '-Wmissing-prototypes',
    '-Wnested-externs',
    '-Wpointer-arith',
    '-Wno-sign-compare',
    '-Wformat-security'
  ]
  test_cpp_args = [
    '-Wall',
    '-Wcast-align',
    '-Wtype-limits',
    '-Wclobbered',
    '-Wempty-body',
    '-Wignored-qualifiers',
    '-Wpointer-arith',
    '-Wno-sign-compare',
    '-Wformat-security'
  ]
else
  warn_deprecated = false
  test_c_args = [ '-Wall' ]
  test_cpp_args = [ '-Wall' ]
endif
if not(warn_deprecated)
  test_c_args += [ '-Wno-deprecated-declarations' ]
  test_cpp_args += [ '-Wno-deprecated-declarations' ]
endif
c_args += c_comp.get_supported_arguments(test_c_args)
cpp_args += cpp_comp.get_supported_arguments(test_cpp_args)






common_deps = [
  libm_dep,
  dependency('threads'),
  dependency('glib-2.0', version : glib_version),
  dependency('gthread-2.0'),
  dependency('gmodule-2.0'),
  dependency('gio-unix-2.0'),
  dependency('gtk+-3.0', version : gtk_version),
  dependency('libpng'),
  dependency('zlib'),
  dependency('gsettings-desktop-schemas')
]


config_file = configure_file(output : 'config.h', configuration : config_data)
config_inc = include_directories('.')

subdir('gthumb/gthumb')
subdir('extension')