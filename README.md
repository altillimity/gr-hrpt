# gr-hrpt

HRPT Blocks from gr-noaa and others ported to GNU Radio 3.8+

Currently blocks from gr-noaa were kept in their original form for compatbility with older flowcharts. This may change.

## Building

Make sure you have swig, cmake, boost, python and gnuradio installed.

eg. `sudo apt install gnuradio-dev libboost-dev cmake swig python3-dev`

On some distributions, including most debian-based ones such as Ubuntu, you probably need to use /usr as an installation prefix. This is done by replacing the below `cmake ..` command with `cmake -DCMAKE_INSTALL_PREFIX=/usr ..`.

```
git clone https://gitlab.altillimity.com/altillimity/gr-hrpt.git
cd gr-hrpt
mkdir build && cd build
cmake ..
make -j4
sudo make install
```


You can run `make uninstall` to remove the package.