
#include <RobGL/Renderer.h>
#include <Window/Window.h>
#include <Input/Input.h>
#include <RobGL/TextureLoader.h>
#include <RobGL/MeshHelpers.h>

#include "CameraController.h"

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

	rgl::Texture* texture = rgl::TextureLoader::LoadFromFile("Assets/Textures/test.png",false, true);
	rgl::Texture* transparentTexture = rgl::TextureLoader::LoadFromFile("Assets/Textures/stainedglass.tga",true, true);
	rgl::Texture* andyTexture = rgl::TextureLoader::LoadFromFile("Assets/Textures/Anky.png",true, true);

	rgl::Mesh* triangleMesh = rgl::MeshHelpers::GenerateTriangle();
	rgl::Mesh* quadMesh = rgl::MeshHelpers::GenerateQuad();
	rgl::Mesh* andyMesh = rgl::MeshHelpers::LoadMeshFromObj("Assets/Models/anky.obj");

	std::vector<rgl::Shader*> colouredShaders;
	colouredShaders.push_back(colouredVertexShader);
	colouredShaders.push_back(colouredFragmentShader);

	std::vector<rgl::Shader*> texturedShaders;
	texturedShaders.push_back(texturedVertexShader);
	texturedShaders.push_back(texturedFragmentShader);

	//TODO camera to camera controller
	rgl::Camera mainCamera;
	mainCamera.setProjectionPerspective();
	glm::vec3 cameraPos(0, 0, 10);
	mainCamera.setPosition(cameraPos);

	CameraController cameraController(&mainCamera, &i);

	rgl::RenderPool colouredPool(colouredShaders, &mainCamera);
	rgl::RenderPool texturedPool(texturedShaders, &mainCamera);
	rgl::RenderPool transparentTexturedPool(texturedShaders, &mainCamera);

	rgl::RenderObject ro;
	glm::mat4x4 roPos;
	roPos = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -10)) * glm::scale(glm::mat4(1.0f), glm::vec3(10, 10, 10));
	ro.setModelMatrix(roPos);
	ro.setMesh(triangleMesh);
	colouredPool.addRenderObject(&ro);

	rgl::RenderObject ro2;
	roPos = glm::translate(glm::mat4(1.0f), glm::vec3(2, 1, -5)) * glm::scale(glm::mat4(1.0f), glm::vec3(3, 3, 3));
	ro2.setModelMatrix(roPos);
	ro2.setMesh(triangleMesh);
	colouredPool.addRenderObject(&ro2);

	rgl::RenderObject roTex;
	roPos = glm::translate(glm::mat4(1.0f), glm::vec3(5, 0, -9)) * glm::scale(glm::mat4(1.0f), glm::vec3(10, 10, 10));
	roTex.setModelMatrix(roPos);
	roTex.setTexture(texture);
	roTex.setMesh(quadMesh);
	texturedPool.addRenderObject(&roTex);


	rgl::RenderObject roTransparent;
	roPos = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -2)) * glm::scale(glm::mat4(1.0f), glm::vec3(10, 10, 10));
	roTransparent.setModelMatrix(roPos);
	roTransparent.setTexture(andyTexture);
	roTransparent.setMesh(andyMesh);
	texturedPool.addRenderObject(&roTransparent);

	renderer.addRenderPool(&colouredPool);
	renderer.addRenderPool(&texturedPool);
	renderer.addRenderPool(&transparentTexturedPool);

	bool bilinear = false;

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



	}

	w.shutdown();

	delete colouredVertexShader;
	delete colouredFragmentShader;

	delete texturedVertexShader;
	delete texturedFragmentShader;

	delete texture;
	delete transparentTexture;
	delete andyTexture;

	delete triangleMesh;
	delete andyMesh;
	delete quadMesh;

	return 0;
}