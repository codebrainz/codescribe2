#include <UI/App.hpp>
#include <utility>
#include <gtk/gtk.h>

namespace ui
{

App::App(int *argc, char ***argv, const char *uniqueName)
	: Object(), quitOnLastWindow_(true)
{
	gtk_init(argc, argv);
	addSignal(UI_SIG_QUIT_ON_LAST_WINDOW_CHANGED);
}

App::~App()
{
	for (Set<Window*>::iterator it = windows_.begin(); it != windows_.end(); ++it)
		removeWindow(*it);
}

int App::run()
{
	gtk_main();
	return 0; // FIXME: have a useful result code
}

void App::quit()
{
	gtk_main_quit();
}

struct Data {
	App *app;
	Window *win;
	Data(App *a, Window *w) : app(a), win(w) { }
};

static void onWindowDestroyed(GtkWindow *win, Data *data)
{
	data->app->removeWindow(data->win);
	delete data;
}

void App::addWindow(Window *win)
{
	std::pair<Set<Window*>::iterator, bool> ret;

	win->ref();
	ret = windows_.insert(win);

	// Only connect to if we haven't already
	if (ret.second)
	{
		g_signal_connect(win->handle(), "destroy",
			G_CALLBACK(onWindowDestroyed), new Data(this, win));
	}

}

void App::removeWindow(Window *win)
{
	Set<Window*>::iterator found = windows_.find(win);
	if (found != windows_.end())
	{
		windows_.erase(found);
		win->unref();
	}
	if (quitOnLastWindow() && windows_.size() == 0)
		quit();
}

Window *App::activeWindow() const
{
	for (Set<Window*>::iterator it = windows_.begin(); it != windows_.end(); ++it)
	{
		if (gtk_window_is_active(GTK_WINDOW((*it)->handle())))
			return *it;
	}
	return 0;
}

bool App::quitOnLastWindow() const
{
	return quitOnLastWindow_;
}

void App::setQuitOnLastWindow(bool value)
{
	if (value != quitOnLastWindow())
	{
		quitOnLastWindow_ = value;
		emit(UI_SIG_QUIT_ON_LAST_WINDOW_CHANGED);
	}
}

} // namespace ui
