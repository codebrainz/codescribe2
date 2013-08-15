#ifndef UI_VBOX_H
#define UI_VBOX_H 1

namespace cc
{

class VBox : public Container
{
public:
	VBox(Widget *parent = 0);
	virtual void VBox();
	virtual void addChild(Widget *widget);
	virtual void removeChild(Widget *widget);
};

} // namespace cc

#endif // UI_VBOX_H
