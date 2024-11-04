This folder contains a .json file containing information about each headerfile/device in the
`external/waveshare/epaper/e-Paper` folder which can then be used to create **DrawTarget** header files for use by the epaper
API.

Each header file was parsed using the `scripts/capabilitiesparser/Parse.py` script which uses the ChatGPT 4o model to read
each header file and determine what color channels are supported, what functions are used for initializing, drawing, etc...

In addition to this, extra information from example C files are also used to determine things like color scale, rotation, and
what bitmap function is used for displaying images. All these things help create header files that are more likely to work
without needing to manually fix anything.

These example files can be obtained from:
https://github.com/waveshareteam/e-Paper/tree/master/RaspberryPi_JetsonNano/c/examples

See `scripts/capabilitiesparser/README.md` if you want to learn how to generate this folder again or want more information on
the format of the JSON files generated.
