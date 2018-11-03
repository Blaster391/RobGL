
#include <RobGL/Renderer.h>
#include <Window/Window.h>
#include <Input/Input.h>
#include <RobGL/TextureLoader.h>
#include <RobGL/MeshHelpers.h>
#include <RobGL/StencilPool.h>

#include "CameraController.h"

#include <RobGL_SceneGraph\SceneNode.h>

int main() {
	Window w;
	w.startup();

	Input i;
	i.startup(&w);

	if (w.hasFailed()) {
		return -1;
	}

	rgl::Renderer renderer(w);
	bool finished = false;


	//Setup world
	rgl::Shader* colouredVertexShader = new rgl::Shader("Assets/Shaders/testVert.glsl", GL_VERTEX_SHADER);
	rgl::Shader* colouredFragmentShader = new rgl::Shader("Assets/Shaders/testFrag.glsl", GL_FRAGMENT_SHADER);

	rgl::Shader* texturedVertexShader = new rgl::Shader("Assets/Shaders/texVert.glsl", GL_VERTEX_SHADER);
	rgl::Shader* texturedFragmentShader = new rgl::Shader("Assets/Shaders/texFrag.glsl", GL_FRAGMENT_SHADER);

	rgl::Shader* stencilVertexShader = new rgl::Shader("Assets/Shaders/stencilVert.glsl", GL_VERTEX_SHADER);
	rgl::Shader* stencilFragmentShader = new rgl::Shader("Assets/Shaders/stencilFrag.glsl", GL_FRAGMENT_SHADER);

	rgl::Texture* texture = rgl::TextureLoader::LoadFromFile("Assets/Textures/test.png",false, true);
	rgl::Texture* transparentTexture = rgl::TextureLoader::LoadFromFile("Assets/Textures/stainedglass.tga",true, true);
	rgl::Texture* andyTexture = rgl::TextureLoader::LoadFromFile("Assets/Textures/Anky.png",true, true);
	rgl::Texture* checkerboardTexture = rgl::TextureLoader::LoadFromFile("Assets/Textures/chessboard.tga", true, false);

	rgl::Mesh* triangleMesh = rgl::MeshHelpers::GenerateTriangle();
	rgl::Mesh* quadMesh = rgl::MeshHelpers::GenerateQuad();
	rgl::Mesh* andyMesh = rgl::MeshHelpers::LoadMeshFromObj("Assets/Models/anky.obj");
	rgl::Mesh* hatMesh = rgl::MeshHelpers::LoadMeshFromObj("Assets/Models/hat.obj");

	std::vector<rgl::Shader*> colouredShaders;
	colouredShaders.push_back(colouredVertexShader);
	colouredShaders.push_back(colouredFragmentShader);

	std::vector<rgl::Shader*> texturedShaders;
	texturedShaders.push_back(texturedVertexShader);
	texturedShaders.push_back(texturedFragmentShader);

	std::vector<rgl::Shader*> stencilShaders;
	stencilShaders.push_back(stencilVertexShader);
	stencilShaders.push_back(stencilFragmentShader);

	//TODO camera to camera controller
	rgl::Camera mainCamera;
	mainCamera.setProjectionPerspective();
	glm::vec3 cameraPos(0, 0, 10);
	mainCamera.setPosition(cameraPos);

	rgl::Camera uiCamera;
	uiCamera.setProjectionOrthographic();
	glm::vec3 uiPos(0, 0, 0);
	uiCamera.setPosition(uiPos);

	CameraController cameraController(&mainCamera, &i);

	rgl::StencilPool stencilPool(stencilShaders, &uiCamera);

	rgl::RenderPool colouredPool(colouredShaders, &mainCamera);
	rgl::RenderPool texturedPool(texturedShaders, &mainCamera);
	rgl::RenderPool transparentTexturedPool(texturedShaders, &mainCamera);

	rgl::RenderObject ro;
	glm::mat4x4 roPos;
	roPos = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -10)) * glm::scale(glm::mat4(1.0f), glm::vec3(10, 10, 10));
	ro.setModelMatrix(roPos);
	ro.setMesh(triangleMesh);
	//colouredPool.addRenderObject(&ro);

	rgl::RenderObject ro2;
	roPos = glm::translate(glm::mat4(1.0f), glm::vec3(2, 1, -5)) * glm::scale(glm::mat4(1.0f), glm::vec3(3, 3, 3));
	ro2.setModelMatrix(roPos);
	ro2.setMesh(triangleMesh);
	//colouredPool.addRenderObject(&ro2);

	rgl::RenderObject roTex;
	roPos = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -25)) * glm::scale(glm::mat4(1.0f), glm::vec3(1, 1, 1));
	roTex.setModelMatrix(roPos);
	roTex.setTexture(texture);
	roTex.setMesh(quadMesh);
	texturedPool.addRenderObject(&roTex);


	rgl::RenderObject roAndy;
	roPos = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -2)) * glm::scale(glm::mat4(1.0f), glm::vec3(10, 10, 10));
	roAndy.setModelMatrix(roPos);
	roAndy.setTexture(andyTexture);
	roAndy.setMesh(andyMesh);
	texturedPool.addRenderObject(&roAndy);


	rgl::scenes::SceneNode parentNode;
	parentNode.attachRenderObject(&roAndy);

	rgl::scenes::SceneNode childNode;
	rgl::RenderObject roChild;
	roChild.setModelMatrix(roPos);
	roChild.setTexture(texture);
	roChild.setMesh(hatMesh);
	childNode.attachRenderObject(&roChild);
	texturedPool.addRenderObject(&roChild);
	parentNode.addChild(&childNode);

	parentNode.setPosition(glm::vec3(0, 0, -5));
	parentNode.setScale(glm::vec3(10, 10, 10));
	childNode.setPosition(glm::vec3(0, 1.7f, 3.3f));
	childNode.setScale(glm::vec3(0.03f, 0.03f, 0.03f));

	rgl::RenderObject roStencil;
	//roPos = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -1)) * glm::scale(glm::mat4(1.0f), glm::vec3(1, 1, 1));
	roPos = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -10000)) * glm::scale(glm::mat4(1.0f), glm::vec3(1000.0f, 1000.0f, 1.0f));
	roStencil.setModelMatrix(roPos);
	roStencil.setTexture(checkerboardTexture);
	roStencil.setMesh(quadMesh);
	stencilPool.addRenderObject(&roStencil);

	//renderer.addRenderPool(&stencilPool);
	renderer.addRenderPool(&colouredPool);
	renderer.addRenderPool(&texturedPool);
	renderer.addRenderPool(&transparentTexturedPool);

	bool bilinear = false;
	bool scissor = false;
	bool stencil = false;
	bool stencil2 = false;

	while (!finished) {
		w.update(1);
		i.update(1);

		renderer.update();

		finished = w.ShouldClose();

		cameraController.update(1);

		if (i.isKeyPressed(InputButton::KEYBOARD_ESCAPE)) {
			finished = true;
		}

		if (i.isKeyPressed(InputButton::KEYBOARD_SPACE)) {
			bilinear = !bilinear;
			texture->setFiltering(bilinear);
			andyTexture->setFiltering(bilinear);
		}

		if (i.isKeyPressed(InputButton::KEYBOARD_H)) {
			scissor = !scissor;
			texturedPool.setScissor(scissor);
			texturedPool.setScissorBounds({200,200,100,100});
		}

		if (i.isKeyPressed(InputButton::KEYBOARD_J)) {
			stencil = !stencil;
			stencilPool.setEnabled(stencil);
		}
	}

	w.shutdown();

	delete colouredVertexShader;
	delete colouredFragmentShader;

	delete texturedVertexShader;
	delete texturedFragmentShader;

	delete texture;
	delete transparentTexture;
	delete andyTexture;
	delete checkerboardTexture;

	delete triangleMesh;
	delete andyMesh;
	delete quadMesh;

	return 0;
}