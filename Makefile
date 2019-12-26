#!/usr/bin/make -f
# Makefile for DISTRHO Plugins #
# ---------------------------- #
# Created by falkTX, Christopher Arndt, and Patrick Desaulniers
#

include dpf/Makefile.base.mk

all: libs plugins gen

# --------------------------------------------------------------

submodules:
	git submodule update --init --recursive

libs:
	$(MAKE) -C dpf/dgl

plugins: libs res
	$(MAKE) all -C plugins/Regrader

ifneq ($(CROSS_COMPILING),true)
gen: plugins dpf/utils/lv2_ttl_generator
	@$(CURDIR)/dpf/utils/generate-ttl.sh
ifeq ($(MACOS),true)
	@$(CURDIR)/dpf/utils/generate-vst-bundles.sh
endif

dpf/utils/lv2_ttl_generator:
	$(MAKE) -C dpf/utils/lv2-ttl-generator
else
gen: plugins dpf/utils/lv2_ttl_generator.exe
	@$(CURDIR)/dpf/utils/generate-ttl.sh

dpf/utils/lv2_ttl_generator.exe:
	$(MAKE) -C dpf/utils/lv2-ttl-generator WINDOWS=true
endif

# --------------------------------------------------------------

res: gen/RegraderEditRes.cpp

gen/RegraderEditRes.cpp: resources/Regrader.json utils/bin/rescc$(APP_EXT)
	@install -d gen
	utils/bin/rescc$(APP_EXT) $< > $@

utils/bin/rescc$(APP_EXT):
	$(MAKE) bin/rescc$(APP_EXT) -C utils

# --------------------------------------------------------------

clean:
	$(MAKE) clean -C dpf/dgl
	$(MAKE) clean -C dpf/utils/lv2-ttl-generator
	$(MAKE) clean -C plugins/Regrader
	rm -rf bin build gen

install: all
	$(MAKE) install -C plugins/Regrader

install-user: all
	$(MAKE) install-user -C plugins/Regrader

# --------------------------------------------------------------

.PHONY: all clean install install-user submodule libs plugins gen
