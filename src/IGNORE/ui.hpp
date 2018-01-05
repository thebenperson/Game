/*
 *
 * Game Development Build
 * https://github.com/TheBenPerson/Game
 *
 * Copyright (C) 2016-2017 Ben Stockett <thebenstockett@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#ifndef GAME_CLIENT_GFX_MENU

#include <GL/gl.h>
#include <stddef.h>

#include "button.hpp"
#include "nodelist.hpp"
#include "timing.hpp"

typedef struct Panel {

	NodeList buttons;
	Button *selected;
	Panel *back;

} Panel;

extern GLuint bg;
extern Panel *panel;
extern Timing::mutex m;
void setPanel(Panel *panel);
bool actnBack();

extern Panel mmenu;
extern Panel about;

extern Panel settings;
extern Panel video;
extern Panel input;
extern void initSettings();
extern void cleanupSettings();

extern GLuint loading;
extern Panel cancel;

void tickLoading();
void drawLoading();

#define GAME_CLIENT_GFX_MENU
#endif
