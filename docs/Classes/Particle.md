# `Particle`

## Constructors

There are two ways to initialize a particle.\
Per default, units are expected in GeV. To specify units in the SI system, add `false` at the end of the argument list.

```cpp
// Using the velocity constructor
Particle p1(Vector3D(3.00894, -0.391837, 0), Vector3D(-210200, -2.64754e8, 0), 0.938272, 1);
// Using the normalized direction + energy constructor
Particle p2(Vector3D(2.99016, -0.391837, 0), 2, Vector3D(210200, -2.64754e8, 0), 0.938272, 1);
cout << p1 << endl;
cout << p2 << endl;
p1.exertLorentzForce(Vector3D(0, 0, 7));
p2.exertLorentzForce(Vector3D(0, 0, 7));
p1.step();
p2.step();
cout << p1 << endl;
cout << p2 << endl;
```

### Using velocity only

```cpp
Particle(
	Vector3D const& pos,
	Vector3D const& speed,
	double const& mass,
	int const& charge = 1,
	bool const& unitGeV = true
);
```

### Using a normalized direction vector and energy

```cpp
Particle(
	Vector3D const& pos,
	double const& energy,
	Vector3D speed,
	double const& mass,
	int const& charge = 1,
	bool const& unitGeV = true
);
```

### Arguments

- `Vector3D pos`: initial position of the particle
- `Vector3D speed`: initial speed of the particle (if applicable)
- `double energy`: intial energy of the particle (if applicable)
- `double mass`: mass of the particle
- `int charge = 1`: charge of the particle in multiples of the elementary charge (i.e. multiples of 1 eV, charge of the electron)
- `bool unitGeV = true`: specify the units of the scalars given to the constructor

## Physics engine

### Integration step

```cpp
p.step();
```

Integrates the movement equations over a time step `dt`, which defaults to `GLOBALS::DT(1e-11)`.

### Force summation

```cpp
// Exert the force of gravity
p.exertForce(Vector3D(0, 0, 9.81*p.getMass()));
```

Exerts a force onto a particle until the next `step` call.

### Lorentz force

```cpp
p1.exertLorentzForce(Vector3D(0, 0, 7));
```

Exerts the Lorentz force on a particle traversing a magnetic field given by the `B` vector over a timestep `dt` (defaults to `GLOBALS::DT(1e-11)`).

## Getters

Getters are available for most of the attributes:

- `double getEnergy`
- `double getGamma`
- `double getMass`
- `double getCharge`
- `int getChargeNumber`
- `Vector3D getSpeed`
- `Vector3D getForces`
- `Vector3D getMoment`
- `Vector3D getPos`

## Setters

No setters are available for this class (once the particle is created, the only way attributes can change is through time steps `Particle::step`).

## String representation

```bash
Position        (3.00894, -0.391837, 0)          (m)
Speed           (-210200, -2.64754e+08, 0)       (m/s)
Gamma           2.13157                          (-)
Energy          1.99999                          (GeV)
Mass            0.938272                         (GeV/c²)
Charge          1.60218e-19                      (Coulomb)
Forces          (0, 0, 0)                        (N)
```

`std::ostream operator <<` is overloaded to stream the `Particle::to_string` representation.
