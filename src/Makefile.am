# Copyright (c) 2008 Dave Freese, W1HKJ (w1hkj AT w1hkj DOT com)

bin_PROGRAMS = flimg

MINGW32_SRC = flimg-rc.rc include/flimgrc.h \
	utils/mingw.c include/mingw.h include/compat.h \
	utils/getsysinfo.c

# Build the xmlrpcpp source if libflxmlrpc is not found
XMLRPCPP_SRC = \
	xmlrpcpp/XmlRpcBase64.h \
	xmlrpcpp/XmlRpcClient.cpp \
	xmlrpcpp/XmlRpcClient.h \
	xmlrpcpp/XmlRpcDispatch.cpp \
	xmlrpcpp/XmlRpcDispatch.h \
	xmlrpcpp/XmlRpcException.h \
	xmlrpcpp/XmlRpc.h \
	xmlrpcpp/XmlRpcMutex.cpp \
	xmlrpcpp/XmlRpcMutex.h \
	xmlrpcpp/XmlRpcServerConnection.cpp \
	xmlrpcpp/XmlRpcServerConnection.h \
	xmlrpcpp/XmlRpcServer.cpp \
	xmlrpcpp/XmlRpcServer.h \
	xmlrpcpp/XmlRpcServerMethod.cpp \
	xmlrpcpp/XmlRpcServerMethod.h \
	xmlrpcpp/XmlRpcSocket.cpp \
	xmlrpcpp/XmlRpcSocket.h \
	xmlrpcpp/XmlRpcSource.cpp \
	xmlrpcpp/XmlRpcSource.h \
	xmlrpcpp/XmlRpcUtil.cpp \
	xmlrpcpp/XmlRpcUtil.h \
	xmlrpcpp/XmlRpcValue.cpp \
	xmlrpcpp/XmlRpcValue.h

# We distribute these but do not always compile them
EXTRA_flimg_SOURCES = $(FLRIG_WIN32_RES_SRC) $(MINGW32_SRC) $(XMLRPCPP_SRC)

flimg_SOURCES =

if !ENABLE_FLXMLRPC
  flimg_SOURCES += $(XMLRPCPP_SRC)
  flimg_CPPFLAGS = @FLIMG_BUILD_CPPFLAGS@
  flimg_CXXFLAGS = @FLIMG_BUILD_CXXFLAGS@
  flimg_CFLAGS = $(flimg_CXXFLAGS)
  flimg_LDFLAGS = @FLIMG_BUILD_LDFLAGS@
  flimg_LDADD = @FLIMG_BUILD_LDADD@
else
  flimg_CPPFLAGS = @FLIMG_BUILD_CPPFLAGS@ @FLXMLRPC_CFLAGS@
  flimg_CXXFLAGS = @FLIMG_BUILD_CXXFLAGS@ @FLXMLRPC_CFLAGS@
  flimg_CFLAGS = $(flimg_CXXFLAGS)
  flimg_LDFLAGS = @FLIMG_BUILD_LDFLAGS@ @FLXMLRPC_LIBS@
  flimg_LDADD = @FLIMG_BUILD_LDADD@
endif

if MINGW32
if HAVE_WINDRES
  flimg_SOURCES += $(MINGW32_SRC)
endif
endif

########################################################################


flimg_VERSION_MAJOR = @FLIMG_VERSION_MAJOR@
flimg_VERSION_MINOR = @FLIMG_VERSION_MINOR@
flimg_VERSION_PATCH = @FLIMG_VERSION_PATCH@
flimg_VERSION = @FLIMG_VERSION@

.EXPORT_ALL_VARIABLES: nsisinst appbundle

# Sources that are generated,
BUILT_SOURCES =
# not distributed,
nodist_flimg_SOURCES = $(BUILT_SOURCES)
# and deleted by the clean targets
CLEANFILES = $(BUILT_SOURCES)
CLEAN_LOCAL =

if MINGW32
if HAVE_WINDRES
.rc.o:
	$(WINDRES) -Iinclude -I../data/win32 $< -O coff $@
endif
endif

install-data-local:
	if test -f ../data/flimg.xpm; then \
	    $(mkinstalldirs) $(DESTDIR)/$(datadir)/pixmaps; \
	    $(INSTALL_DATA) ../data/flimg.xpm $(DESTDIR)/$(datadir)/pixmaps; \
	fi
	if test -f ../data/flimg.desktop; then \
	    $(mkinstalldirs) $(DESTDIR)/$(datadir)/applications; \
	    $(INSTALL_DATA) ../data/flimg.desktop $(DESTDIR)/$(datadir)/applications; \
	fi

uninstall-local:
	rm -f $(DESTDIR)/$(datadir)/pixmaps/flimg.xpm
	rm -f $(DESTDIR)/$(datadir)/applications/flimg.desktop

# FL_SRC = flimg_dialog.fl

