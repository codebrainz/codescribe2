#ifndef UI_APP_H
#define UI_APP_H 1

#include <UI/Types.hpp>
#include <UI/Window.hpp>

namespace ui
{

class App : public Object
{

#define UI_SIG_QUIT_ON_LAST_WINDOW_CHANGED "quitOnLastWindowChanged"

public:
	App(int *argc=0, char ***argv=0, const char *uniqueName=0);
	virtual ~App();
	int run();
	void quit();
	const Set<Window*> &windows() const { return windows_; }
	void addWindow(Window *win);
	void removeWindow(Window *win);
	Window *activeWindow() const;
	bool quitOnLastWindow() const;
	void setQuitOnLastWindow(bool value);
	virtual void ref() { }
	virtual void unref() { }

private:
	Set<Window*> windows_;
	bool quitOnLastWindow_;
};

} // namespace ui

#endif // UI_APP_H
