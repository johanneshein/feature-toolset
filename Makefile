#
# This file is part of the feature-toolset project.
# Copyright 2018 Johannes Hein
#
# Author: Johannes Hein <johannes.hein@tu-ilmenau.de>
#
# feature-toolset is free software: you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.
#
# feature-toolset is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with feature-toolset. If not, see <http://www.gnu.org/licenses/>.
#



# local paths in our repository root directory
DIR_SOURCES = src/
DIR_BINARIES = bin/
DIR_DOCUMENTATION = doc/



# terminal messages
MSG_COMPILING = make: *** COMPILE ...
MSG_LINKING = make: *** LINK ...

MSG_STATICCODEANALYSIS = make: *** RUN STATIC CODE ANALYSIS TOOL...

MSG_DOKU = make: *** CREATE DOCUMENTATION ...
MSG_DOKU_DONE = make: *** CREATE DOCUMENTATION SUCCESS

MSG_CLEAN_BINARIES = make: *** DELETE BINARIES ...
MSG_CLEAN_DOCUMENTATION = make: *** DELETE GENERATED DOCUMENTATION ...
MSG_CLEAN_DONE = make: *** CLEAN SUCCESS



# used programs with all necessary flags
CPP = g++

CPP_FLAGS_COMPILING = -I $(DIR_SOURCES)
CPP_FLAGS_COMPILING += -c
CPP_FLAGS_COMPILING += -std=c++11
CPP_FLAGS_COMPILING += -Wall
#CPP_FLAGS_COMPILING += -ggdb

CPP_FLAGS_LINKING += -std=c++11
CPP_FLAGS_LINKING += -Wall
#CPP_FLAGS_LINKING += -ggdb

CHANGE_DIR = cd

COPY_FILE = cp
COPY_DIR = cp -r

DELETE_FILE = rm
DELETE_DIR = rm -rf

DOXYGEN = doxygen

STATIC_CODE_ANALYSIS_TOOL = cppcheck
STATIC_CODE_ANALYSIS_TOOL_FLAGS = --quiet



# sources and objects excluding tests
SOURCES = $(shell find $(DIR_SOURCES) -name '*.cpp')
OBJECTS = $(patsubst $(DIR_SOURCES)%,$(DIR_BINARIES)%,$(patsubst %.cpp,%.o,$(SOURCES:%.cpp=%.o)))



# build targets
TARGET = main



# targets which are always out of date
.PHONY: default all clean cleanbuild cleandoc checksources doc do_doc



# default target called by make without any further parameters
default: clean rebuild



# does a completely new rebuild of everything what's possible
all: clean checksources doc rebuild



# removes all generated directories and files
clean: cleanbuild cleandoc
	$(info )
	$(info $(MSG_CLEAN_DONE))

cleanbuild:
	$(info )
	$(info $(MSG_CLEAN_BINARIES))
	$(DELETE_DIR) $(DIR_BINARIES)

cleandoc:
	$(info )
	$(info $(MSG_CLEAN_DOCUMENTATION))
	$(DELETE_DIR) $(DIR_DOCUMENTATION)



# executes a static code analysis tool for cpp
checksources:
	$(info )
	$(info $(MSG_STATICCODEANALYSIS))
	$(STATIC_CODE_ANALYSIS_TOOL) $(STATIC_CODE_ANALYSIS_TOOL_FLAGS) $(DIR_SOURCES)



# creates an documentation of the api with doxygen
doc: do_doc
	$(info )
	$(info $(MSG_DOKU_DONE))

do_doc:
	$(info )
	$(info $(MSG_DOKU))
	$(DOXYGEN)



# build process

rebuild: $(TARGET)

# link object files to the target executable
$(TARGET): $(OBJECTS)
	$(info )
	$(info $(MSG_LINKING) $(TARGET))
	$(CPP) $(CPP_FLAGS_LINKING) $(OBJECTS) -o $@

$(DIR_BINARIES)%.o: $(DIR_SOURCES)%.cpp
	$(info )
	$(info $(MSG_COMPILING) $<)
	@mkdir -p $(@D)
	$(CPP) $(CPP_FLAGS_COMPILING) $< -o $@
