/*
 * Mouse.h
 *
 *  Created on: Mar 16, 2013
 *      Author: Tyler
 */

#ifndef MOUSE_H_
#define MOUSE_H_

#include <glm/glm.hpp>

namespace ts {

class Mouse {
public:
	enum Button/* : char*/{
		Button0,
		Button1,
		Button2,

		buttonCount
	};

	enum MouseButtonEventType/* : char*/ {
		defaultEventType,
		buttonPressed,
		buttonReleased
	};

	static void init();

	static void setPosition(int x, int y);
	static glm::vec2 getPosition();
	static void movePosition(int dx, int dy);

	static void setLastMove(int dx, int dy);
	static glm::vec2 getLastMove();

	static void setMouseWheelDelta(int delta);
	static int getMouseWheelDelta();

	static void setLocked(bool isLocked);
	static bool isLocked();

	static void setMouseButton(int button, bool value);
	static bool isMouseButtonPressed(Button button);

	static void setMouseButtonEvent(int button, MouseButtonEventType type);
	static MouseButtonEventType checkMouseButtonEvent(Button button);

	static void clear();
private:
	Mouse();
	Mouse(const Mouse& mouse);
	Mouse& operator=(Mouse const& mouse);
	virtual ~Mouse();

	static bool locked;
	static glm::vec2 position;
	static int lastDX, lastDY;

	static bool buttons[buttonCount];
	static MouseButtonEventType buttonEvents[buttonCount];
	static int mouseWheelDelta;
};

} /* namespace ts */
#endif /* MOUSE_H_ */
