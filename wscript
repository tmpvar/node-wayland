
import glob
import Options

srcdir = '.'
blddir = 'build'
VERSION = '0.0.1'

def set_options(opt):
  opt.tool_options('compiler_cxx')
  opt.add_option('--profile', action='store_true', help='Enable profiling', dest='profile', default=False)

def configure(conf):
  o = Options.options
  conf.env['USE_PROFILING'] = o.profile
  conf.check_tool('compiler_cxx')
  conf.check_tool('node_addon')
  conf.env.append_value('CPPFLAGS', '-DNDEBUG')

  if conf.env['USE_PROFILING'] == True:
    conf.env.append_value('CXXFLAGS', ['-pg'])
    conf.env.append_value('LINKFLAGS', ['-pg'])

  conf.check_cfg(package='wayland-client', args='--cflags --libs', mandatory=True)
  conf.check_cfg(package='glib-2.0', args='--cflags --libs', mandatory=True)
  conf.check_cfg(package='cairo', args='--cflags --libs', mandatory=True)
  flags = ['-O3', '-Wall', '-D_FILE_OFFSET_BITS=64', '-D_LARGEFILE_SOURCE']
  conf.env.append_value('CCFLAGS', flags)
  conf.env.append_value('CXXFLAGS', flags)

def build(bld):
  obj = bld.new_task_gen('cxx', 'shlib', 'node_addon')
  obj.target = 'wayland'
  obj.source = bld.glob('src/*.cc')
  obj.uselib = ['WAYLAND-CLIENT', 'GLIB-2.0', 'CAIRO']
