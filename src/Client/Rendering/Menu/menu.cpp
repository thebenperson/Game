#include <cstddef>
#include "menu.hpp"
#include "Util/NodeList/nodelist.hpp"

bool Menu::active = true;
NodeList Menu::panels[1];
bool Menu::inGame = false;
unsigned char Menu::mode = 0;

void Menu::cleanup() {

	for (unsigned int i = 0; i < 1; i++) {

		unsigned int len = panels[i].len;

		for (unsigned int j = 0; j < len; j++)
			delete (Button *) panels[i].get(j);

	}

	Button::cleanup();

}

void Menu::init() {

	Button::init();

	panels[0].add(new Button({0.0f, 0.0f}, 9.0f, NULL));

}