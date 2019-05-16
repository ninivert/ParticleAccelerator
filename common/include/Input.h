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
	// State checking
	static bool isKeyTriggered(Qt::Key key);
	static bool isKeyPressed(Qt::Key key);
	static bool isKeyReleased(Qt::Key key);
	static bool isButtonTriggered(Qt::MouseButton button);
	static bool isButtonPressed(Qt::MouseButton button);
	static bool isButtonReleased(Qt::MouseButton button);
	static InputState getButtonState(Qt::MouseButton button);
	static InputState getKeyState(Qt::Key key);
	static QPoint getMousePosition();
	static QPoint getMouseDelta();

	// For window controls
	static void resetMouseDelta();

private:
	// State updating
	static void update();
	template <typename TPair> static void updateStates(TPair& instance);
	template <typename Container> static void updateContainer(Container& container);
	template <typename TPair> static bool checkReleased(TPair const& instance);
	static void registerKeyPress(int key);
	static void registerKeyRelease(int key);
	static void registerMousePress(Qt::MouseButton button);
	static void registerMouseRelease(Qt::MouseButton button);
	static void reset();
	friend class Window;

	// Utility functions
	static KeyContainer::iterator findKey(Qt::Key key);
	static ButtonContainer::iterator findButton(Qt::MouseButton key);

	// Trackers (inline to initialize directly)
	static inline KeyContainer keyInstances;
	static inline ButtonContainer buttonInstances;
	static inline QPoint mouseCurrPosition;
	static inline QPoint mousePrevPosition;
	static inline QPoint mouseDelta;
};

#endif
