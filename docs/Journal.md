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
- Used C-ptr to for `Particle` and `Element` class
- Used `class Element;` or `class Particle;` in header files to resolve circular header definitions
- Review the `linkNext` function (create a method in `Element` to make the "full circle" (or not) i.e. the first `Element` has to point on the last one and vice versa (without creating a new Element))
- Add [large scale error management](#exceptions.h) -> custom `Exception` sub-classes: Throw division by 0 errors
- Add accelerator class
- Add element class
	- Dipole sub-class

## Week 5

- Doxygen
- Quadrupole sub-class
- Straight sub-class
- Polymorphism pointer in accelerator -> define class destructor
- Beware the copy constructor of `Element` (cause : pointers)
- Finish documentation until Element class
- Finish tests for Element
- NULLPTR exception in class Element
- When a particle gets out of an Element, it points to the next Element
- test the passPartoNextElement function
- test the updateElement function

## Todo

- make_circle function in accelerator ?
- init_particles for the pointer of particles to be initialized with the 1st element (or the closest one)
- Force the fact that 2 touching Elements must have the same posOut (in init) and posIn
- Rename Element::isOut
- Rename Element::passPartoNextElement
- Drawable class and its derivatives (oh no!)
- Accelerator::step() needs to take into account the fact that particles are leaving the accelerator (not in an Element anymore)

## Questions

- Add relativist mass to particle ?
- Si `void f()` et `void f() const` sont différents, comment les distiguer lors d'un appel ?
- Comment detecter a quelle sous-classe appartient une instance ?
- Doit on rendre un `README.md` ?
