#pragma once
#include "AudioSystemUI.h"
#include "Application.h"
#include "Renderer2D.h"

class ComplexGameSystemApp : public aie::Application {
public:
	//----------------------------------------------------------------------------------------------
	// default constructor
	//----------------------------------------------------------------------------------------------
	ComplexGameSystemApp();

	//----------------------------------------------------------------------------------------------
	// default destructor
	//----------------------------------------------------------------------------------------------
	virtual ~ComplexGameSystemApp();

	//----------------------------------------------------------------------------------------------
	// Startup is used to initiliaze values and call functions which need to be called at the start
	// of the application.
	//----------------------------------------------------------------------------------------------
	virtual bool startup();

	//----------------------------------------------------------------------------------------------
	// Used to destroy pointers to stop memory leaks
	//----------------------------------------------------------------------------------------------
	virtual void shutdown();

	//----------------------------------------------------------------------------------------------
	// updates the game
	//
	// Param:
	//		deltaTime: calls a timer every frame per second that holds the time between now and last
	//		call
	//----------------------------------------------------------------------------------------------
	virtual void update(float deltaTime);

	//----------------------------------------------------------------------------------------------
	// Used to draw things like shapes, textures, text, etc.
	//----------------------------------------------------------------------------------------------
	virtual void draw();

protected:
	//----------------------------------------------------------------------------------------------
	// A pointer to AudioSystemUI.
	//----------------------------------------------------------------------------------------------
	AudioSystemUI * audioSystemUI;
	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	float freq;
};