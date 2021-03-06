#include "AbductionScene.h"
#include <RobGL/DirectionalLightCamera.h>
#include <RobGL/AdditionalTextureUniform.h>


AbductionScene::AbductionScene(Window & window, Input & input) : BaseScene(window, input)
{
}

AbductionScene::~AbductionScene()
{
}

void AbductionScene::setupScene(AssetPack * assets)
{
	_mainCamera = new rgl::Camera;
	_cameraController = new CameraController(_mainCamera, &_input);
	_mainCamera->setPosition(glm::vec3(60,10, 75));
	_mainCamera->yaw(-1.5);
	_mainCamera->pitch(1);


	_renderer.enablePostProcessing({ assets->getShader("TexturedVertex"), assets->getShader("UnlitTexturedFragment") });
	_renderer.enableDeferredLighting({ assets->getShader("PointLightVertex"), assets->getShader("PointLightFragment") }, { assets->getShader("LightingCombineVertex"), assets->getShader("LightingCombineFragment") }, _mainCamera, _screenInfoUniform);
	//_renderer.enableShadowMapping({ assets->getShader("ShadowMapVertex"), assets->getShader("ShadowMapFragment") }, { assets->getShader("AnimatedShadowMapVertex"), assets->getShader("ShadowMapFragment") }, directionalLightCamera, 2160);

	
	_mainCamera->setProjectionPerspective(800, 600);

	rgl::DirectionalLightCamera* directionalLightCamera = new rgl::DirectionalLightCamera(glm::vec4(0.25f, 0.25f,0.25f, 1), glm::vec3(0, 1, 0));
	rgl::DirectionalLightUniform* directionalLightUniform = directionalLightCamera->getUniformData();
	directionalLightCamera->setProjectionOrthographic(1, 400, 300, 300);
	directionalLightCamera->setPosition(glm::vec3(75, 200, 100));
	directionalLightCamera->pitch(-3.14f / 2);
	directionalLightCamera->yaw(-3.14f / 2);


	//directionalLightUniform->setShadowTexture(_renderer.getShadowMapTexture());

	//Setup particles
	rgl::ParticleSystem* beamParticles = new rgl::ParticleSystem(numberOfParticlesInBeam);
	beamParticles->setTexture(assets->getTexture("particle"));
	beamParticles->setModelMatrix(glm::translate(glm::mat4(1), glm::vec3(75,0,75)) * glm::scale(glm::mat4(1), glm::vec3(5, 1, 5)));
	_beamParticles = beamParticles->getParticleBuffer();

	//Setup render pools
	rgl::ParticlePool*  beamParticlesPool = new rgl::ParticlePool({ assets->getShader("BeamVertexFX"),assets->getShader("BeamGeoFX"), assets->getShader("BeamFragmentFX")}, _mainCamera, beamParticles);
	_renderer.addRenderPool(beamParticlesPool);

	rgl::RenderPool* texturedRenderPool = new rgl::RenderPool({ assets->getShader("TexturedVertex"), assets->getShader("TexturedFragment") }, _mainCamera);
	texturedRenderPool->addUniformData(directionalLightUniform);
	_renderer.addRenderPool(texturedRenderPool);

	rgl::RenderPool* animatedRenderPool = new rgl::RenderPool({ assets->getShader("AnimatedVertex"), assets->getShader("TexturedFragment") }, _mainCamera);
	animatedRenderPool->addUniformData(directionalLightUniform);
	_renderer.addRenderPool(animatedRenderPool);


	//Setup render objects
	rgl::RenderObject* floor = new rgl::RenderObject;
	floor->setMesh(assets->getMesh("abductionFloor"));
	floor->setTexture(assets->getTexture("ground_rock"));
	floor->setModelMatrix(glm::translate(glm::mat4(1), glm::vec3(0, 0, 0)) * glm::scale(glm::mat4(1), glm::vec3(1, 3, 1)));
	texturedRenderPool->addRenderObject(floor);

	_ufoNode = new rgl::scenes::SceneNode;
	rgl::RenderObject* ufo = new rgl::RenderObject;
	ufo->setMesh(assets->getMesh("ufo"));
	ufo->setTexture(assets->getTexture("ufo"));
	_ufoNode->setPosition(glm::vec3(75, 100, 75));
	_ufoNode->setScale(glm::vec3(1, 1, 1));
	texturedRenderPool->addRenderObject(ufo);
	_ufoNode->attachRenderObject(ufo);


	rgl::AnimatedRenderObject* dino1 = new rgl::AnimatedRenderObject;
	dino1->setMesh(assets->getAnimatedMesh("anky"));
	dino1->setTexture(assets->getTexture("anky"));
	dino1->setModelMatrix(glm::translate(glm::mat4(1), glm::vec3(75,20,75)) * glm::scale(glm::mat4(1), glm::vec3(1, 1, 1)) * glm::rotate(glm::mat4(1), -glm::half_pi<float>(), glm::vec3(1, 0, 0)));
	dino1->setActiveAnimation(2, 0);
	animatedRenderPool->addRenderObject(dino1);
	_abductees.push_back({ dino1 , 0, false, glm::vec3(75,50,75) });


	rgl::AnimatedRenderObject* dino2 = new rgl::AnimatedRenderObject;
	dino2->setMesh(assets->getAnimatedMesh("anky"));
	dino2->setTexture(assets->getTexture("anky"));
	dino2->setModelMatrix(glm::translate(glm::mat4(1), glm::vec3(60, 25, 75)) * glm::scale(glm::mat4(1), glm::vec3(1, 1, 1)) * glm::rotate(glm::mat4(1), -glm::half_pi<float>(), glm::vec3(1, 0, 0)));
	dino2->setActiveAnimation(2, 1);
	animatedRenderPool->addRenderObject(dino2);
	_abductees.push_back({ dino2 , 3, false, glm::vec3(60, 35, 75) });

	rgl::AnimatedRenderObject* dino3 = new rgl::AnimatedRenderObject;
	dino3->setMesh(assets->getAnimatedMesh("anky"));
	dino3->setTexture(assets->getTexture("anky"));
	dino3->setModelMatrix(glm::translate(glm::mat4(1), glm::vec3(70, 20, 80)) * glm::scale(glm::mat4(1), glm::vec3(1, 1, 1)) * glm::rotate(glm::mat4(1), -glm::half_pi<float>(), glm::vec3(1, 0, 0)));
	dino3->setActiveAnimation(2, 0.7);
	animatedRenderPool->addRenderObject(dino3);
	_abductees.push_back({ dino3 , -2, true, glm::vec3(70, 60, 80) });

	//Setup lights
	rgl::PointLight* light = new rgl::PointLight(glm::vec4(0.4f, 0.5f, 0.2f, 1));
	light->setMesh(assets->getMesh("sphere"));
	_renderer.addLight(light);
	_spinLight.push_back({ light, 2, false, 0, 3, glm::vec3(50,0,50) , glm::vec3(40,40,40) });

	rgl::PointLight* light2 = new rgl::PointLight(glm::vec4(0.3f, 0.6f, 0.1f, 1));
	light2->setMesh(assets->getMesh("sphere"));
	_renderer.addLight(light2);
	_spinLight.push_back({ light2, 2, false, 0, 7, glm::vec3(80, 10, 50) , glm::vec3(60, 60, 60) });

	rgl::PointLight* light3 = new rgl::PointLight(glm::vec4(0.3f, 0, 0.8f, 1));
	light3->setMesh(assets->getMesh("sphere"));
	_renderer.addLight(light3);
	_spinLight.push_back({ light3, 2, true, 0, 10, glm::vec3(100, 10, 90) , glm::vec3(40, 40, 40) });

	rgl::PointLight* light4 = new rgl::PointLight(glm::vec4(0.2f, 0.3f, 0.5f, 1));
	light4->setMesh(assets->getMesh("sphere"));
	_renderer.addLight(light4);
	_spinLight.push_back({ light4, 2, true, 0, 6, glm::vec3(75, 20, 75) , glm::vec3(40, 40, 40) });

	rgl::PointLight* light5= new rgl::PointLight(glm::vec4(1, 1, 1, 1));
	light5->setMesh(assets->getMesh("sphere"));
	_renderer.addLight(light5);
	_spinLight.push_back({ light5, 2, false, 0, 1, glm::vec3(85, 25, 75) , glm::vec3(25, 25, 25) });

	rgl::PointLight* light6 = new rgl::PointLight(glm::vec4(0.2f, 0.5f, 0.5f, 1));
	light6->setMesh(assets->getMesh("sphere"));
	_renderer.addLight(light6);
	_spinLight.push_back({ light6, 5, false, 0, 3, glm::vec3(85, 20, 75), glm::vec3(45, 45, 45) });

	rgl::PointLight* light7 = new rgl::PointLight(glm::vec4(1.0f, 0.4f, 0, 1));
	light7->setMesh(assets->getMesh("sphere"));
	_renderer.addLight(light7);
	_spinLight.push_back({ light7, 3, false, 0, 5, glm::vec3(85, 10, 75), glm::vec3(50, 50, 50) });

	rgl::PointLight* light8 = new rgl::PointLight(glm::vec4(0.7f, 0, 0.6f, 1));
	light8->setMesh(assets->getMesh("sphere"));
	_renderer.addLight(light8);
	_spinLight.push_back({ light8, 5, false, 0, 2, glm::vec3(85, 40, 75), glm::vec3(50, 50, 50) });

	rgl::SkyboxFX* skybox = new rgl::SkyboxFX({ assets->getShader("SkyboxVertexFX"), assets->getShader("SkyboxFragmentFX") }, assets->getCubemap("abduction"), _renderer.getDepthTexture(), _mainCamera);
	_renderer.addPostProcessingFX(skybox);

	_sceneNameText->setText("Alien Abduction");
}


