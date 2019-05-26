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
	- `getField`
	- String representation
- Updated every constructor that inherits from `Drawable` to also init `Renderer * engine_ptr`
- Added suffix `_ptr` to all pointers and vector of pointers
- Moved `Particle::step()` call to `exertLorentzForce` to `Accelerator::step()`
- Transfered object property to inside the class
- Polymorphic copy
- Changed `TextRenderer::TextRenderer()` to construct directly with a filename (or nothing)
- `Accelerator::addParticle` bind the Particle to the first element of the Accelerator
- Reviewed `exerciceP9`
- Reimplemented the method `Element::isInNextElement()` not here anymore
	- pure virtual in `Element`
	- projection in `Straight`
	- method with angles and tan (compare with the one between the input and output position) in `Dipole`
- Changed `Frodo::getField()` : remove the +0.05 at the end (needed for compilation uwu)
- Rewrote `Element::updatePointedElement()`

## Stage 7

- `Beam` class
	- creation of the `Beam` (constructor initializing the particles_ptr -> 1st)
	- convention if emittance is 0 (ask Chap)
	- adapt the `Accelerator` class
- Improve `Drawable`: fuse `draw` and `drawTo` to automatically search for the good engine
- ExerciceP10
- Removed useless consts in `Vector3D` and `Particle` according to warnings (non-class type rvalues are not modifiable (inherited from C), and thus the Standard says non-class type rvalues are never const-qualified (right-most const was ignored even tho specified by you) since the const would be kinda redundant.) [link1](https://stackoverflow.com/questions/1607188/why-is-a-type-qualifier-on-a-return-type-meaningless) and [link2](https://stackoverflow.com/questions/1134237/pedantic-gcc-warning-type-qualifiers-on-function-return-type)
- Move Makefile to qmake
- Cleanup the facking extra dependencies
- ExerciceP13
- add draw for vector3d
- bug with methodChapi = false corrected
- Particle can turn in both direction
	- Do not work with all combination of speed and charge
	- To change the direction, change BOTH signs of speed and charge

## Stage 8

- bool beamFromParticle for Beam::Beam() (2 different representations of Beams)
- update correct dependencies in header files -> use bundles
- added fps counter
- added antialising
- added transparency (is a bit buggy though) [solution ?](https://stackoverflow.com/questions/3388294/opengl-question-about-the-usage-of-gldepthmask) -> just force particles to be drawn + removed inside vertices
- Graphics documentation
- Dynamic scene lighting
- Solve problem where app.pro does not update when something in commom updates: use `make && cd apps/app/ && make -B && cd ../.. && bin/app.bin` `¯\_(ツ)_/¯`
- Return type for getters: const, const reference ? -> const ref for getters, const for queries (if temp object is computed)
- Framerate-independant movement
- add proton, antiproton and electron sub-class
- fixed polymorphism not being applied on Particle in Beam constructor
- fixed polymorphism not being applied on Particle in Accelerator::addParticle
- ExerciceP14 (KÄÄÄÄÄÄÄÄÄÄÄÄÄÄSE)
- Added simulation speed control
- Pause using Space
- Return const string in `to_string`
- Add pause button
- Update `README.md`

## Todo

- Calibrate accelerator to our settings
- Document window.h
- YEEET sucky wucky particle constructor
- verify virtual destructors
