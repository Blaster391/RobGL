#include <iostream>
#include <RobGL/Renderer.h>
#include <Window/Window.h>
#include <Input/Input.h>
#include <RobGL/TextureLoader.h>
#include <RobGL/MeshHelpers.h>
#include <RobGL/StencilPool.h>

#include "Timer.h"

#include "CameraController.h"
#include <RobGL/AnimatedRenderObject.h>

#include <RobGL_SceneGraph\SceneNode.h>
#include <RobGL/SkyboxFX.h>
#include <RobGL/DirectionalLightCamera.h>

int main() {
	Window w;
	w.startup();

	w.hideCursor();

	Input i;
	i.startup(&w);

	if (w.hasFailed()) {
		return -1;
	}

	rgl::Renderer renderer(w);
	bool finished = false;


	//Setup world
	rgl::Shader* colouredVertexShader = new rgl::Shader("Assets/Shaders/colourVert.glsl", GL_VERTEX_SHADER);
	rgl::Shader* colouredFragmentShader = new rgl::Shader("Assets/Shaders/colourFrag.glsl", GL_FRAGMENT_SHADER);

	rgl::Shader* texturedVertexShader = new rgl::Shader("Assets/Shaders/texVert.glsl", GL_VERTEX_SHADER);
	rgl::Shader* texturedFragmentShader = new rgl::Shader("Assets/Shaders/texFrag.glsl", GL_FRAGMENT_SHADER);
	rgl::Shader* litTexturedFragmentShader = new rgl::Shader("Assets/Shaders/litTexFrag.glsl", GL_FRAGMENT_SHADER);

	rgl::Shader* animatedVertexShader = new rgl::Shader("Assets/Shaders/animatedVert.glsl", GL_VERTEX_SHADER);

	rgl::Shader* stencilVertexShader = new rgl::Shader("Assets/Shaders/stencilVert.glsl", GL_VERTEX_SHADER);
	rgl::Shader* stencilFragmentShader = new rgl::Shader("Assets/Shaders/stencilFrag.glsl", GL_FRAGMENT_SHADER);

	rgl::Shader* texturedVertexShaderNoMVP = new rgl::Shader("Assets/Shaders/texVertNoMVP.glsl", GL_VERTEX_SHADER);
	rgl::Shader* noRedFXFragmentShader = new rgl::Shader("Assets/Shaders/noRedFragFX.glsl", GL_FRAGMENT_SHADER);
	rgl::Shader* noBlueFXFragmentShader = new rgl::Shader("Assets/Shaders/noBlueFragFX.glsl", GL_FRAGMENT_SHADER);
	rgl::Shader* blurFXFragmentShader = new rgl::Shader("Assets/Shaders/blurFragFX.glsl", GL_FRAGMENT_SHADER);
	rgl::Shader* sobelFXFragmentShader = new rgl::Shader("Assets/Shaders/sobelFragFX.glsl", GL_FRAGMENT_SHADER);

	rgl::Shader* skyboxFXVertShader = new rgl::Shader("Assets/Shaders/skyboxVertFX.glsl", GL_VERTEX_SHADER);
	rgl::Shader* skyboxFXFragShader = new rgl::Shader("Assets/Shaders/skyboxFragFX.glsl", GL_FRAGMENT_SHADER);

	rgl::Shader* shadowMapVertShader = new rgl::Shader("Assets/Shaders/shadowMapVert.glsl", GL_VERTEX_SHADER);
	rgl::Shader* shadowMapFragShader = new rgl::Shader("Assets/Shaders/shadowMapFrag.glsl", GL_FRAGMENT_SHADER);

	rgl::Shader* pointLightVertShader = new rgl::Shader("Assets/Shaders/pointLightVert.glsl", GL_VERTEX_SHADER);
	rgl::Shader* pointLightFragShader = new rgl::Shader("Assets/Shaders/pointLightFrag.glsl", GL_FRAGMENT_SHADER);

	rgl::Shader* combineVertShader = new rgl::Shader("Assets/Shaders/combineVert.glsl", GL_VERTEX_SHADER);
	rgl::Shader* combineFragShader = new rgl::Shader("Assets/Shaders/combineFrag.glsl", GL_FRAGMENT_SHADER);

	rgl::Texture* texture = rgl::TextureLoader::LoadFromFile("Assets/Textures/test.png",false, true);
	rgl::Texture* transparentTexture = rgl::TextureLoader::LoadFromFile("Assets/Textures/stainedglass.tga",true, true);
	rgl::Texture* andyTexture = rgl::TextureLoader::LoadFromFile("Assets/Textures/Anky.png",true, true);
	rgl::Texture* checkerboardTexture = rgl::TextureLoader::LoadFromFile("Assets/Textures/chessboard.tga", true, false);

	rgl::Cubemap* skyboxTex = rgl::TextureLoader::LoadCubemapFromFile({
		"Assets/Textures/cubemaps/rusted_west.jpg",
		"Assets/Textures/cubemaps/rusted_east.jpg",
		"Assets/Textures/cubemaps/rusted_up.jpg",
		"Assets/Textures/cubemaps/rusted_down.jpg",
		"Assets/Textures/cubemaps/rusted_south.jpg" ,
		"Assets/Textures/cubemaps/rusted_north.jpg" }, true);

	rgl::Mesh* triangleMesh = rgl::MeshHelpers::GenerateTriangle();
	rgl::Mesh* quadMesh = rgl::MeshHelpers::GenerateQuad();
	rgl::Mesh* andyMesh = rgl::MeshHelpers::LoadMeshFromObj("Assets/Models/anky.obj");
	rgl::Mesh* hatMesh = rgl::MeshHelpers::LoadMeshFromObj("Assets/Models/hat.obj");
	rgl::Mesh* floorMesh = rgl::MeshHelpers::GenerateHeightMap(16,16,10, "Assets/Textures/heightmap.png");

	rgl::AnimatedMesh* animatedAndyMesh = rgl::MeshHelpers::LoadAnimatedMeshFromGLTF("Assets/Models/ankyanim.gltf");
	rgl::Mesh* lightSphereMesh = rgl::MeshHelpers::LoadMeshFromObj("Assets/Models/ico.obj");
	//rgl::AnimatedMesh* ahhhhhh = rgl::MeshHelpers::LoadAnimatedMeshFromGLTF("Assets/Models/animationtest2.gltf");
	//rgl::Mesh* ahhhhhh = rgl::MeshHelpers::LoadMeshFromGLTF("Assets/Models/animationtest2.gltf");


	std::vector<rgl::Shader*> colouredShaders;
	colouredShaders.push_back(colouredVertexShader);
	colouredShaders.push_back(colouredFragmentShader);

	std::vector<rgl::Shader*> texturedShaders;
	texturedShaders.push_back(texturedVertexShader);
	texturedShaders.push_back(litTexturedFragmentShader);

	std::vector<rgl::Shader*> stencilShaders;
	stencilShaders.push_back(stencilVertexShader);
	stencilShaders.push_back(stencilFragmentShader);

	std::vector<rgl::Shader*> animatedShaders;
	animatedShaders.push_back(animatedVertexShader);
	animatedShaders.push_back(litTexturedFragmentShader);

	std::vector<rgl::Shader*> noRedFXShaders;
	noRedFXShaders.push_back(texturedVertexShaderNoMVP);
	noRedFXShaders.push_back(noRedFXFragmentShader);

	std::vector<rgl::Shader*> noBlueFXShaders;
	noBlueFXShaders.push_back(texturedVertexShaderNoMVP);
	noBlueFXShaders.push_back(noBlueFXFragmentShader);

	std::vector<rgl::Shader*>blurFXShaders;
	blurFXShaders.push_back(texturedVertexShaderNoMVP);
	blurFXShaders.push_back(blurFXFragmentShader);

	std::vector<rgl::Shader*>sobelFXShaders;
	sobelFXShaders.push_back(texturedVertexShaderNoMVP);
	sobelFXShaders.push_back(sobelFXFragmentShader);

	std::vector<rgl::Shader*>combineShaders;
	combineShaders.push_back(combineVertShader);
	combineShaders.push_back(combineFragShader);

	std::vector<rgl::Shader*>pointLightShaders;
	pointLightShaders.push_back(pointLightVertShader);
	pointLightShaders.push_back(pointLightFragShader);

	std::vector<rgl::Shader*> texturedUnlitShaders;
	texturedUnlitShaders.push_back(texturedVertexShader);
	texturedUnlitShaders.push_back(texturedFragmentShader);

	std::vector<rgl::Shader*> shadowMapShaders;
	shadowMapShaders.push_back(shadowMapVertShader);
	shadowMapShaders.push_back(shadowMapFragShader);

	std::vector<rgl::Shader*>skyboxFXShaders;
	skyboxFXShaders.push_back(skyboxFXVertShader);
	skyboxFXShaders.push_back(skyboxFXFragShader);


	//TODO camera to camera controller
	rgl::Camera mainCamera;
	mainCamera.setProjectionPerspective();
	glm::vec3 cameraPos(0, 0, 10);
	mainCamera.setPosition(cameraPos);

	rgl::Camera uiCamera;
	uiCamera.setProjectionOrthographic();
	glm::vec3 uiPos(0, 0, 0);
	uiCamera.setPosition(uiPos);

	rgl::DirectionalLightCamera directionalLightCamera(glm::vec4(1, 1, 1, 1), glm::vec3(0, 1, 1));
	rgl::DirectionalLightUniform* directionalLightUniform = directionalLightCamera.getUniformData();
	directionalLightCamera.setProjectionPerspective();
	directionalLightCamera.setPosition(glm::vec3(0,100,0));
	directionalLightCamera.pitch(1);

	renderer.enablePostProcessing(texturedUnlitShaders);
	renderer.enableDeferredLighting(pointLightShaders, combineShaders, &mainCamera);
	renderer.enableShadowMapping(shadowMapShaders, &directionalLightCamera, 512);

	directionalLightUniform->setShadowTexture(renderer.getShadowMapTexture());

	CameraController cameraController(&mainCamera, &i);

	//rgl::StencilPool stencilPool(stencilShaders, &uiCamera);

	rgl::RenderPool colouredPool(colouredShaders, &mainCamera);
	rgl::RenderPool texturedPool(texturedShaders, &mainCamera);
	rgl::RenderPool animatedPool(animatedShaders, &mainCamera);
	rgl::RenderPool transparentTexturedPool(texturedShaders, &mainCamera);

	colouredPool.addUniformData(directionalLightUniform);
	texturedPool.addUniformData(directionalLightUniform);
	animatedPool.addUniformData(directionalLightUniform);
	transparentTexturedPool.addUniformData(directionalLightUniform);

	rgl::PostProcessingFX noRedFX(noRedFXShaders, 1);
	rgl::PostProcessingFX noBlueFX(noBlueFXShaders, 1);
	rgl::PostProcessingFX blurFX(blurFXShaders, 100);
	rgl::PostProcessingFX sobelFX(sobelFXShaders, 1);
	rgl::SkyboxFX skyboxFX(skyboxFXShaders, skyboxTex, renderer.getDepthTexture(), &mainCamera);

	rgl::RenderObject ro;
	glm::mat4x4 roPos;
	roPos = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -10)) * glm::scale(glm::mat4(1.0f), glm::vec3(10, 10, 10));
	ro.setModelMatrix(roPos);
	ro.setMesh(triangleMesh);
	ro.setBounds(new rgl::BoundingSphere(&ro,3.0f));
	colouredPool.addRenderObject(&ro);

	rgl::RenderObject roFloor;
	roPos = glm::translate(glm::mat4(1.0f), glm::vec3(0, -1, -10)) * glm::scale(glm::mat4(1.0f), glm::vec3(1, 1, 1));
	roFloor.setModelMatrix(roPos);
	roFloor.setMesh(floorMesh);
	roFloor.setTexture(texture);
	texturedPool.addRenderObject(&roFloor);

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


	rgl::PointLight light(glm::vec4(1,0,0,1));
	roPos = glm::translate(glm::mat4(1.0f), glm::vec3(2, 1, 0)) * glm::scale(glm::mat4(1.0f), glm::vec3(15, 15, 15));
	light.setModelMatrix(roPos);
	light.setMesh(lightSphereMesh);
	renderer.addLight(&light);

	rgl::PointLight light2(glm::vec4(0, 1, 0, 1));
	roPos = glm::translate(glm::mat4(1.0f), glm::vec3(1, 1, 0)) * glm::scale(glm::mat4(1.0f), glm::vec3(20, 20, 20));
	light2.setModelMatrix(roPos);
	light2.setMesh(lightSphereMesh);
	//texturedPool.addRenderObject(&light2);
	renderer.addLight(&light2);


	rgl::PointLight light3(glm::vec4(0, 0, 1, 1));
	roPos = glm::translate(glm::mat4(1.0f), glm::vec3(3, 1, 3)) * glm::scale(glm::mat4(1.0f), glm::vec3(10, 10, 10));
	light3.setModelMatrix(roPos);
	light3.setMesh(lightSphereMesh);
	renderer.addLight(&light3);


	rgl::AnimatedRenderObject roAndy;
	roPos = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -2)) * glm::scale(glm::mat4(1.0f), glm::vec3(10, 10, 10));
	roAndy.setModelMatrix(roPos);
	roAndy.setTexture(andyTexture);
	roAndy.setMesh(animatedAndyMesh);
	animatedAndyMesh->setActiveAnimation(0);
	animatedPool.addRenderObject(&roAndy);
	

	rgl::scenes::SceneNode parentNode;
	parentNode.attachRenderObject(&roAndy);

	rgl::scenes::SceneNode childNode;
	rgl::RenderObject roChild;
	roChild.setModelMatrix(roPos);
	roChild.setTexture(texture);
	roChild.setMesh(hatMesh);
	childNode.attachRenderObject(&roChild);
	colouredPool.addRenderObject(&roChild);
	parentNode.addChild(&childNode);

	parentNode.setPosition(glm::vec3(0, 0, -5));
	parentNode.setScale(glm::vec3(10, 10, 10));
	childNode.setPosition(glm::vec3(0, 1.7f, 3.3f));
	childNode.setScale(glm::vec3(0.03f, 0.03f, 0.03f));


	//rgl::scenes::SceneNode sunNode;
	//rgl::scenes::SceneNode sunLightNode;
	//sunNode.addChild(&sunLightNode);
	//sunNode.setPosition(glm::vec3(3, 50, 10));
	//sunNode.setScale(glm::vec3(10, 10, 10));
	//sunLightNode.setScale(glm::vec3(100, 100, 100));
	//rgl::RenderObject sun;
	//rgl::PointLight sunLight(glm::vec4(1,1,1,1));
	//sun.setMesh(lightSphereMesh);
	//sunLight.setMesh(lightSphereMesh);
	//sunNode.attachRenderObject(&sun);
	//sunLightNode.attachRenderObject(&sunLight);
	//colouredPool.addRenderObject(&sun);
	//renderer.addLight(&sunLight);


	animatedAndyMesh->setGlobalTransform(roAndy.getModelMatrix());

	//rgl::RenderObject roStencil;
	////roPos = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -1)) * glm::scale(glm::mat4(1.0f), glm::vec3(1, 1, 1));
	//roPos = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -10000)) * glm::scale(glm::mat4(1.0f), glm::vec3(1000.0f, 1000.0f, 1.0f));
	//roStencil.setModelMatrix(roPos);
	//roStencil.setTexture(checkerboardTexture);
	//roStencil.setMesh(quadMesh);
	//stencilPool.addRenderObject(&roStencil);

	//renderer.addRenderPool(&stencilPool);
	renderer.addRenderPool(&colouredPool);
	renderer.addRenderPool(&texturedPool);
	renderer.addRenderPool(&animatedPool);
	renderer.addRenderPool(&transparentTexturedPool);

	renderer.addPostProcessingFX(&skyboxFX);
	//renderer.addPostProcessingFX(&noRedFX);

	//renderer.addPostProcessingFX(&noBlueFX);

	//renderer.addPostProcessingFX(&blurFX);
	//renderer.addPostProcessingFX(&sobelFX);

	renderer.addRenderObjectToShadowPool(&roAndy);
	renderer.addRenderObjectToShadowPool(&ro);
	renderer.addRenderObjectToShadowPool(&roFloor);
	
	bool bilinear = false;
	bool scissor = false;
	bool stencil = false;
	bool stencil2 = false;

	Timer t;
	t.start();

	while (!finished) {
		float delta = t.delta();
		w.update(delta);
		i.update(delta);

		renderer.update(delta);

		finished = w.ShouldClose();

		cameraController.update(delta);

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

		//if (i.isKeyPressed(InputButton::KEYBOARD_J)) {
		//	stencil = !stencil;
		//	stencilPool.setEnabled(stencil);
		//}

		if (i.isKeyPressed(InputButton::KEYBOARD_V)) {
			auto verts = floorMesh->getVertices();
			verts[20].Position.y = 3;
			verts[21].Position.y = 3;
			verts[22].Position.y = 3;

			floorMesh->setVerticies(verts);

			floorMesh->rebuffer();
		}

		if (i.isKeyPressed(InputButton::KEYBOARD_T)) {
			parentNode.setPosition(glm::vec3(5, 0, -5));
		}

		light.setColour(glm::vec4((float)rand()/RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX,1));
		light2.setColour(glm::vec4((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, 1));
		light3.setColour(glm::vec4((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, 1));
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