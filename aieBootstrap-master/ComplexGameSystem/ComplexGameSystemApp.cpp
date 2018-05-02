#include "ComplexGameSystemApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"


ComplexGameSystemApp::ComplexGameSystemApp() {

}

ComplexGameSystemApp::~ComplexGameSystemApp() {

}

bool ComplexGameSystemApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);
	audioSystemUI = new AudioSystemUI();
	return true;
}

void ComplexGameSystemApp::shutdown() {
	delete audioSystemUI;
	delete m_font;
	delete m_2dRenderer;
}

void ComplexGameSystemApp::update(float deltaTime) {

	audioSystemUI->Update();

	// input example
	aie::Input* input = aie::Input::getInstance();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void ComplexGameSystemApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();
	float x = 0;
	float R = 0;
	float G = 0;
	float B = 0;
	// draw your stuff here!
	for (int i = 0; i < 127; ++i)
	{

		if (i < 21)
		{
			R = i * 0.16;
			m_2dRenderer->setRenderColour(R, G, B, 1);
		}
		else if (i >= 21 && i < 42)
		{
			G = (i - 21) * 0.16;
			m_2dRenderer->setRenderColour(R, G, B, 1);
		}
		 else if (i >= 42 && i < 63)
		{
			R = 1 - ((i - 42) * 0.16);
			m_2dRenderer->setRenderColour(R, G, B, 1);
		}
		else if (i >= 63 && i < 84)
		{
			B = (i - 63) * 0.16;
			m_2dRenderer->setRenderColour(R, G, B, 1);
		}
		else if (i >= 84 && i < 105)
		{
			G = 1 - ((i - 21) * 0.16);
			m_2dRenderer->setRenderColour(R, G, B, 1);
		}
		else if (i >= 105 && i < 126)
		{
			R = (i - 105) * 0.16;
			m_2dRenderer->setRenderColour(R, G, B, 1);
		}
		m_2dRenderer->drawBox(x, 360, 10, audioSystemUI->m_fSpectrumData[i]);
		x += 11;
		m_2dRenderer->setRenderColour(1, 1, 1, 1);
	}

	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}