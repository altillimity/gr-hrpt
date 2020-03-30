# gr-hrpt

HRPT Blocks from gr-noaa and others ported to GNU Radio 3.8+

Currently blocks from gr-noaa were kept in their original form for compatbility with older flowcharts. This may change.

## Building

Make sure you have swig, cmake, boost, python and gnuradio installed.

eg. `sudo apt install gnuradio-dev libboost-dev cmake swig python3-dev`

```
git clone https://gitlab.altillimity.com/altillimity/gr-hrpt.git
cd gr-hrpt
mkdir build && cd build
cmake ..
make -j4
sudo make install
```


You can run `make uninstall` to remove the package.