import os
import sys
from build_config import *

#setup our requirements
cppEnv = Environment()

# add boost header
cppEnv.Append(CPPPATH=include_search_path)

# compile-time flags
cppEnv.Append(CCFLAGS = ['-g'])

# variables the sub build directories need
Export('cppEnv','test_sources')

SConscript('tests/cpp/SConscript')



