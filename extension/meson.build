extension_data = configuration_data()
extension_data.set('VERSION', meson.project_version())
extension_data.set('GTHUMB_API_VERSION', api_version)

extension_common_deps = [ common_deps, gthumb_h_dep ]

source_files = files(
  'ExrLoader.cpp',
  'main.c'
)

shared_module('openexr_viewer',
  sources : source_files ,
  dependencies : [
    extension_common_deps
  ],
  include_directories : [ config_inc, gthumb_inc ],
  c_args : c_args,
  install : true,
  install_dir : extensions_install_dir,
  install_rpath : extensions_install_dir
)

# .extension file

extension_in_file = configure_file(
  input : 'openexr_viewer.extension.in.in',
  output : 'openexr_viewer.extension.in',
  configuration : extension_data
)

i18n.merge_file(
  input : extension_in_file,
  output : 'openexr_viewer.extension',
  type : 'desktop',
  po_dir : po_dir,
  install : true,
  install_dir : extensions_install_dir
)
