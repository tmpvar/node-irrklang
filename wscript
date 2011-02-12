import Options, glob
from os.path import join, dirname, abspath, exists
from shutil import copy, rmtree
from os import unlink
import sys, os

srcdir = "."
blddir = "build"
VERSION = "0.0.1"
srcdir = abspath(srcdir)
irrklangdir = srcdir + "/deps/irrKlang"

def set_options(opt):
  opt.tool_options("compiler_cxx")
  opt.tool_options("compiler_cc")

def configure(conf):
  conf.check_tool("compiler_cxx")
  conf.check_tool("compiler_cc")
  conf.check_tool("node_addon")


def clean(ctx): 
  if exists("lib/node-irrklang.node"): unlink("lib/node-irrklang.node")
  if exists("build"): rmtree("build")

def build(bld):
  node_irrklang = bld.new_task_gen("cxx", "shlib", "node_addon")
  node_irrklang.source = bld.glob("src/*.cc")
  node_irrklang.name = "node-irrklang"
  node_irrklang.target = "node-irrklang"
  node_irrklang.uselib = ["irrklang"]
  node_irrklang.includes = [irrklangdir + '/include']
  node_irrklang.linkflags = [irrklangdir + "/bin/macosx-gcc/libirrklang.dylib", '-m32']
  node_irrklang.cxxflags = ['-O2', '-m32']
  bld.add_post_fun(copynode)

def copynode(ctx):
  if exists('build/default/node-irrklang.node'):
    print "Copying addon to lib directory"
    copy('build/default/node-irrklang.node','lib/irrklang.node')

  print "Setting up libirrklang"
  os.system("install_name_tool -change /usr/local/lib/libirrklang.dylib %s/lib/libirrklang.dylib ./lib/irrklang.node" % srcdir)

def test(tst):
  os.system("node test/sanity.js")
