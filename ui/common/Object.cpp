#include <UI/Object.hpp>
#include <cstdio>

namespace ui
{

Object::Object()
	: refCount_(1), name_(nextName())
{
	addSignal(UI_SIG_DESTROY);
	addSignal(UI_SIG_NAME_CHANGED);
}

Object::~Object()
{
//	if (refCount() > 0)
//		 issue warning about being destroyed before refCount == 0?
	emit(UI_SIG_DESTROY);
}

void Object::addSignal(const char *name)
{
	callbackMap_.insert(std::make_pair(name, Set<CallbackFunc>()));
}

void Object::removeSignal(const char *name)
{
	CallbackMap::iterator found = callbackMap_.find(name);
	if (found != callbackMap_.end())
		callbackMap_.erase(found);
}

void Object::ref()
{
	refCount_.inc();
}

void Object::unref()
{
	if (refCount_.dec() == 0)
		delete this;
}

void Object::connect(const char *signal, CallbackFunc f)
{
	CallbackMap::iterator found = callbackMap_.find(signal);
	if (found != callbackMap_.end())
		found->second.insert(f);
}

void Object::disconnect(const char *signal, CallbackFunc f)
{
	CallbackMap::iterator found = callbackMap_.find(signal);
	if (found != callbackMap_.end())
	{
		Set<CallbackFunc>::iterator foundFunc = found->second.find(f);
		if (foundFunc != found->second.end())
			found->second.erase(foundFunc);
	}
}

void Object::emit(const char *name)
{
	CallbackMap::iterator found = callbackMap_.find(name);
	if (found != callbackMap_.end())
	{
		for (Set<CallbackFunc>::iterator it = found->second.begin();
		     it != found->second.end(); ++it)
		{
			(*it)(this);
		}
	}
}

AtomicCounter<unsigned long> Object::uniqueId_ = 0;

unsigned long Object::nextId()
{
	return Object::uniqueId_.inc();
}

String Object::nextName()
{
	char newName[128] = {0};
	snprintf(newName, 128, "Object_%lu", nextId());
	return String(newName);
}

void Object::setName(const String &value)
{
	if (value != name_)
	{
		name_ = value;
		emit(UI_SIG_NAME_CHANGED);
	}
}

} // namespace ui
