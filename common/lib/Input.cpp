#include "include/bundle/Input.bundle.h"

/*******************************************************************************
 * Helper functions
 ******************************************************************************/

KeyContainer::iterator Input::findKey(Qt::Key key) {
	// Returns an iterator to the first element in the range [first,last) that compares equal to val.
	// If no such element is found, the function returns last.
	return std::find(keyInstances.begin(), keyInstances.end(), key);
}

ButtonContainer::iterator Input::findButton(Qt::MouseButton key) {
	return std::find(buttonInstances.begin(), buttonInstances.end(), key);
}

template <typename TPair> void Input::updateStates(TPair& instance) {
	switch (instance.second) {
		case InputRegistered:
		instance.second = InputTriggered;
		break;
		case InputTriggered:
		instance.second = InputPressed;
		break;
		case InputUnregistered:
		instance.second = InputReleased;
		break;
		default:
		// Other instance types
		break;
	}
}

template <typename TPair> bool Input::checkReleased(TPair const& instance) {
	return instance.second == InputReleased;
}

template <typename Container> void Input::updateContainer(Container& container) {
	// typename here is letting the compiler know that value_type is a type and not an attribute of Container
	// Here we are attributing a typedef for cleaner code
	// In STL, vector are a type of container and have value_type and iterator
	typedef typename Container::iterator Iter;
	typedef typename Container::value_type TPair;

	// Remove old data using erase-remove idiom
	// https://en.wikipedia.org/wiki/Erase%E2%80%93remove_idiom
	Iter remove = std::remove_if(container.begin(), container.end(), &checkReleased<TPair>);
	container.erase(remove, container.end());

	// Update existing data
	std::for_each(container.begin(), container.end(), &updateStates<TPair>);
}

/****************************************************************
 * Getters
 ****************************************************************/

bool Input::isKeyTriggered(Qt::Key key) { return getKeyState(key) == InputTriggered; }
bool Input::isKeyPressed(Qt::Key key) { return getKeyState(key) == InputPressed; }
bool Input::isKeyReleased(Qt::Key key) { return getKeyState(key) == InputReleased; }
bool Input::isButtonTriggered(Qt::MouseButton button) { return getButtonState(button) == InputTriggered; }
bool Input::isButtonPressed(Qt::MouseButton button) { return getButtonState(button) == InputPressed; }
bool Input::isButtonReleased(Qt::MouseButton button) { return getButtonState(button) == InputReleased; }
QPoint Input::getMousePosition() { return QCursor::pos(); }
QPoint Input::getMouseDelta() { return mouseDelta; }

InputState Input::getKeyState(Qt::Key key) {
	KeyContainer::iterator it = findKey(key);
	// Iterator returns last if no element has been found
	return (it != keyInstances.end()) ? it->second : InputInvalid;
}

InputState Input::getButtonState(Qt::MouseButton button) {
	ButtonContainer::iterator it = findButton(button);
	// Iterator returns last if no element has been found
	return (it != buttonInstances.end()) ? it->second : InputInvalid;
}

/****************************************************************
 * Setters
 ****************************************************************/

void Input::resetMouseDelta() {
	mousePrevPosition = mouseCurrPosition = QCursor::pos();
	mouseDelta = QPoint();
}

/****************************************************************
 * Logic
 ****************************************************************/

void Input::update() {
	// Update Mouse Delta
	mousePrevPosition = mouseCurrPosition;
	mouseCurrPosition = QCursor::pos();
	mouseDelta = mouseCurrPosition - mousePrevPosition;

	// Update KeyState values
	updateContainer(buttonInstances);
	updateContainer(keyInstances);
}

void Input::registerKeyPress(int key) {
	KeyContainer::iterator it = findKey((Qt::Key)key);
	if (it == keyInstances.end()) {
		keyInstances.push_back(KeyInstance((Qt::Key)key, InputRegistered));
	}
}

void Input::registerKeyRelease(int key) {
	KeyContainer::iterator it = findKey((Qt::Key)key);
	if (it != keyInstances.end()) {
		it->second = InputUnregistered;
	}
}

void Input::registerMousePress(Qt::MouseButton button) {
	ButtonContainer::iterator it = findButton(button);
	if (it == buttonInstances.end()) {
		buttonInstances.push_back(ButtonInstance(button, InputRegistered));
	}
}

void Input::registerMouseRelease(Qt::MouseButton button) {
	ButtonContainer::iterator it = findButton(button);
	if (it != buttonInstances.end()) {
		it->second = InputUnregistered;
	}
}

void Input::reset() {
	keyInstances.clear();
	buttonInstances.clear();
}
