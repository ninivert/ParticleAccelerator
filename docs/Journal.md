# Journal

## Stage 1

- Added `Vector3D` class
- Wrote header file for `Vector3D`
- Wrote `Vector3D` documentation
- Wrote standardized tests template
- Wrote tests for `Vector3D`
- Made `constants.h` file
- Setup compilation and `Makefile`

## Stage 2

- `Makefile` template done
- Change order of `const double` to `double const`
- Use `v.getX()` in class functions instead of `v.x()`
- Change `Vector3D` (tests) to `testVector3D`
- Change `Vector3D` constructor to a default constructor

## Stage 3

- Change constants to `inline` according to the C++17 norm
- Rename `stringify` to `to_string` to comply to the C++ norm
- Improved `Makefile` style and added `dir` command to create required directories
- Check `Vector3D` class overloading for optimization
- Move `Vector3D `overloading from `__method__` directly to the operator
- Added physical constants in `globals.h`
- Speedtests
- Creation of a class `Particule`
- Added physical constants namespace

## Stage 4

- Fixed `Particle::step` function -> units used were incorrect
- Creation of tests for `Particle` and `Convert`
- Decided on energy vs momentum -> we used momentum (see Réponses)
- Added padding for `Vector3D` and Particle display (ostream)
- Added 2 constructors for Particle class
- Added `CONVERT` namespace to easily convert from SI units to GeV and reciprocally
- Added `STYLES` namespace for unified text output
- Finish tests for `Particle`
- Used C-ptr to for `Particle` and `Element` class
- Used `class Element;` or `class Particle;` in header files to resolve circular header definitions
- Review the `linkNext` function (create a method in `Element` to make the "full circle" (or not) i.e. the first `Element` has to point on the last one and vice versa (without creating a new Element))
- Add large scale error management -> custom `Exception` sub-classes: Throw division by 0 errors
- Add Accelerator class
- Add Element class
- Add Dipole sub-class

## Stage 5

- Doxygen
- Quadrupole sub-class
- Straight sub-class
- Polymorphism pointer in Accelerator -> define class destructor
- Beware the copy constructor of `Element` (cause : pointers)
- Finish documentation until Element class
- Finish tests for Element
- NULLPTR exception in class Element
- When a Particle gets out of an Element, it points to the next Element
- Test the `Element::updatePointedElement` function
- Test the `Accelerator::updateParticleElement` function
- Changed every include header in `.h` files to a forward declaration to resolve circular conflicts from HELL
- Bundle up dependencies on header files
- Rename `Element::isInWall`
- Answer questions
- Drawable class and its inheritance
- `Accelerator::closeElementLoop` method
- Review `Accelerator` documentation
- Review `Particle` documentation
- Review `Dipole` documentation
- Review `Quadrupole` documentation
- Review `Straight` documentation
- In Particle, why check if `B` is not null (see Particle documentation) ?
- Switched places of arguments in `Dipole` constructor to be more coherent with the other `Element` constructors
- Make `exerciceP9.cpp`
- [Verify precision in `Particle` class](https://moodle.epfl.ch/mod/forum/discuss.php?d=15995) -> precision is up to \~9-10 digits, errors are due Euler integration (with correction, which itself comes with some level of imprecision) and display, which has to convert units.
- In Particle, why check if `B` is not null (see Particle documentation)
- `Accelerator::step()` needs to take into account the fact that Particles are leaving the Accelerator (not in an Element anymore)
- Implement textual `Renderer`
	- Different `iostream`s
	- Prevent drawing on `nullptr`
- Significantly improved `makefile`

## Stage 6

- Update `testAccelerator.cpp`
- Make `README.md`
- Implement `FODO`
	- Constructor
	- String representation
- Update every constructor that inherits from `Drawable` to also init `Renderer * engine_ptr`
- Added suffix `_ptr` to all pointers and vector of pointers

## Todo

- Move `Particle::step()` call to `exertLorentzForce` to `Accelerator::step()`
- Transfer object property to inside the class
- Polymorphic copy
- Review exercice9 and `EXCEPTIONS::BAD_DIRECTION`
- `FODO`
	- `getField`
	- Link elements together
- init_Particles for the pointer of Particles to be initialized with the 1st Element (or the closest one)
- Update `README.md`
- je veux me tuer !
- Change textRenderer::textRenderer() to construct directly with a filename (or nothing)

## Questions

- Add relativist mass to Particle ?
- Do we need to specify a virtual destructor on all parent classes (aka `Drawable`) for destruction to correctly take place ?
- Problem with exerciceP9 ?
