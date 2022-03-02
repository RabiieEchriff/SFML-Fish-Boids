#include "Window.h"

sf::RenderWindow w(sf::VideoMode(1000, 700), "Fish Schooling Simulation");
sf::Event e;
window_methods mw;

void window_methods::close_window() {
	while (w.pollEvent(e)) {
		ImGui::SFML::ProcessEvent(e);
		switch (e.type) {
		case sf::Event::Closed:
			w.close();
			break;
		}
	}
}

