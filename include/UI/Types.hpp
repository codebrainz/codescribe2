#ifndef UTIL_TYPES_H
#define UTIL_TYPES_H 1

#include <vector>
#include <string>
#include <set>
#include <map>
#include <utility>

namespace ui {
	class Object; // forward declare
	typedef void* Handle;
	struct Size
	{
		int width, height;
		Size(int width=-1, int height=-1) : width(width), height(height) { }
		bool operator==(const Size &other) const {
			return (width == other.width && height == other.height);
		}
		bool operator!=(const Size &other) const {
			return !(*this == other);
		}
	};
	struct Point
	{
		int x, y;
		Point(int x=-1, int y=-1) : x(x), y(y) { }
		bool operator==(const Point &other) const {
			return (x == other.x && y == other.y);
		}
		bool operator!=(const Point &other) const {
			return !(*this == other);
		}
	};
}

namespace util
{

// I hate C++! I just want to typedef these containers so I can
// switch implementations without update butloads of code later.
//typedef std::vector Vector;
//typedef std::string String;
//typedef std::set Set;
//typedef std::map Map;
// KaBOOM! Why was I using namespaces again?
#define Vector std::vector
#define String std::string
#define Set std::set
#define Map std::map

typedef void (*CallbackFunc) (ui::Object*);

typedef Map<String, Set<CallbackFunc> > CallbackMap;

} // namespace util


#endif // UTIL_TYPES_H
