# Folder structure

- `/`: `Makefile`, `README.md`
- `/bin`: executables
- `/build`: compiled files (`.o`)
- `/test`: test scripts (`.cpp`, `.sh`)
- `/lib`: third party libraries (openGL, Qt, etc.)
- `/data`: images, saves, config, etc.
- `/src`: source code
- `/src/lib`: class implementations (`.cpp`)
- `/src/includes`: class headers (`.h`)

# Class structure

```cpp
class Foo {
public:
	// Constructor, destructor
	Foo(double, double, double);
	~Foo();

	// Getters
	double getX();

	// Setters
	void setX(double);

	// Methods
	void draw();

	// Static methods
	static double tripleProduct(Vector3D, Vector3D, Vector3D);

private:
	// Private methods and values
	int N;

	// Overloading methods
	bool __eq__() const;
};
```
