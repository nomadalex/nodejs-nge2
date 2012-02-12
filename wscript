#!/usr/bin/env python

from os import popen
import Utils

srcdir = "."
blddir = "build"
VERSION = "0.0.1"

def set_options(opt):
  opt.tool_options("compiler_cxx")

def configure(conf):
  conf.check_tool("compiler_cxx")
  conf.check_tool("node_addon")
  nge2_libdir = "/home/ifreedom/pjt-l/libnge2/build/linux/dll/lib"
#  if nge2_libdir == "":
#    nge2_libdir = "/usr/lib"
#  nge2_libdir = nge2_libdir.replace("-L", "")
  nge2_includedir = ["../libnge2/include", "../libnge2/coolaudio"]
#  if nge2_includedir == "":
#    nge2_includedir = "/usr/include"
#  nge2_includedir = nge2_includedir.replace("-I", "")
  conf.env.append_value("LIBPATH_NGE2", nge2_libdir)
  conf.env.append_value('CPPPATH_NGE2', nge2_includedir)
  conf.env.append_value("LIB_NGE2", "nge2")

def build(bld):
  obj = bld.new_task_gen("cxx", "shlib", "node_addon")
  obj.source = [ 'src/nge2.cpp', 'src/main.cpp', 'src/input.cpp', 'src/graphics.cpp', 'src/NgeApp.cpp' ]
#  obj.source = [ 'src/nge2.cpp','src/graphics.cpp', 'src/input.cpp', 'src/main.cpp',
#               'src/NgeApp.cpp' ]
  obj.target = 'nge2'
  obj.uselib = "NGE2"
