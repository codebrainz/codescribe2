#include <UI/Window.hpp>
#include <gtk/gtk.h>

namespace ui
{

Window::Window(const char *title, int width, int height, Widget *parent)
	: Widget((void*)gtk_window_new(GTK_WINDOW_TOPLEVEL), parent)
{
	if (width > -1 || height > -1)
		gtk_window_set_default_size(GTK_WINDOW(handle()), width, height);
	if (title != 0)
		gtk_window_set_title(GTK_WINDOW(handle()), title);
	addSignal(UI_SIG_TITLE_CHANGED);
	addSignal(UI_SIG_RESIZABLE_CHANGED);
	addSignal(UI_SIG_SIZE_CHANGED);
	addSignal(UI_SIG_POSITION_CHANGED);
}

String Window::title() const
{
	const char *title = gtk_window_get_title(GTK_WINDOW(handle()));
	if (title != 0)
		return String(title);
	return String();
}

void Window::setTitle(const String &value)
{
	if (value != title())
	{
		gtk_window_set_title(GTK_WINDOW(handle()), value.c_str());
		emit(UI_SIG_TITLE_CHANGED);
	}
}

bool Window::resizable() const
{
	return gtk_window_get_resizable(GTK_WINDOW(handle()));
}

void Window::setResizable(bool value)
{
	if (value != resizable())
	{
		gtk_window_set_resizable(GTK_WINDOW(handle()), value);
		emit(UI_SIG_RESIZABLE_CHANGED);
	}
}

Size Window::size() const
{
	Size sz;
	GdkWindow *win = gtk_widget_get_window(GTK_WIDGET(handle()));
	sz.width = gdk_window_get_width(win);
	sz.height = gdk_window_get_height(win);
	return sz;
}

void Window::setSize(const Size &value)
{
	// FIXME: connect to window configure event to emit "changed" signal
	if (value != size())
	{
		gtk_window_resize(GTK_WINDOW(handle()), value.width, value.height);
		emit(UI_SIG_SIZE_CHANGED);
	}
}

Point Window::position() const
{
	Point pos;
	GdkWindow *win = gtk_widget_get_window(GTK_WIDGET(handle()));
	gdk_window_get_position(win, &(pos.x), &(pos.y));
	return pos;
}

void Window::setPosition(const Point &value)
{
	// FIXME: connect to window configure event to emit "changed" signal
	if (value != position())
	{
		gtk_window_move(GTK_WINDOW(handle()), value.x, value.y);
		emit(UI_SIG_POSITION_CHANGED);
	}
}

} // namespace ui
