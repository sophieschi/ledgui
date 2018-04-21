# ledgui
GUI to contol Adafruit LED Ring


## Needed Libraries

### qtmosquitto
```
git clone https://github.com/skyhisi/qtmosquitto.git
cd qtmosquitto/build
cmake -D CMAKE_BUILD_TYPE=Debug ../source/
make
cp libqtmosquitto.so /usr/local/lib/
cp ../source/qtmosquitto.hpp /usr/local/include/
```

### other stuff
may be incomplete
- libmosquitto-dev
- qt stuff
