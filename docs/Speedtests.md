# Speedtests

In this section we try out different code snippets and get their execution time using the `time` command.

## `Vector3D` coordinates: c-style array vs triplet of doubles

We compared performance of storing `Vector3D` coordinates in a c-style array and in a triplet of doubles.\
Using the `array` library gave us horrible performance that couldn't even compete against the other tests.

### c-style

```cpp
class Vector {
public:
	Vector(double x, double y, double z) {
		coords[0] = x;
		coords[1] = y;
		coords[2] = z;
	}

	void operator += (Vector const& v) {
		coords[0] += v.coords[0];
		coords[1] += v.coords[1];
		coords[2] += v.coords[2];
		return *this;
	}

private:
	double coords[3];
};
```

### Triplet of doubles

```cpp
class Vector {
public:
	Vector(double _x, double _y, double _z) {
		x = _x;
		y = _y;
		z = _z;
	}

	void operator += (Vector const& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

private:
	double x;
	double y;
	double z;
};
```

### Results

```cpp
int main() {
	Vector v(1, 2, 3);

	for (int i(0); i < 1e9; ++i) {
		v += Vector(i, i+1, i+2);
	}

	return 0;
}
```

Results: on 1e9 iterations, no significant difference.


## Return type for operator overloading

### Return type `void`

```cpp
class Vector {
public:
	Vector(double _x, double _y, double _z) {
		x = _x;
		y = _y;
		z = _z;
	}

	void operator += (Vector const& v) {
		x += v.x;
		y += v.y;
		z += v.z;
	}

private:
	double x;
	double y;
	double z;
};
```

### Return type `Vector&`

```cpp
class Vector {
public:
	Vector(double _x, double _y, double _z) {
		x = _x;
		y = _y;
		z = _z;
	}

	Vector& operator += (Vector const& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

private:
	double x;
	double y;
	double z;
};
```

### Results

```cpp
int main() {
	Vector v(1, 2, 3);

	for (int i(0); i < 1e9; ++i) {
		v += Vector(i, i+1, i+2);
	}

	return 0;
}
```

On 1e9 iterations, return type `void` was about 0.5 seconds faster.
