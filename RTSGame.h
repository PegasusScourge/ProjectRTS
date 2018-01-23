#ifndef __INC_RTSGAME_H__
#define __INC_RTSGAME_H__
#pragma once

/**

RTSGame.h: ProjectRTS

Contains the definitions for the main .cpp file

In namespace RTSEngine, along with the rest of the engine files

*/

// INCLUDE - Dependancies

// std includes
#include <iostream>
#include <string>

// sfml includes
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

// opengl includes here?
//..

#include "RTSMesh3D.h"

// Include the define constants
#include "RTSDefineConsts.h"

namespace RTSEngine {

	class RTSGame;

	// Definitions
	class RTSGame {

	public:
		void run();
		int init();
		void sim();
		void display();
		void displayGUI();
		void pollSFMLEvents();

#ifdef _DEBUG
		static const bool globalDebug = true;
#else
		static const bool globalDebug = false;
#endif

	private:
		// The window
		sf::RenderWindow window;
		sf::ContextSettings windowContextSettings;

		int WIDTH = 800;
		int HEIGHT = 600;

		std::string windowTitle;

		// The exit condition
		bool running = true;

		// Window monitoring bools
		bool windowRequestClose = false;

		// Misc
		sf::CircleShape circle;

		// FPS
		float lastTime = 0;
		int nbFrames;
		float secsPerUpdate = 1.0f;
		int fps = 0;

	};
}

int main();

#endif
