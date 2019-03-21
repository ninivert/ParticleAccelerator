# Journal

## Week 1

- Added `Vector3D` class
- Wrote header file for `Vector3D`
- Wrote `Vector3D` documentation
- Wrote standardized tests template
- Wrote tests for `Vector3D`
- Made `constants.h` file
- Setup compilation and `Makefile`

## Week 2

- `Makefile` template done
- Change order of `const double` to `double const`
- Use `v.getX()` in class functions instead of `v.x()`
- Change `Vector3D` (tests) to `testVector3D`
- Change `Vector3D` constructor to a default constructor

## Week 3

- Change constants to `inline` according to the C++17 norm
- Rename `stringify` to `to_string` to comply to the C++ norm
- Improved `Makefile` style and added `dir` command to create required directories
- Check `Vector3D` class overloading for optimization
- Move `Vector3D `overloading from `__method__` directly to the operator
- Added physical constants in `globals.h`
- [Speedtests](#speedtests)
- Creation of a class `Particule`
- Added physical constants namespace

## Week 4

- Fixed `Particle::step` function -> units used were incorrect
- Creation of tests for `Particle` and `Converter.h`
- Decided on energy vs momentum -> we used momentum (see [Réponses](#semaine-3))
- Added padding for `Vector3D` and particle display (ostream)
- Added 2 constructors for particle class
- Added [`CONVERT`](#convert.h) namespace to easily convert from SI units to GeV and reciprocally
- Added `STYLES` namespace for unified text output
- Finish tests for `Particle`

## Todo

- Add large scale error management -> custom `Exception` sub-classes
- Add accelerator class
- Add element class
	- unique_ptr for next element
	- C-ptr to know in which `Element` we are
		- use `class Element;` or `class Particle;` in header files
	- magnet sub-class
	- electric sub-class
- Add relatist mass to particle
- Doxygen
- Polymorphism pointer in accelerator -> define class destructor
