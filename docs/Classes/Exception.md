# `exceptions.h`

We defined a compiler macro `ERROR(char msg[])` which throws a new instance of `OurException`, sub-class of `std::runtime_error`.\
`OurException` provides a simple wrapper to display file name and line number along with the error message.\
In this example, we throw a division by 0 (`DIV_0`) error that we catch then re-throw to get the error callstack.

Available messages in the `EXCEPTIONS` namespace:

- `DIV_0` : Division by 0
- `BAD_ORIENTATION` : (in [Element](#element)) Input and output positions are colinear

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
