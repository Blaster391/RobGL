#include "ToScreenRenderPool.h"
#include "FixedScreenCamera.h"
#include "MeshHelpers.h"
namespace rgl {

	ToScreenRenderPool::ToScreenRenderPool(std::vector<Shader*> shaders, GLuint colourTex) : RenderPool(shaders, new FixedScreenCamera)
	{
		_camera->setProjectionOrthographic();
		_quadMesh = MeshHelpers::GenerateQuad();
		_quadObject = new RenderObject();
		_quadObject->setMesh(_quadMesh);
		_quadTexture = new Texture(colourTex, false);
		_quadObject->setTexture(_quadTexture);
		_renderObjects.push_back(_quadObject);
	}

	ToScreenRenderPool::~ToScreenRenderPool()
	{
		delete _camera;
		delete _quadMesh;
		delete _quadObject;
		delete _quadTexture;
	}
}