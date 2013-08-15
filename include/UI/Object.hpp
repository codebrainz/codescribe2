//
// Abstract Base Object - Provides stuff common to widgets and other objects.
//

#ifndef UI_OBJECT_H
#define UI_OBJECT_H 1

#include <UI/AtomicCounter.hpp>
#include <UI/Types.hpp>

namespace ui
{

using namespace util;

class Object
{

#define UI_CALLBACK(cbFunc) ((CallbackFunc)(cbFunc))
#define UI_SIG_DESTROY      "destroy"
#define UI_SIG_NAME_CHANGED "nameChanged"

public:
	void ref();
	void unref();
	size_t refCount() const { return refCount_.count(); }
	void connect(const char *signal, CallbackFunc f);
	void disconnect(const char *signal, CallbackFunc f);
	void emit(const char *signal);
	const String &name() const { return name_; }
	void setName(const String &value);
	// TODO: make this protected?
	void addSignal(const char *name);
	void removeSignal(const char *name);

protected:
	Object();
	virtual ~Object();
	unsigned long nextId();

private:
	CallbackMap callbackMap_;
	String nextName();
	AtomicCounter<unsigned long> refCount_;
	static AtomicCounter<unsigned long> uniqueId_;
	String name_;

};

} // namespace ui

#endif // UI_OBJECT_H
