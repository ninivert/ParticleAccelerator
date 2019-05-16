#ifndef INPUT_H
#define INPUT_H

#pragma once

#include <Qt>
#include <QPoint>
#include <QCursor>
#include <vector>
#include <utility>
#include <algorithm>

/**
 * InputState enum
 * Registered -> Triggered -> Pressed
 * Unregistered -> Released
 */

enum InputState {
	InputInvalid,
	InputRegistered,
	InputUnregistered,
	InputTriggered,
	InputPressed,
	InputReleased
};

template <typename T>

/**
 * InputInstance class
 *
 * Inherits from std::pair and overwrites the == operator
 *
 * Basically writing both classes KeyInstance and ButtonInstance
 */

class InputInstance : public std::pair<T, InputState> {
public:

	/**
	 * Base class type
	 */

	typedef std::pair<T, InputState> base_class;

	/**
	 * Default constructor initializes the std::pair with InputInvalid
	 */

	InputInstance(T value) : base_class(value, InputInvalid) {}

	/**
	 * Default constructor initializes the std::pair with a given state
	 */

	InputInstance(T value, InputState state) : base_class(value, state) {}

	/**
	 * operator == is for std::find included from <algorithm>
	 */

	bool operator == (InputInstance const& rhs) const {
		return this->first == rhs.first;
	}
};

// Instance types
typedef InputInstance<Qt::Key> KeyInstance;
typedef InputInstance<Qt::MouseButton> ButtonInstance;

// Container types
typedef std::vector<KeyInstance> KeyContainer;
typedef std::vector<ButtonInstance> ButtonContainer;

/**
 * (static) Input class
 */

class Input {
public:

	/****************************************************************
	 * State checking
	 ****************************************************************/

	/**
	 * Returns whether a keyboard key has been triggered
	 */

	static bool isKeyTriggered(Qt::Key key);

	/**
	 * Returns whether a keyboard key has been pressed
	 */

	static bool isKeyPressed(Qt::Key key);

	/**
	 * Returns whether a keyboard key has been released
	 */

	static bool isKeyReleased(Qt::Key key);

	/**
	 * Returns whether a mouse button has been triggered
	 */

	static bool isButtonTriggered(Qt::MouseButton button);

	/**
	 * Returns whether a mouse button has been pressed
	 */

	static bool isButtonPressed(Qt::MouseButton button);

	/**
	 * Returns whether a mouse button has been released
	 */

	static bool isButtonReleased(Qt::MouseButton button);

	/**
	 * Returns the InputState of a mouse button
	 */

	static InputState getButtonState(Qt::MouseButton button);

	/**
	 * Returns the InputState of a keyboard key
	 */

	static InputState getKeyState(Qt::Key key);

	/**
	 * Return the mouse position relative to the window
	 */

	static QPoint getMousePosition();

	/**
	 * Returns the differences between the current mouse position and last since Input::update was called
	 */

	static QPoint getMouseDelta();

	/**
	 * Resets the mouse position difference to 0 without affecting mouse position
	 */

	static void resetMouseDelta();

private:

	/**
	 * Update mouse delta, mouse buttons and keyboard keys
 	 */

	static void update();

	/**
	 * Update the current state of the keys
	 *
	 * Registered -> Triggered -> Pressed
	 *
	 * Unregistered -> Released
	 */

	template <typename TPair> static void updateStates(TPair& instance);

	/**
	 * Modify the templated container (here, std::vector)
	 * to remove keys as needed
	 */

	template <typename Container> static void updateContainer(Container& container);

	/**
	 * Check whether a key should be removed
	 */

	template <typename TPair> static bool checkReleased(TPair const& instance);

	/**
	 * Adds key to keyInstances if not there already
	 */

	static void registerKeyPress(int key);

	/**
	 * Removes a key from keyInstances if present
	 */

	static void registerKeyRelease(int key);

	/**
	 * Adds mouse button to buttonInstances if not there already
	 */

	static void registerMousePress(Qt::MouseButton button);

	/**
	 * Removes mouse button from keyInstances if present
	 */

	static void registerMouseRelease(Qt::MouseButton button);

	/**
	 * Clears keyInstances and buttonInstances
	 */

	static void reset();

	/**
	 * Window, which actually registers inputs, can access private methods and data members
	 */

	friend class Window;

	/****************************************************************
	 * Utility functions
	 ****************************************************************/

	/**
	 * Finds a given key in keyInstances
	 */

	static KeyContainer::iterator findKey(Qt::Key key);

	/**
	 * Finds a given mouse button in keyInstances
	 */

	static ButtonContainer::iterator findButton(Qt::MouseButton key);

	/****************************************************************
	 * Trackers (inline to initialize directly)
	 ****************************************************************/

	/**
	 * Vector of all pressed keys and their states
	 */

	static inline KeyContainer keyInstances;

	/**
	 * Vector of all pressed mouse buttons and their states
	 */

	static inline ButtonContainer buttonInstances;

	/**
	 * Current mouse position relative to Window
	 */

	static inline QPoint mouseCurrPosition;

	/**
	 * Previous mouse position relative to Window
	 */

	static inline QPoint mousePrevPosition;

	/**
	 * Difference between current and previous mouse positions
	 */

	static inline QPoint mouseDelta;
};

#endif
