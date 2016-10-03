#pragma once

#include <glm\vec3.hpp>
#include <glm\vec2.hpp>


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
	glm::vec3 pos;
	glm::vec2 tc;
} EtherVert_Pos_Tex;

class EtherVert_Pos_Tex_Nml {
public:
	glm::vec3 pos;
	glm::vec3 nml;
	glm::vec2 tc;

	bool operator==(const EtherVert_Pos_Tex_Nml& other) const {
		return pos == other.pos && nml == other.nml && tc == other.tc;
	}
};

}
}

 //hash function for verts
typedef Ether::Core::EtherVert_Pos_Tex_Nml EtherVertPTN;

namespace std {
	template<> 
	struct hash<EtherVertPTN> {
		size_t operator()(EtherVertPTN const& vertex) const {
			return vertex.pos.x + vertex.pos.y + vertex.pos.z +
				vertex.nml.x + vertex.nml.y + vertex.nml.z +
				vertex.tc.x + vertex.tc.y;
		}
	};
}
