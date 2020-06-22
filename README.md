
# Raw data for TRD O2

This repository collects code snippets and documents about the new data format
for the ALICE TRD in the O2 software framework.

A **Makefile** gives some hints and shortcuts to run common tasks.

## Documents

 - **RawTrackletBitsizes.ipynb** helps to understand how different field sizes
   in the new tracklet format affect the resolution.

## Utilities for old Run 1+2 data

The following utitlies can be used to understand how reading of old Run 1+2 data
files works.

 - **raw_analysis.C** shows how to use the AliRoot classes AliRawReader (or
   subclasses of it, depending on data format), AliTRDrawStream (decoder for the
   TRD specific raw data, as extracted from the files read by the AliRawReader),
   and the AliTRDdigitsArray (a horrible class that will be replaced by
   something nicer in run3). This macro basically does with run 2 data what we
   want to do with run 3 data.

 - **dumraw.C** is more basic, and just extracts from a raw data file in ROOT
 - format the TRD specific information for each super-module into a binary file.
