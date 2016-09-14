#!/bin/bash

#set -euo pipefail

# GDAL VRT derived band with python defined pixel function
time gdal_translate landsat.vrt landsat_average_gdal_vrt.tif

# gdal_calc.py
time gdal_calc.py \
-A Data/LANDSAT_MultiTempIm_clip_GapF_20140309.tif \
-B Data/LANDSAT_MultiTempIm_clip_GapF_20140401.tif \
-C Data/LANDSAT_MultiTempIm_clip_GapF_20140417.tif \
-D Data/LANDSAT_MultiTempIm_clip_GapF_20140528.tif \
-E Data/LANDSAT_MultiTempIm_clip_GapF_20140620.tif \
-F Data/LANDSAT_MultiTempIm_clip_GapF_20140731.tif \
-G Data/LANDSAT_MultiTempIm_clip_GapF_20140901.tif \
-H Data/LANDSAT_MultiTempIm_clip_GapF_20141003.tif \
-I Data/LANDSAT_MultiTempIm_clip_GapF_20141026.tif \
--calc="(A+B+C+D+E+F+G+H+I)/9.0" \
--outfile=landsat_average_gdal_calc.tif

# OTB BandMathX
time otbcli_BandMathX -il \
Data/LANDSAT_MultiTempIm_clip_GapF_20140309.tif \
Data/LANDSAT_MultiTempIm_clip_GapF_20140401.tif \
Data/LANDSAT_MultiTempIm_clip_GapF_20140417.tif \
Data/LANDSAT_MultiTempIm_clip_GapF_20140528.tif \
Data/LANDSAT_MultiTempIm_clip_GapF_20140620.tif \
Data/LANDSAT_MultiTempIm_clip_GapF_20140731.tif \
Data/LANDSAT_MultiTempIm_clip_GapF_20140901.tif \
Data/LANDSAT_MultiTempIm_clip_GapF_20141003.tif \
Data/LANDSAT_MultiTempIm_clip_GapF_20141026.tif \
-out landsat_average_otb.tif \
-exp "(im1b1 + im2b1 + im3b1 + im4b1 + im5b1 + im6b1 + im7b1 + im8b1 + im9b1)/9.0"
