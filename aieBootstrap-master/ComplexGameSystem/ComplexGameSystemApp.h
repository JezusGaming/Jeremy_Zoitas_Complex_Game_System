#pragma once
#include "AudioSystemUI.h"
#include "Application.h"
#include "Renderer2D.h"

class ComplexGameSystemApp : public aie::Application {
public:

	ComplexGameSystemApp();
	virtual ~ComplexGameSystemApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:
	AudioSystemUI * audioSystemUI;
	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	float freq;
};