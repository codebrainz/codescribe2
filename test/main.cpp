#include <UI/App.hpp>
#include <cstdio>

int main(int argc, char *argv[])
{
	ui::App app(&argc, &argv, "org.foo.bar");
	ui::Window *win = new ui::Window("Hello World", 640, 480);

	app.addWindow(win);
	win->show();

	return app.run();
}
