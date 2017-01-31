#include <GL/gl.h>
#include <stdio.h>
#include "Button.hpp"
#include "Rendering/rendering.hpp"
#include "Util/Point/point.h"
#include "XClient/xclient.hpp"
#include "XInput/xinput.hpp"

GLuint Button::texture;

Button::Button(Point pos, float width, void (*callback)()) {

	float deltaX = width / 2.0f;
	float deltaY = 2.0f / 2.0f;

	float capRatio = 1.0f;

	values[0] = X - deltaX;
	values[1] = Y - deltaY;
	values[2] = X + deltaX;
	values[3] = Y + deltaY;
	values[4] = values[0] + capRatio;
	values[5] = values[2] - capRatio;
	values[6] = (width - 2.0f) / capRatio;

	this->callback = callback;

}

void Button::Cleanup() {

	glDeletetextures(1, &texture);

}

void Button::Init() {

	texture = Rendering::loadtexture("res/button.png");

}

void Button::Tick() {

	if (((XInput::mousePos.x > values[0]) && (XInput::mousePos.y > values[1])) && ((XInput::mousePos.x < values[2]) && (XInput::mousePos.y < values[3]))) {

		if (XInput::mousePress) {

			state = (unsigned char) 2;

		} else {

			if (state == 2)
				callback();

			state = (unsigned char) 1;

		}

	} else {

		state = 0;

	}

}

void Button::Render() {

	glPushMatrix();

		glMatrixMode(GL_texture);
		glPushMatrix();

			glTranslatef(0.0f, state / 4.0f, 0.0f);

			glBindtexture(GL_texture_2D, texture);

			glBegin(GL_QUADS);

				glTexCoord2f(0.0f, 0.125f);
				glVertex2f(values[0], values[1]);
				glTexCoord2f(1.0f, 0.125f);
				glVertex2f(values[4], values[1]);
				glTexCoord2f(1.0f, 0.0f);
				glVertex2f(values[4], values[3]);
				glTexCoord2f(0.0f, 0.0f);
				glVertex2f(values[0], values[3]);

				glTexCoord2f(0.0f, 0.25f);
				glVertex2f(values[4], values[1]);
				glTexCoord2f(values[6], 0.25f);
				glVertex2f(values[5], values[1]);
				glTexCoord2f(values[6], 0.125f);
				glVertex2f(values[5], values[3]);
				glTexCoord2f(0.0f, 0.125f);
				glVertex2f(values[4], values[3]);

				glTexCoord2f(1.0f, 0.125f);
				glVertex2f(values[5], values[1]);
				glTexCoord2f(0.0f, 0.125f);
				glVertex2f(values[2], values[1]);
				glTexCoord2f(0.0f, 0.0f);
				glVertex2f(values[2], values[3]);
				glTexCoord2f(1.0f, 0.0f);
				glVertex2f(values[5], values[3]);

			glEnd();

		glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

}