float offset = 0;


void AbductionScene::draw(float delta)
{
	_cameraController->update(delta);
	_currentUfoRotation += delta * _ufoRotateSpeed;
	_ufoNode->setRotation(glm::rotate(glm::mat4(1), _currentUfoRotation, glm::vec3(0,1,0)));



	for (auto& a : _abductees) {
		a.RenderObject->update(delta);
		if (a.reverse) {
			a.CurrentPosition -= delta * _dinoAbductSpeed;
			if (a.CurrentPosition < -_dinoMovementRadius) {
				a.reverse = false;
			}
		}
		else {
			a.CurrentPosition += delta * _dinoAbductSpeed;
			if (a.CurrentPosition > _dinoMovementRadius) {
				a.reverse = true;
			}
		}
		a.RenderObject->setModelMatrix(glm::translate(glm::mat4(1), a.originalPosition + glm::vec3(0,a.CurrentPosition * _dinoMovementRadius,0)) 
													* glm::scale(glm::mat4(1), glm::vec3(std::max(abs(a.CurrentPosition) / _dinoMovementRadius, _dinoMinScale), std::max(abs(a.CurrentPosition) / _dinoMovementRadius, _dinoMinScale), std::max(abs(a.CurrentPosition) / _dinoMovementRadius, _dinoMinScale)))
													* glm::rotate(glm::mat4(1), -a.CurrentPosition, glm::vec3(1, 1, 0)));
	}

	for (auto& l : _spinLight) {
		l.currentSpin += delta * l.speed;
		if (l.reverse) {
			l.light->setModelMatrix(glm::translate(glm::mat4(1), l.originalPosition) * -glm::translate(glm::mat4(1), glm::vec3(sin(l.currentSpin), 0, cos(l.currentSpin) * l.spinRadius)) * glm::scale(glm::mat4(1), l.scale));
		}
		else {
			l.light->setModelMatrix(glm::translate(glm::mat4(1), l.originalPosition) * glm::translate(glm::mat4(1), glm::vec3(sin(l.currentSpin), 0, cos(l.currentSpin) * l.spinRadius)) * glm::scale(glm::mat4(1), l.scale));
		}

	}

	offset = offset + delta;
	if (offset > 3.14 * 2) {
		offset -= 3.14 * 2;
	}
	for (int i = 0; i < numberOfParticlesInBeam; ++i) {
		_beamParticles[i].Position = glm::vec3(sin(offset + i), i*0.005f, cos(offset + i));
		float colour = offset / (3.14 * 2);
		_beamParticles[i].Colour = glm::vec4(colour, 0.2f, 1 - colour, 1);
	}


	BaseScene::draw(delta);
}


