#include "EtherApp.h"
#include "EtherCubeRO.h"
#include "EtherPlatform.h"
#include "EtherGeometry.h"
#include <memory>
#include "tiny_obj_loader.h"
#include <unordered_map>
#include "EtherRenderable.h"
#include "EtherCamera.h"
#include "EtherLog.h"
#include <sstream>

#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc

tinyobj::attrib_t attrib;
std::vector<tinyobj::shape_t> shapes;
std::vector<tinyobj::material_t> materials;

class PhongLighting : public Ether::Core::EtherApp
{
protected:
	void Init() {
		EtherApp::Init();
		SetWindowTitle("Phong Lighting Demo");
	}

	void Startup() {
		EtherApp::Startup();

		std::string err;
		std::string assetsDir = Ether::Core::EtherPlatform::GetInstance()->GetAssetsDirectory();
		std::string matlDir = assetsDir + "models/Crate/";
		//std::string inputfile = assetsDir + "models/Crate/Crate1.obj";
		std::string inputfile = assetsDir + "models/custom/sphere.obj";
		bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, inputfile.c_str(), matlDir.c_str(), true);

		if (!err.empty()) { // `err` may contain warning message.
			std::cerr << err << std::endl;
		}

		std::unordered_map<Ether::Core::EtherVert_Pos_Tex_Nml, int> unique_vertices;
		std::vector<size_t> indices;
		std::string texturePath = "";

		// Loop over shapes/meshes, for a cube, there are 6 "shapes" ("front", "back", "right", etc...)
		for (size_t s = 0; s < shapes.size(); s++) {
			// Loop over triangles of each mesh
			size_t index_offset = 0;
			// num_face_vertices holds numbers of vertices per face of the mesh (will have 2 triangles in this case, so {3, 3} )
			for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
				int fv = shapes[s].mesh.num_face_vertices[f]; // i think this will always be 3 if "triangulation" is set?

				// Loop over vertices in the face (there will be 3 vertices on each of the 2 faces of this mesh)
				for (size_t v = 0; v < fv; v++) {
					Ether::Core::EtherVert_Pos_Tex_Nml vert;

					// accessing 1 of the 6 index_t items in this meshes 'indices' vector (in case of a quad face - being 2 faces of 3 verts each)
					tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
					float vx = attrib.vertices[3 * idx.vertex_index + 0];
					float vy = attrib.vertices[3 * idx.vertex_index + 1];
					float vz = attrib.vertices[3 * idx.vertex_index + 2];

					float nx = 0;
					float ny = 0;
					float nz = 0;

					float tx = 0;
					float ty = 0;

					if (idx.normal_index >= 0) {
						nx = attrib.normals[3 * idx.normal_index + 0];
						ny = attrib.normals[3 * idx.normal_index + 1];
						nz = attrib.normals[3 * idx.normal_index + 2];
					}

					if (idx.texcoord_index >= 0) {
						tx = attrib.texcoords[2 * idx.texcoord_index + 0];
						ty = attrib.texcoords[2 * idx.texcoord_index + 1];
					}

					vert.pos[0] = vx;
					vert.pos[1] = vy;
					vert.pos[2] = vz;

					vert.nml[0] = nx;
					vert.nml[1] = ny;
					vert.nml[2] = nz;

					vert.tc[0] = tx;
					vert.tc[1] = ty;

					// if this is first time seeing this vertex, store it...
					if (unique_vertices.count(vert) == 0) {
						unique_vertices[vert] = mVertices.size();
						mVertices.push_back(vert);
					}

					// store index entry for this vertex of this face
					mIndices.push_back(unique_vertices[vert]);
				}

				index_offset += fv;

				// per-face material
				int matId = shapes[s].mesh.material_ids[f];
				if (matId >= 0) {
					tinyobj::material_t faceMaterial = materials[matId];
					texturePath = faceMaterial.diffuse_texname;
				}
			}
		}

		mCamera = std::make_unique<Ether::Graphics::EtherCamera>();
		mCube = std::make_unique<Ether::Renderables::EtherRenderable>(mVertices, mIndices, texturePath);

		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
	}

	virtual void OnKey(int key, int action) override {
		mCamera->UpdateMovement(key, action);
	}

	virtual void OnCursorPos(double xpos, double ypos) override {
		mCamera->UpdateDirection(xpos, ypos);
	}

	virtual void OnMouseButton(int button, int action, int mods) override {
		if (button == GLFW_MOUSE_BUTTON_LEFT) {
			if (action == GLFW_PRESS)
				mCamera->DirectionCapture(true);
			else if(action == GLFW_RELEASE)
				mCamera->DirectionCapture(false);
		}
	}

	void Render(double currentTime) {
		EtherApp::Render(currentTime);

		static const GLfloat skyBlue[] = { 0.3f, 0.72f, 1.0f, 1.0f };
		static const GLfloat one = 1.0f;

		glViewport(0, 0, mWindowWidth, mWindowHeight);
		glClearBufferfv(GL_COLOR, 0, skyBlue);
		glClearBufferfv(GL_DEPTH, 0, &one);

		mCamera->Update(currentTime);

		float f = (float)currentTime * 0.3f;
		// model matrix
		glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.f, 0.f));
		//modelMatrix = glm::scale(glm::mat4(1.f), glm::vec3(0.1f, 0.1f, 0.1f));
		modelMatrix = glm::rotate(modelMatrix, f, glm::vec3(0.f, 1.f, 0.f));

		// view matrix
		glm::mat4 viewMatrix = mCamera->GetView();

		// projection matrix
		glm::mat4 projMatrix = glm::perspective(glm::radians(50.f), (float)mWindowWidth / (float)mWindowHeight, 0.1f, 1000.f);

		mCube->Render(currentTime, modelMatrix, viewMatrix, projMatrix);
	}

	void Shutdown() {
		EtherApp::Shutdown();
	}

private:
	std::unique_ptr<Ether::Renderables::EtherRenderable> mCube;
	std::unique_ptr<Ether::Graphics::EtherCamera> mCamera;

	std::vector<Ether::Core::EtherVert_Pos_Tex_Nml> mVertices;
	std::vector<GLushort> mIndices;
};

DECLARE_MAIN(PhongLighting);