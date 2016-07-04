#pragma once

#include "vmath.h"

namespace Ether {
namespace Core {


#define BUFFER_OFFSET(i) ((char *)NULL + (i))

template<class T>
class Size {
public:

	Size<T>(T w, T h) : width(w), height(h) {}
	Size<T>() : width(0), height(0) {}

	T width;
	T height;
};

typedef Size<int> SizeI;

// VERTEX TYPES
typedef struct EtherVert_Pos_Tex {
	vmath::vec3 pos;
	vmath::vec2 tc;
} EtherVert_Pos_Tex;

}
}