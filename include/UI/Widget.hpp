//
// Abstract Base Widget - Base of all widgets that use graphical resources.
//

#ifndef UI_WIDGET_H
#define UI_WIDGET_H 1

#include <UI/Object.hpp>

namespace ui
{

// Base of all widgets that use graphics resources (windows).
class Widget : public Object
{

#define UI_SIG_VISIBLE_CHANGED "visibleChanged"
#define UI_SIG_ENABLE_CHANGED  "enabledChanged"

public:
	Handle handle() const { return handle_; }
	Widget *parent() const { return parent_; }
	bool operator==(const Widget &other);
	bool operator!=(const Widget &other);
	void update();
	bool isVisible() const;
	void setVisible(bool value);
	void show() { setVisible(true); }
	void hide() { setVisible(false); }
	bool isEnabled() const;
	void setEnabled(bool value);
	void enable() { setEnabled(true); }
	void disable() { setEnabled(false); }

protected:
	Widget(Handle handle, Widget *parent = 0);
	virtual ~Widget();
private:
	Handle handle_;
	Widget *parent_;
};

} // namespace

#endif // UI_WIDGET_H
