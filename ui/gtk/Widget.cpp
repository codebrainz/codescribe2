#include <UI/Widget.hpp>
#include <gtk/gtk.h>

namespace ui
{

// FIXME: need to have a strategy for dealing with lifetimes
static void onWidgetDestroy(Handle *, Widget *self)
{
	if (self != 0)
		self->unref();
}

Widget::Widget(Handle handle, Widget *parent)
	: Object(), handle_(handle), parent_(parent)
{
	addSignal(UI_SIG_VISIBLE_CHANGED);
	addSignal(UI_SIG_ENABLE_CHANGED);
	g_signal_connect(handle_, "destroy", G_CALLBACK(onWidgetDestroy), this);
}

Widget::~Widget()
{
	if (GTK_IS_WIDGET(handle())
	    && gtk_widget_is_toplevel(GTK_WIDGET(handle())))
	{
		gtk_widget_destroy(GTK_WIDGET(handle()));
	}
}

bool Widget::operator==(const Widget &other)
{
	return other.handle() == handle();
}

bool Widget::operator!=(const Widget &other)
{
	return !(*this == other);
}

void Widget::update()
{
	gtk_widget_queue_draw(GTK_WIDGET(handle()));
}

bool Widget::isVisible() const
{
	return gtk_widget_get_visible(GTK_WIDGET(handle()));
}

void Widget::setVisible(bool value)
{
	if (value != isVisible())
	{
		gtk_widget_set_visible(GTK_WIDGET(handle()), value);
		emit(UI_SIG_VISIBLE_CHANGED);
	}
}

bool Widget::isEnabled() const
{
	return gtk_widget_get_sensitive(GTK_WIDGET(handle()));
}

void Widget::setEnabled(bool value)
{
	if (value != isEnabled())
	{
		gtk_widget_set_sensitive(GTK_WIDGET(handle()), value);
		emit(UI_SIG_ENABLE_CHANGED);
	}
}

} // namespace ui
