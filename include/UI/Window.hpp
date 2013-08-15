#ifndef UI_WINDOW_H
#define UI_WINDOW_H 1

#include <UI/Widget.hpp>

namespace ui
{

class Window : public Widget
{

#define UI_SIG_TITLE_CHANGED     "titleChanged"
#define UI_SIG_RESIZABLE_CHANGED "resizableChanged"
#define UI_SIG_SIZE_CHANGED      "sizeChanged"
#define UI_SIG_POSITION_CHANGED  "positionChanged"

public:
	Window(const char *title=0, int width=-1, int height=-1, Widget *parent = 0);
	String title() const;
	void setTitle(const String &value);
	bool resizable() const;
	void setResizable(bool value);
	Size size() const;
	void setSize(const Size &value);
	Point position() const;
	void setPosition(const Point &value);
};

} // namespace ui

#endif // UI_WINDOW_H
