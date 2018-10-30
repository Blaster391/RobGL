
#include <RobGL/Renderer.h>
#include <Window/Window.h>

int main() {
	Window w;
	w.startup();

	if (w.hasFailed()) {
		return -1;
	}

	rgl::Renderer renderer(w);
	bool finished = false;


	//Setup world
	rgl::Shader* vertexShader = new rgl::Shader("Shaders/testVert.glsl", GL_VERTEX_SHADER);
	rgl::Shader* fragmentShader = new rgl::Shader("Shaders/testFrag.glsl", GL_FRAGMENT_SHADER);

	std::vector<rgl::Shader*> shaders;
	shaders.push_back(vertexShader);
	shaders.push_back(fragmentShader);


	Camera mainCamera;
	mainCamera.setPerspective();

	rgl::RenderPool pool(shaders, &mainCamera);

	rgl::RenderObject ro;
	pool.addRenderObject(&ro);


	renderer.addRenderPool(&pool);

	while (!finished) {
		w.update(1);

		renderer.update();

		finished = w.ShouldClose();
	}

	w.shutdown();

	delete vertexShader;
	delete fragmentShader;

	return 0;
}