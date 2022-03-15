DEP = ../dep
PDLIBBUILDER_DIR=$(DEP)/pd-lib-builder/
IS_DIR = $(DEP)/InterfacesSonores/

lib.name = is

helloworld.class.sources = 1-helloworld.cpp
# helloworld~.class.sources = 2-helloworld-tilde.cpp
# sine~.class.sources = 3-sine-tilde.cpp
# blosc~.class.sources = 4-blosc-tilde.cpp

cflags = -std=c++11 -I$(IS_DIR)

define forDarwin
  cflags += -mmacosx-version-min=10.9
endef

PDLIBBUILDER_DIR=$(DEP)/pd-lib-builder/
include $(PDLIBBUILDER_DIR)/Makefile.pdlibbuilder
