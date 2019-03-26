# Double dispatching in C++

The particle accelerator project has two facets: the physics engine and the rendering.\
The naïve solution is do something like this:

```cpp
#include <iostream>
#include <vector>

using namespace std;

class Animal {};
class Cat : public Animal {};
class Dog : public Animal {};
class Fox : public Animal {};

class Renderer {
public:
	// Normally, we should not be drawing animals, however we are here !
	// How do we solve this problem ?
	void draw(Animal const& a) { cout << "Drawing animal " << &a << endl; }
	void draw(Cat const& a) { cout << "Drawing cat " << &a << endl; }
	void draw(Dog const& a) { cout << "Drawing dog " << &a << endl; }
	void draw(Fox const& a) { cout << "Drawing fox " << &a << endl; }
};

int main() {
	Renderer engine;
	vector<Animal*> animals;
	animals.push_back(new Dog());
	animals.push_back(new Cat());
	animals.push_back(new Fox());

	for (Animal* animal : animals) {
		engine.draw(*animal);
	}
}
```

The ouput of the program is not what the user would expect:

```shell
Drawing animal 0x557557c25e70
Drawing animal 0x557557c25eb0
Drawing animal 0x557557c25e90
```

The problem is that polymorphism is _not_ applied in this situation, rather static function overloading is.\
The C++ compiler understands the type of the pointer is `Animal` and thus calls `Renderer::draw(Animal)`.

The solution to this problem is to use double dispatching. Each animal has its own `draw` function of which the sole purpose is to call the correct `Renderer` method, while maintaining polymorphism. The parent `Animal` class inherits from `Drawable` such that polymorphism includes both the simulation side (`Animal`) and drawing side (`Drawable`).

```cpp
#include <iostream>
#include <vector>

using namespace std;

/****************************************************************
 * Renderer function
 ****************************************************************/

// Prototypes that will be properly implemented later
class Animal;
class Cat;
class Dog;
class Fox;
class Drawable;

class Renderer {
public:
	void draw(Cat const& a) { cout << "Drawing cat " << &a << endl; }
	void draw(Dog const& a) { cout << "Drawing dog " << &a << endl; }
	void draw(Fox const& a) { cout << "Drawing fox " << &a << endl; }
};

/****************************************************************
 * Abstract drawable class
 ****************************************************************/

class Drawable {
protected:
	Renderer* engine;

public:
	Drawable(Renderer* engine) : engine(engine) {}

	// draw() needs to be virtual in order for Renderer overloading to take the correct type
	// By inheriting from draw() directly, all animals would be rendered from with Drawable type
	virtual void draw() const = 0;
};

/****************************************************************
 * Abstract animal class
 ****************************************************************/

// Animal needs to inherit from Drawable
// in order to access both draw() and speak() from vector<Animal*>
class Animal : public Drawable {
public:
	using Drawable::Drawable;
	virtual void speak() const = 0;
};

/****************************************************************
 * Concrete animal implementations
 ****************************************************************/

class Cat : public Animal {
	using Animal::Animal;
	void draw() const override { engine->draw(*this); }
	void speak() const override { cout << "Cat says meow" << endl; }
};
class Dog : public Animal {
	using Animal::Animal;
	void draw() const override { engine->draw(*this); }
	void speak() const override { cout << "Dog goes woof" << endl; }
};
class Fox : public Animal {
	using Animal::Animal;
	void draw() const override { engine->draw(*this); }
	void speak() const override { cout << "WHAT DOES THE FOX SAY" << endl "RING DING DING DING DING DING" << endl; }
};

/****************************************************************
 * Main
 ****************************************************************/

int main() {
	Renderer engine;
	vector<Animal*> animals;
	animals.push_back(new Dog(&engine));
	animals.push_back(new Cat(&engine));
	animals.push_back(new Fox(&engine));

	for (Animal* animal : animals) {
		animal->speak();
		animal->draw();
	}
}
```

This program gives the desired output:

```shell
Dog goes woof
Drawing dog 0x55de0ebe3e70
Cat says meow
Drawing cat 0x55de0ebe3eb0
WHAT DOES THE FOX SAY
RING DING DING DING DING DING
Drawing fox 0x55de0ebe3e90
```
