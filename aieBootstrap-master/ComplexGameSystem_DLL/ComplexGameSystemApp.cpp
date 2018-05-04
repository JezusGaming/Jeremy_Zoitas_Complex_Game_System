#include "ComplexGameSystemApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

//----------------------------------------------------------------------------------------------
// default constructor
//----------------------------------------------------------------------------------------------
ComplexGameSystemApp::ComplexGameSystemApp() {

}

//----------------------------------------------------------------------------------------------
// default destructor
//----------------------------------------------------------------------------------------------
ComplexGameSystemApp::~ComplexGameSystemApp() {

}

//----------------------------------------------------------------------------------------------
// Startup is used to initiliaze values and call functions which need to be called at the start
// of the application.
//----------------------------------------------------------------------------------------------
bool ComplexGameSystemApp::startup() {
	
	// Initializes m_2dRenderer.
	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	// Initializes audioSystemUI.
	audioSystemUI = new AudioSystemUI();

	return true;
}

//----------------------------------------------------------------------------------------------
// Used to destroy pointers to stop memory leaks
//----------------------------------------------------------------------------------------------
void ComplexGameSystemApp::shutdown() {

	// deletes the AudioSystem.
	delete audioSystemUI;

	// deletes the m_font.
	delete m_font;

	// deletes the m_2dRenderer.
	delete m_2dRenderer;
}

//----------------------------------------------------------------------------------------------
// updates the game
//
// Param:
//		deltaTime: calls a timer every frame per second that holds the time between now and last
//		call
//----------------------------------------------------------------------------------------------
void ComplexGameSystemApp::update(float deltaTime) {

	// Updates the UI and audio.
	audioSystemUI->Update();

	// input example
	aie::Input* input = aie::Input::getInstance();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

//----------------------------------------------------------------------------------------------
// Used to draw things like shapes, textures, text, etc.
//----------------------------------------------------------------------------------------------
void ComplexGameSystemApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	// Sets RGB floats to 0.
	float x = 0;
	float R = 0;
	float G = 0;
	float B = 0;
	// Goes through a loop and draws 320 bars that change colour throughout.
	for (int i = 0; i < 320; ++i)
	{
		// Checks if i is less than 53 then increases the red value.
		if (i < 53)
		{
			R = i * 0.16f;
			m_2dRenderer->setRenderColour(R, G, B, 1);
		}
		// Checks if i is less than 106 and greater than 53 then increases the green value.
		else if (i >= 53 && i < 106)
		{
			G = (i - 53) * 0.16f;
			m_2dRenderer->setRenderColour(R, G, B, 1);
		}
		// Checks if i is less than 159 and greater than 106 then decreases the red value.
		 else if (i >= 106 && i < 159)
		{
			R = 1 - ((i - 106) * 0.16f);
			m_2dRenderer->setRenderColour(R, G, B, 1);
		}
		// Checks if i is less than 212 and greater than 159 then increases the blue value.
		else if (i >= 159 && i < 212)
		{
			B = (i - 159) * 0.16f;
			m_2dRenderer->setRenderColour(R, G, B, 1);
		}
		// Checks if i is less than 265 and greater than 212 then decreases the green value.
		else if (i >= 212 && i < 265)
		{
			G = 1 - ((i - 212) * 0.16f);
			m_2dRenderer->setRenderColour(R, G, B, 1);
		}
		// Checks if i is less than 320 and greater than 265 then decreases the blue value.
		else if (i >= 265 && i < 320)
		{
			R = (i - 265) * 0.16f;
			m_2dRenderer->setRenderColour(R, G, B, 1);
		}
		// Draws a box with and moves it based on the spectrum data.
		m_2dRenderer->drawBox(x, 500, 6, audioSystemUI->m_fSpectrumData[i]);
		// Increases the placement by 6 on the x.
		x += 6;
		// Sets the render colour back to white.
		m_2dRenderer->setRenderColour(1, 1, 1, 1);
	}

	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}