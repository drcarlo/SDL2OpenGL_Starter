#include "GameEngine.h"
#include <iostream>
#include <assert.h>

namespace GE {
	GameEngine::GameEngine() {
		w = 1280;
		h = 1024;
		windowflags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
	}
	GameEngine::GameEngine(int _w, int _h) {
		w = _w;
		h = _h;
		windowflags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
	}
	GameEngine::~GameEngine() {

	}
	bool GameEngine::init(bool vsync) {
		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			std::cerr << "Unable to initialise SDL! SDL error: " << SDL_GetError() << std::endl;
			return false;
		}
		// Set the OpenGL version for the program
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3); // OpenGL 3+
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1); // OpenGL 3.1
		// Set the type of profile which is core meaning modern OpenGL
		// means no legacy features for backwards compatibility
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		// Create the window frame and features
		// Fixed size window created for OpenGL to render to
		window = SDL_CreateWindow("CMP5334 Programming for Game Engines SDL OpenGL", 50, 50, w, h, windowflags);
		// Check window was created: http://www.cplusplus.com/reference/cassert/assert/
		assert(window);

		// Create the OpenGL context and link to the window object
		// Context represents OpenGL for program such as objects and drawing
		glContext = SDL_GL_CreateContext(window);
		// Check the context object was created
		assert(glContext);
		// Check we are setup with the correct GL version
		std::cout << "glGetString (GL_VERSION) returns: " << glGetString(GL_VERSION) << std::endl;

		// Initialise GLEW. GLEW solves a problem with OpenGL on windows
		// OpenGL version supported on Windows is 1.1 (from 1997)
		// GLEW binds latest extensions that can be used
		GLenum status = glewInit();
		// Check GLEW initialised
		if (status != GLEW_OK) {
			std::cerr << "Error initialising GLEW! Error: " << glewGetErrorString(status) << std::endl;
			return false;
		}

		// Try to turn on VSync, if requested
		if (vsync) {
			if (SDL_GL_SetSwapInterval(1) != 0) {
				std::cerr << "Warning: unable to set VSync! Error: " << SDL_GetError() << std::endl;
				return false;
			}
		}

		// Create camera object
		cam = new Camera(glm::vec3(0.0f, 0.0f, 5.0f),	// cam position
			glm::vec3(0.0f, 0.0f, 0.0f),				// cam look at
			glm::vec3(0.0f, 1.0f, 0.0f),				// cam up direction
			90.0, w / h, 0.1f, 100.0f);					// fov, aspect ratio, near and far clip planes

		// Initialise the object renderers
		quad = new QuadRenderer();
		quad->init();

		// Woo! All setup so we can return success
		return true;
	}

	// Check if the window was closed and SDL_QUIT message was resultant
	bool GameEngine::keep_running() {
		// Need to do this to keep the event queue up to date
		SDL_PumpEvents();

		SDL_Event evt;

		// Check for quit event
		if (SDL_PeepEvents(&evt, 1, SDL_GETEVENT, SDL_QUIT, SDL_QUIT)) {
			// If user quit the program, then return false
			return false;
		}

		// If no SDL_QUIT event in event queue then keep running
		return true;
	}

	// Update method which updates the game logic
	// Used to invoke GE object update methods
	void GameEngine::update() {
		quad->update();
	}

	// Draw method. Used to render scenes to the window frame
	// For now, just clears the background
	void GameEngine::draw() {
		glClearColor(0.392f, 0.584f, 0.929f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// GL Immediate mode to render a triangle to the screen
		// Requires setting GL minor version to 3.1
		/*glBegin(GL_TRIANGLES);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex2f(-1.0f, 0.0f);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex2f(1.0f, 0.0f);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex2f(0.0f, 2.0f);
		glEnd();*/

		// Render the VBOs
		quad->draw(cam);

		SDL_GL_SwapWindow(window);
	}

	// Shutdown method closes OpenGL and SDL
	// When additional objects are added, ensure these are also freed safely
	void GameEngine::shutdown() {
		// Release object renderers
		quad->destroy();
		
		// Release memory associate with camera and primitive renderers
		delete quad;
		delete cam;

		SDL_GL_DeleteContext(glContext);
		SDL_DestroyWindow(window);
		window = nullptr;
		SDL_Quit();
	}

	// Helped to set text in the window title bar
	void GameEngine::setwindowtitle(const char* new_title) {
		SDL_SetWindowTitle(window, new_title);
	}

	// Helper function to display program information
	// Part of the namespace, but not the GameEngine class
	void display_info_message(const char* msg) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Basic Game Engine", msg, nullptr);
	}
}