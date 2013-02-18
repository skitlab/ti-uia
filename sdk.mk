# 
#  Copyright (c) 2011, Texas Instruments Incorporated
#  All rights reserved.
# 
#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions
#  are met:
# 
#  *  Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
# 
#  *  Redistributions in binary form must reproduce the above copyright
#     notice, this list of conditions and the following disclaimer in the
#     documentation and/or other materials provided with the distribution.
# 
#  *  Neither the name of Texas Instruments Incorporated nor the names of
#     its contributors may be used to endorse or promote products derived
#     from this software without specific prior written permission.
# 
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
#  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
#  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
#  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
#  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
#  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
#  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
#  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
#  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
#  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
#  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# 

#
# ==== Standard Variables ====
#


#
# Where to install/stage the packages
# Typically this would point to the devkit location
#

DESTDIR ?= $(HOME)/target-root
packagedir ?= /packages
libdir ?= /lib
includedir ?= /include
ifeq ($(docdir),)
    docdir := /share/ti/uia/doc
    xdcdocdir := /docs/uia
else
    xdcdocdir := $(docdir)
endif

ifeq ($(prefix),)
    prefix := /usr
    xdcprefix := /
else
    xdcprefix = $(prefix)
endif

#
# Installation of XDCTools. This must be passed to the Makefile for the
# install-packages target.
#

XDC_INSTALL_DIR="<UNDEFINED>"



# 
# ==== Tools ====
#

XS=$(XDC_INSTALL_DIR)/xs
XDC=$(XDC_INSTALL_DIR)/xdc
XDCPKG=$(XDC_INSTALL_DIR)/bin/xdcpkg

#
# == Helper variables ==
#

PRODUCTS = $(subst packages/,,$(wildcard packages/ti/*))
LIBS = $(shell cd packages && find . -name '*.av5T' -or -name '*.a' -type f)
HEADERS = $(shell cd packages && find . -name '*.h' -type f -not \( -name "package.defs.h" -o -name "_*.h" \))
DOCS = $(wildcard *release_notes.html) docs/*

LIBDIR = $(DESTDIR)/$(prefix)/$(libdir)
INCDIR = $(DESTDIR)/$(prefix)/$(includedir)
DOCDIR = $(DESTDIR)/$(prefix)/$(docdir)
PACKAGESDIR = $(DESTDIR)/$(xdcprefix)/$(packagedir)
XDCDOCDIR = $(DESTDIR)/$(xdcprefix)/$(xdcdocdir)

#
# ==== Helper functions ====
#

define purge
        @find $(PACKAGESDIR)/$(1) -name $(2) -exec rm -rf {} \;

endef


# 
# ==== Targets ====
#

install-packages:
	@echo "Installing packages.."
	@mkdir -p $(PACKAGESDIR)
	@cd packages && cp --parents -rf $(PRODUCTS) $(PACKAGESDIR)
	$(foreach prod,$(PRODUCTS),$(call purge,$(prod),'*.c'))
	$(foreach prod,$(PRODUCTS),$(call purge,$(prod),'*.bld'))
	@echo "Installing documentation.."
	@mkdir -p $(XDCDOCDIR)
	@cp -rf $(DOCS) $(XDCDOCDIR)

install:
	@echo "Installing libraries.."
	@mkdir -p $(LIBDIR)
	@cd packages && cp -f --parents $(LIBS) $(LIBDIR)
	@echo "Installing header files.."
	@mkdir -p $(INCDIR)
	@cd packages && cp -f --parents $(HEADERS) $(INCDIR)
	@echo "Installing documentation.."
	@mkdir -p $(DOCDIR)
	@cp -rf $(DOCS) $(DOCDIR)

help:
	@echo
	@echo "Available build targets are:"
	@echo
	@echo "  install-packages"
	@echo "      Install the RTSC packages in the repository at DESTDIR"
	@echo
	@echo "  install"
	@echo "      Install the headers and libraries in the DESTDIR directory"
	@echo
