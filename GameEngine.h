#pragma once

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include "Camera.h"
#include "TriangleRenderer.h"
#include "QuadRenderer.h"
#include "ModelRenderer.h"
#include "Model.h"

#include "Terrain.h"
#include "Texture.h"
#include "SkyDome.h"


namespace GE {
	class GameEngine {
	public:
		GameEngine();						// Class default constructor
		GameEngine(int _w, int _h);			// Class overloaded constructor
		virtual ~GameEngine();				// Virtual destructor
		bool init(bool vsync = false);		// Object initialisation, vsync default off
		bool keep_running();				// Window closed?
		void update();						// Update Game Logic
		void draw();						// Render the frame
		void shutdown();					// Release objects and close safely

		void setwindowtitle(const char*);
		bool fullscreen = false;			// Logic handle for fullscreen mode
		int w, h;							// Window width and height
		int windowflags;					// Hold info on how to display the window
	private:
		// Privately encapsulated data
		// SDL window object to represent the frame
		SDL_Window* window;

		// SDL GL context to represent OpenGL in the program
		SDL_GLContext glContext;

		// Camera
		Camera* cam;

		// Object renderers
		TriangleRenderer* tri;
		QuadRenderer* quad;
		ModelRenderer* modelRenderer;
		std::unique_ptr<Model> model;

		// Scene Objects
		Texture* terrainTexture;
		Texture* skydomeTexture;
		Terrain* terrain;
		Skydome* skydome;

	};

	// Helper Function
	void display_info_message(const char*);
}