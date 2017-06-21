#include "client.hpp"
#include "gfx/gfx.hpp"
#include "menu.hpp"
#include "win/win.hpp"

namespace Menu {

	GLuint loading;

	Button* bCancel[] = {

		(Button*) main,
		new Button({0, -3}, 10.0f, "Cancel", cancel),
		NULL

	};

	bool cancel() {

		Client::setState(Client::PAUSED);
		actnBack();

	}

	void tickLoading() {



	}

	void drawLoading() {

		static float i = 0;
		i += 0.05f;

		glMatrixMode(GL_TEXTURE);
		glBindTexture(GL_TEXTURE_2D, loading);

		glBegin(GL_QUADS);

		glTexCoord2f(0.0f, 0.75f);
		glVertex2f(-5, 4.0f);
		glTexCoord2f(1.0f, 0.75f);
		glVertex2f(-3, 4.0f);
		glTexCoord2f(1.0f, 0.5f);
		glVertex2f(-3, 0.0f);
		glTexCoord2f(0.0f, 0.5f);
		glVertex2f(-5, 0.0f);

		glTexCoord2f(0.0f, 0.5f);
		glVertex2f(3, 4.0f);
		glTexCoord2f(1.0f, 0.5f);
		glVertex2f(5, 4.0f);
		glTexCoord2f(1.0f, 0.25f);
		glVertex2f(5, 0.0f);
		glTexCoord2f(0.0f, 0.25f);
		glVertex2f(3, 0.0f);

		glEnd();

		glPushMatrix();
		glTranslatef(-i, 0, 0);
		glBegin(GL_QUADS);

		glTexCoord2f(0.0f, 1.0f);
		glVertex2f(-3.0f, 4.0f);
		glTexCoord2f(5.0f, 1.0f);
		glVertex2f(3.0f, 4.0f);
		glTexCoord2f(5.0f, 0.75f);
		glVertex2f(3.0f, 0.0f);
		glTexCoord2f(0.0f, 0.75f);
		glVertex2f(-3.0f, 0.0f);

		glEnd();
		glPopMatrix();

		glMatrixMode(GL_MODELVIEW);

		GFX::drawText("Loading...", {0, 2}, 1, true);

	}

}