# Raster algebra comparison

Following [the introduction](https://lists.osgeo.org/pipermail/gdal-dev/2016-September/045134.html)
in GDAL of pixel functions written in python in VRT derived bands, I was curious
to compare various tools for raster algebra.

This is a very simple benchmark and results should be taken with massive amounts of
salt. There is probably significant overhead here and there, and I'm not
even sure what I am measuring. It would be interesting to test different
functions with different image formats, sizes, number of bands, etc.

Requires GDAL trunk (for VRT derived bands in python), and --with-python enabled
(for `gdal_calc.py`).  Amazingly the VRT python functionality does not require
python at compile time.

The computation done is the average of the first bands of the nine input images (size 3671x3671, int16).

For some unknown reason the output of `gdal_calc.py` is slightly different than the others. Probably some pixel type issue?