if HAVE_FLUID
flgen: $(FL_SRC)
	(cd include; \
	for f in $(FL_SRC); do \
	    c=$${f%.fl}.cxx; \
		h=$${f%.fl}.h; \
		h=$${h##*/}; \
	    $(FLUID) -c -o ../$$c -h $$h ../$$f; \
	done)
endif


INSTALLER_FILE = flimg-$(flimg_VERSION)_setup.exe
APPBUNDLE=flimg-$(flimg_VERSION)
APPBUNDLE_NOLIBS=$(APPBUNDLE)-nolibs

if HAVE_NSIS
nsisinst: $(bin_PROGRAMS)
	sh ../scripts/mknsisinst.sh "../data" .
    CLEANFILES += $(INSTALLER_FILE)
endif

if DARWIN
appbundle: $(bin_PROGRAMS)
	sh ../scripts/mkappbundle.sh "../data" .
    CLEAN_LOCAL += $(APPBUNDLE_NOLIBS) $(APPBUNDLE) $(APPBUNDLE)*.dmg
endif

clean-local:
	-rm -rf $(CLEAN_LOCAL)

# Sources that we build. It is OK to have headers here.
flimg_SOURCES += \
	flimg.cxx \
	flimg_dialog.cxx \
	lzma/Alloc.h \
	lzma/Alloc.c \
	lzma/LzFind.c \
	lzma/LzFind.h \
	lzma/LzHash.h \
	lzma/LzmaDec.c \
	lzma/LzmaDec.h \
	lzma/LzmaEnc.c \
	lzma/LzmaEnc.h \
	lzma/LzmaLib.c \
	lzma/LzmaLib.h \
	lzma/Types.h \
	utils/amp.cxx \
	utils/base64.cxx \
	utils/base128.cxx \
	utils/base256.cxx \
	utils/debug.cxx \
	utils/socket.cxx \
	utils/status.cxx \
	utils/timeops.cxx \
	utils/util.cxx \
	utils/file_io.cxx \
	utils/xml_io.cxx \
	utils/global_amp.cxx \
	utils/circular_queue.cxx \
	utils/tagSearch.cxx \
	utils/time_table.cxx \
	utils/transmit_camp.cxx \
	utils/ztimer.cxx \
	utils/script_parsing.cxx \
	utils/run_scripts.cxx \
	widgets/calendar.cxx \
	widgets/combo.cxx \
	widgets/date.cxx \
	widgets/fileselect.cxx \
	widgets/flinput2.cxx \
	widgets/flslider2.cxx \
	widgets/Fl_BlockMap.cxx \
	widgets/Fl_Text_Buffer_mod.cxx \
	widgets/Fl_Text_Editor_mod.cxx \
	widgets/Fl_Text_Display_mod.cxx \
	widgets/FTextView.cxx \
	widgets/icons.cxx \
	widgets/missing_strings.c \
	widgets/pixmaps.cxx \
	widgets/pixmaps_tango.cxx \
	widgets/font_browser.cxx \
	widgets/hamcast_group.cxx \
	include/hamcast_group.h 

# Additional source files that are distributed
EXTRA_DIST = \
	config.h \
	utils/mingw.c \
	utils/time_table_dat.cxx \
	widgets/flnfc_common.cxx \
	include/amp.h \
	include/ascii.h \
	include/base64.h \
	include/base128.h \
	include/base256.h \
	include/calendar.h \
	include/combo.h \
	include/compat.h \
	include/compat-mingw.h \
	include/crc16.h \
	include/date.h \
	include/debug.h \
	include/dirent-check.h \
	include/fileselect.h \
	include/fl_lock.h \
	include/flmisc.h \
	include/flimg_config.h \
	include/flimgrc.h \
	include/flinput2.h \
	include/flslider2.h \
	include/font_browser.h \
	include/gettext.h \
	include/icons.h \
	include/flimg.h \
	include/flimg_dialog.h \
	include/missing_strings.h \
	include/socket.h \
	include/mingw.h \
	include/pixmaps.h \
	include/status.h \
	include/threads.h \
	include/timeops.h \
	include/util.h \
	include/file_io.h \
	include/xml_io.h \
	include/global_amp.h \
	include/circular_queue.h \
	include/tagSearch.h \
	include/time_table.h \
	include/transmit_camp.h \
	include/ztimer.h \
	include/script_parsing.h \
	widgets/Fl_Text_Buffer_mod.cxx \
	widgets/Fl_Text_Display_mod.cxx \
	widgets/Fl_Text_Editor_mod.cxx \
	include/Fl_BlockMap.h \
	include/Fl_Text_Buffer_mod.H \
	include/Fl_Text_Display_mod.H \
	include/Fl_Text_Editor_mod.H \
	include/FTextView.h

# Additional non-source files that are distributed
#EXTRA_DIST += \
#	../data/template.rtf
#	../flimg-doc/flimg-quick-guide.html

# Additional source files that support non-Linux cross compilation
EXTRA_DIST += \
	../ChangeLog \
	../data/flimg.desktop \
	../data/flimg.xpm \
	../data/flimg.png \
	../data/win32/fl_app.nsi \
	../data/win32/flimg.ico \
	../scripts/buildmxe.sh \
	../scripts/builddist.sh \
	../scripts/mkappbundle.sh \
	../scripts/mknsisinst.sh \
	../data/mac/Info.plist.in \
	../data/mac/flimg.icns \
	$(flimg_WIN32_SRC) \
	$(flimg_FL_SRC)
