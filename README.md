# gr-hrpt

HRPT Blocks from gr-noaa and others ported to GNU Radio 3.8+

Currently blocks from gr-noaa were kept in their original form for compatbility with older flowcharts. This may change.

## Examples

Several usage example can be found in the [examples](https://github.com/altillimity/gr-hrpt/tree/master/examples) directory included in this repo. This includes flowcharts used for decoding NOAA, METEOR, MetOp and FengYun-3 (soon) HRPT downlinks. Data generated has to be processed by softwares such as [MetFy3x](http://www.sat.cc.ua/page5.html), [HRPT Reader](https://www.satsignal.eu/software/hrpt.htm), [weathersat](https://github.com/rocketscientist-fred/weathersat), my [quite WIP decoder](https://gitlab.altillimity.com/altillimity/hrpt-decoder) or anything else that can do so.

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