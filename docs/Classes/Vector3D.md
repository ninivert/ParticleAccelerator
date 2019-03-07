# `Vector3D`

## Constructor

```cpp
Vector3D();
Vector3D(double const& _x, double const& _y, double const& _z);
Vector3D(Vector3D const& v);
```

An instance of `Vector3D` can be initialized with

- nothing so the vector will be initialized with `(0.0, 0.0, 0.0)`, or
- a triplet of `double`s representing the vector parameters, or
- an existing instance of `Vector3D`, of which a copy will be made.

## Getters

```cpp
Vector3D v(1, -2, 6);
v.getY(); // -2
```

- `double get<X>()`
	- Arguments: none
	- Returns: `double`, parameter of the vector

## Setters

```cpp
Vector3D v(1, -2, 6);
v.setY(-9);
v.getY(); // -9
```

- `void set<X>(double)`:
	- Arguments
		- `double`: value to assign the parameter
	- Returns: none

## String representation

```cpp
Vector3D v(1, -2, 6);
std::cout << v.stringify << endl; // (1, -2, 6)
```

- `std::string stringify()`:
	- Arguments: none
	- Returns: `string` representation of the vector.

## Arithmetic operations

```cpp
Vector3D v1(2, -5, 6);
Vector3D v2(3, -7, -2);
Vector3D v3(4, 7, -1);
v1 + v2; // Vector3D(5, -12, 4)
v1 - v2; // Vector3D(-1, 2, 8)
v1 += v2 // Vector3D(5, -12, 4) in v1
v1 -= v2 // Vector3D(2, -5, 6) in v1
v1 * 2; // Vector3D(4, -10, 12)
v1 *= 2; // Vector3D(4, -10, 12) in v1
v1 / 3; // Vector3D(0.666667, -1.666667, 2)
v1 /= 3; // Vector3D(0.666667, -1.666667, 2) in v1
v1 * v2; // 29
(v1 ^ v2); // Vector3D(52, 22, 1)
Vector3D::tripleProduct(v1, v2, v3); // 361
```

Operators `+`, `+=`, `-`, `-=`, `*` and `^` are overloaded and correspond to the following operations between two instances of `Vector3D`:

- `+`: addition, returns: `Vector3D`
- `+=`: addition, modifies and returns: `Vector3D`
- `-`: substraction, returns: `Vector3D`
- `-=`: substraction, modifies and returns: `Vector3D`
- `*`: dot product, returns: `double`
- `^`: cross product, returns: `Vector3D`

> __WARNING__: the `^` operator has a low priority and is evaluated after relational operators. Use parantheses to prioritize the evaluation of `^`. See [the reference](https://en.cppreference.com/w/cpp/language/operator_precedence) for more information.

Scalar multiplication is also overloaded with the `*`, `*=`, `/` and `/=` operators (returns: `Vector3D`).

The `Vector3D` class implements a static function `double Vector3D::tripleProduct` to evaluate the triple product (volume) of three vectors.

- `Vector3D::tripleProduct(Vector3D, Vector3D, Vector3D)`:
	- Arguments: three `Vector3D` instances
	- Returns: `double` corresponding to `v1 * (v2 ^ v3)`

## Boolean operations

```cpp
Vector3D v1(1, 5, -4);
Vector3D v2(1, 5, -4);
v1 == v2; // true
```

The `==` operator is overloaded and returns `true` iff all the vector parameters coincide.

## Assignment operations

```cpp
Vector3D v1(1, 2, -6);
Vector3D v2;
v2 = v1;
v2; // Vector3D(1, 2, -6)
```

You can assign the parameters of a vector to another without copying it.

## Norm and normalization

```cpp
Vector3D v(4, -3, 0);
v.norm(); // 5
v.normSquared(); // 25
~v; // Vector3D(0.8, -0.6, 0)
v.norm(); // 1
```

`norm` and `normSquared` return the norm and the squared norm of the vector, respectively. Use the `normalize` method to make it a unit vector pointing in the same direction.

- `double norm()`:
	- Arguments: none
	- Returns: `double`, norm of the vector
- `double normSquared()`:
	- Arguments: none
	- Returns: `double`, squared norm of the vector

The `~` operator is overloaded and makes the `Vector3D` instance a unit vector

## Rotation

```cpp
Vector3D v1(4, -3, 0);
Vector3D v2(9, 12, 0);

// rotate v1 from 180° around the axis v2
v1.rotate(v2, M_PI); // Vector3D(-4, 3, 0)
```

`rotate` modifies and returns `Vector3D` by turning it from `alpha` **radians** around an axis `axis`

> __WARNING__: The angles are in RADIANS
