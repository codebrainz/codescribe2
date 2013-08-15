#ifndef UI_CONTAINER_H
#define UI_CONTAINER_H 1

#include <UI/Widget.hpp>

namespace ui
{
class Container : public Widget
{
public:
	virtual void addChild(Widget *widget)=0;
	virtual void removeChild(Widget *widget)=0;
	const Vector<Widget*> &children() { return children_; }
protected:
	Container(Widget *parent = 0);
	virtual ~Container();
private:
	Vector<Widget*> children_;
};

} // namespace ui

#endif // UI_CONTAINER_H
