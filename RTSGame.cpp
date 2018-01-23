/**

RTSGame.cpp: ProjectRTS

Entry point of the application, and the central hub

See RTSGame.h for more

*/

// Include our header
#include "RTSGame.h"

using namespace std;
using namespace RTSEngine;

// -------------------------------------------------------------------------------------------------- RTSGame

/*
Inits the application for run-time
*/
int RTSGame::init() {

	windowTitle = "HelloWindow";

	// Set the context
	windowContextSettings.depthBits = 24;
	windowContextSettings.stencilBits = 8;
	windowContextSettings.antialiasingLevel = 8;

	// Request opengl 3.3
	windowContextSettings.majorVersion = 3;
	windowContextSettings.minorVersion = 3;

	// Init sfml for context
	window.create(sf::VideoMode(WIDTH, HEIGHT), windowTitle, sf::Style::Close, windowContextSettings);

	window.setVerticalSyncEnabled(true);

	// Init opengl states
	glViewport(0, 0, WIDTH, HEIGHT);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(true);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0, 1);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	circle.setRadius(50);
	circle.setFillColor(sf::Color(150, 50, 250));

	return EXIT_SUCCESS;

}

/*
Central node of the application
*/
void RTSGame::run() {

	// DEBUG TEST
	{
		MeshObject3D testMesh;
		testMesh.loadModelWithAssimp("./test.dae");
	}

	sf::Clock clock;

	while (running) {
		pollSFMLEvents();
		sim();
		display();

		// Close logic
		if (windowRequestClose)
			running = false;

		// ms per frame logic
		float currentTime = clock.getElapsedTime().asSeconds();
		nbFrames++;
		float dt = currentTime - lastTime;
		if (dt >= secsPerUpdate) {
			// Update the window title
			float avgMsFrame = nbFrames / (dt*1000.0f);
			fps = (int)(nbFrames / dt);
			window.setTitle(windowTitle + " " + std::to_string(avgMsFrame) + " ms/frame | FPS: " + std::to_string(fps) + " | dt: " + std::to_string(dt));
			nbFrames = 0;
			lastTime += secsPerUpdate;
		}
	}

	window.close();
}

/*
Runs the simulation step of the application
*/
void RTSGame::sim() {



}

/*
Does the on-screen rendering of the application
*/
void RTSGame::display() {
	// Activate the context attached to the window
	window.setActive(true);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw opengl 3d
	// ...

	// Do the SFML 2d drawing
	// NOTE: OWN STATE MANAGER AT SOME POINT?
	// Push the current states
	window.pushGLStates();
	// Draw
	displayGUI();
	// Pop the GL states
	window.popGLStates();

	// Do the buffer swap
	window.display();

	// Deactivate the context
	window.setActive(false);
}

void RTSGame::displayGUI() {

	//window.draw etc
	window.draw(circle);

}

void RTSGame::pollSFMLEvents() {
	sf::Event event;
	while (window.pollEvent(event))
	{
		// Close request
		if (event.type == sf::Event::Closed)
			windowRequestClose = true;
	}
}

// Entry point of application
int main() {

	RTSGame game;

	int rtVal = game.init();

	if (rtVal != EXIT_SUCCESS) {
		cout << "The RTSGame init failed to run correctly, terminating." << endl;
		return rtVal;
	}
	else {
		try {
			if (RTSGame::globalDebug)
				cout << "Global debug is enabled, so this is a debug release" << endl;

			game.run();
		}
		catch (int e) {
			// Exception occured
			cout << "An exception occured: " << e << endl;
			return EXIT_FAILURE;
		}
	}

	return 0;

}