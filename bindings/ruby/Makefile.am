#
# Makefile.am for libstorage/bindings/ruby
#

SUBDIRS = examples

EXTRA_DIST = storage-ruby.i enum_ref.i

MAINTAINERCLEANFILES = storage_wrap.cxx

BUILT_SOURCES = storage_wrap.cxx

rubyextensiondirdir = $(RUBY_EXTENSION_DIR)

AM_CXXFLAGS = -fPIC -DPIC

AM_CPPFLAGS = -I${top_srcdir} -I$(RUBY_INCLUDE_DIR) -I$(RUBY_INCLUDE_DIR)/$(RUBY_ARCH_NAME)

include ../storage.deps

# Build Ruby module as shared library
rubyextensiondir_LTLIBRARIES = storage.la
nodist_storage_la_SOURCES = storage_wrap.cxx
storage_la_LIBADD =  $(top_builddir)/storage/libstorage.la -l$(RUBY_SO_NAME)
storage_la_LDFLAGS = -no-undefined -module -avoid-version -L$(RUBY_EXTENSION_DIR)

storage_la_DEPENDENCIES =				\
	$(DEPENDENCIES)					\
	${top_builddir}/storage/libstorage.la

storage_wrap.cxx: storage-ruby.i enum_ref.i ../storage.i $(DEPENDENCIES)
	swig -o storage_wrap.cxx -c++ -ruby ${AM_CPPFLAGS} storage-ruby.i

CLEANFILES = storage.so storage_wrap.cxx

