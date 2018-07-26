# SimulationBRM
Simulate particle tracking in the BigRedMagnet and/or extract the momentum from the deflection

The measured magnetic field profiles for various currents are located in md_corr_edit, measured by the machine group.

The Boris Algorithm (see e.g. [here](https://www.particleincell.com/2011/vxb-rotation/)) is used for a reliable propagation in the magnetic field.

This software can be used as a python library, or include the corresponding headers.

Two examples/executables are implemented in C++, one in python to demonstrate the usage as library.


## C++

To compile the C++ executables, do
```
make cc
```
to compile both or
```
make getDeflection
make findMomentum
```
for separate compilations.

### getDeflection

Calculate the deflection (position in x and angle) for a given setup:
```
./BRMeval [momentum in GeV] [magnet current in A] [end of tracking in mm]
```
Note: The end of tracking is defined in reference to the center of the magnet (z=1166 mm in the magnetic field map). The magnetic field (map) extents to (center + ~1160 mm).


### findMomentum

Find the momentum for a measured particle from its deflection angle and the current of the BRM:
```
./findMomentum [deflection angle in radian] [magnet current in A]
```

## python

For installing the python library, the boost python libraries have to be installed (libboost-python-dev). To install, do
```
make shared
```
This will create `measurement.so`. In any python program, use
```
import measurement
```
to load the library. As an example, see `findMomentum.py`.

There is currently no python equivalent to the deflection calculator. Feel free to contribute :-)
