# Examples

## Vector3D

```cpp
Vector3D v1(2, -5, 6);
v1.getY(); 								// -5

Vector3D v2(3, -7, -2);
Vector3D v3(4, 7, -1);
v1 += v2; 								// Vector3D(5, -12, 4) in v1
v1 -= v2; 								// Vector3D(2, -5, 6) in v1
v1 ^= v2; 								// Vector3D(52, 22, 1) in v1
v1 *= 2; 								// Vector3D(4, -10, 12) in v1
v1 /= 3; 								// Vector3D(0.666667, -1.666667, 2) in v1
v1 = Vector3D(2, -5, 6);

v1 + v2; 								// Vector3D(5, -12, 4)
v1 - v2; 								// Vector3D(-1, 2, 8)
v1 * 2; 								// Vector3D(4, -10, 12)
v1 / 3; 								// Vector3D(0.666667, -1.666667, 2)
v1 * v2; 								// 29
(v1 ^ v2); 								// Vector3D(52, 22, 1)

std::cout << v1.to_string() << endl; 	// (2, -5, 6)

Vector3D::tripleProduct(v1, v2, v3); 	// 361

v1 = Vector3D(4, -3, 0);
v1.norm(); 								// 5
v1.normSquared(); 						// 25
~v1; 									// Vector3D(0.8, -0.6, 0)
v1.norm(); 								// 1

v1 = Vector3D(4, -3, 0);
v2 = Vector3D(9, 12, 0);

// rotate v1 from 180° around the axis v2
v1.rotate(v2, M_PI); 					// Vector3D(-4, 3, 0)

v1 = Vector3D(2, -5, 6);
v2 = Vector3D(2, -5, 6);
v1 == v2; 								// true
v1 != v2; 								// false
```

## Particle

```cpp
// Using the velocity constructor
Particle p1(Vector3D(3.00894, -0.391837, 0), Vector3D(-210200, -2.64754e8, 0), 0.938272, 1);

// Using the normalized direction + energy constructor
Particle p2(Vector3D(2.99016, -0.391837, 0), 2, Vector3D(210200, -2.64754e8, 0), 0.938272, 1);

cout << p1 << endl;

p1.exertLorentzForce(Vector3D(0, 0, 7));
p1.step();

cout << p1 << endl;
```
```shell
Position        (3.00894, -0.391837, 0)          (m)
Speed           (-210200, -2.64754e+08, 0)       (m/s)
Gamma           2.13157                          (-)
Energy          1.99999                          (GeV)
Mass            0.938272                         (GeV/c²)
Charge          1.60218e-19                      (Coulomb)
Forces          (0, 0, 0)                        (N)
```
Forces = (0, 0, 0) because we set forces to null

## `exceptions.h`

```cpp
void child(double x) {
	// something went terribly wrong
	// did someone divide by 0 again ?
	ERROR(EXCEPTIONS::DIV_0);
}

void parent() {
	try {
		// ...
		// parent depends child treating some value
		child(5);
		// ...
	} catch (OurException& e) {
		// Retrow the exception for the call stack
		ERROR(e.what());
	}
}

int main() {
	try {
		parent();
	} catch (OurException& e) {
		cout << e.what() << endl;
	}

	return 0;
}
```

The following code yields

```
At file test/src/testException.cpp, line 20
	At file test/src/testException.cpp, line 9
	Division by 0
```

## `converter.h`

```cpp
// 1 eV = 1.60217653e-19 Joules
CONVERT::EnergyEVtoSI(1); // 1.60217653e-19

// 0.938272 GeV/c² (mass of the proton)
CONVERT::MassGeVtoSI(CONSTANTS::M_PROTON);		// 1.67262e-27 kg

// 9.10938e-31 kg (mass of the electron)
CONVERT::MassSItoGeV(9.10938e-31); 				// 5.10999e-4 GeV/c²

// 9.10938e-31 kg (mass of the electron)
CONVERT::MassSItoEV(9.10938e-31); 				// 510999 eV/c²

// (1, 2, -1) GeV/c (momentum)
CONVERT::MomentumGeVtoSI(Vector3D(1, 2, -1));	// (5.34429e-19, 1.06886e-18, -5.34429e-19) kg*m/s
```
