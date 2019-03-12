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

## Todo

- Add large scale error management -> custom `Exception` sub-classes
- Answer questions week 3
- Test performance of storing coordinates as doubles or an array
- Creation of a class `Particule`
- Creation of tests `Particule`
- Replace getters with readers inside class definition (we can trust ourselves) --> What if we change the representation from (x, y, z) to (phi, theta, rho) or (phi, rho, z). We would have to change the entire classe to cope with that change !!
