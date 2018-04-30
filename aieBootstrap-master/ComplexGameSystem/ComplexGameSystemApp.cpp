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
	AD = new AudioSystem();
	AD->OnCreate();
	AD->LoadAudio("../bin/audio/SKRILLEX.mp3");
	AD->PlayAudio();
	//AD->FrequencyAnalysis();
	return true;
}

void ComplexGameSystemApp::shutdown() {
	AD->OnDestroy();
	delete m_font;
	delete m_2dRenderer;
}

void ComplexGameSystemApp::update(float deltaTime) {

	AD->UpdateAudio();
	AD->FrequencyAnalysis();


	// input example
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_SPACE))
		AD->Pause(true);
	if (input->isKeyDown(aie::INPUT_KEY_C))
		AD->Pause(false);

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void ComplexGameSystemApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();
	float x = 1;
	// draw your stuff here!
	for (int i = 0; i < 32; ++i)
	{
		m_2dRenderer->drawBox(x, 360, 38, AD->f[i]);
		x += 50;
	}

	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}