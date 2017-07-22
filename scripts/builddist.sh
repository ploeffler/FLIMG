autoreconf

./configure \
  $PKGCFG \
  $CROSSCFG \
  --with-ptw32=$PREFIX/usr/i686-w64-mingw32.static \
  --enable-static \
  PTW32_LIBS="-lpthread -lpcreposix -lpcre -lregex" \
  FLTK_CONFIG=$PREFIX/bin/i686-w64-mingw32.static-fltk-config

make

$PREFIX/bin/i686-w64-mingw32.static-strip src/flimg.exe
make nsisinst
mv src/*setup*exe .

make clean

./configure
make distcheck
make clean
