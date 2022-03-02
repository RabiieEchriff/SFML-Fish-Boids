#include "Boid.h"
#include <vector>
#include <iostream>
#include "sundry.h"
#include "Timer.h"
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

float Boid::speed;
int Boid::align_range;
int Boid::cohere_range;
int Boid::separate_range;

int main() {
	
	//handle events here
	ImGui::SFML::Init(w);

	sundry s;

	std::vector<Boid>boids;

	Boid::speed = 0.003;
	Boid::align_range = 50;
	Boid::cohere_range = 48;
	Boid::separate_range = 52;

	bool align_flag = true;
	bool cohere_flag = true;
	bool separate_flag = true;

	bool wall_switch = true;

	float time = 0;

	//handle events here
	sf::Clock deltaClock;
	while (w.isOpen()) {

		mw.close_window();
		ImGui::SFML::Update(w, deltaClock.restart());
		//update game logic here
		ImGui::Begin("Controls");
		ImGui::Text("Spawn Boids:");
		if (ImGui::Button("+10 Boid", { 100,20 })) {
			for (int i = 0; i < 10; i++) {
				float spawn_x = rand() % w.getSize().x;
				float spawn_y = rand() % w.getSize().y;
				float angle = rand() % 360;
				boids.push_back(Boid({ spawn_x,spawn_y }, angle, sf::Color(rand() % 255, rand() % 255, rand() % 255, 200)));
			}
		}
		if (ImGui::Button("+50 Boids", { 100,20 })) {
			for (int i = 0; i < 50; i++) {
				float spawn_x = rand() % w.getSize().x;
				float spawn_y = rand() % w.getSize().y;
				float angle = rand() % 360;
				boids.push_back(Boid({ spawn_x,spawn_y }, angle, sf::Color(rand() % 255, rand() % 255, rand() % 255, 200)));
			}
		}
		if (ImGui::Button("Clear", { 100,20 })) { boids.clear(); }
		std::string boid_number = "Boids" + std::to_string(boids.size());
		ImGui::Text(("Boids: " + std::to_string(boids.size())).c_str());
		ImGui::Checkbox("Alignment", &align_flag);
		ImGui::InputInt("ARange", &Boid::align_range);
		ImGui::Checkbox("Coherence", &cohere_flag);
		ImGui::InputInt("CRange", &Boid::cohere_range);
		ImGui::Checkbox("Sepration", &separate_flag);
		ImGui::InputInt("SRange", &Boid::separate_range);
		ImGui::Checkbox("Walls", &wall_switch);
		if (wall_switch) { ImGui::Text("Solid"); }
		else{ ImGui::Text("Wrap-around"); }
		ImGui::SliderFloat("Speed", &Boid::speed, 0, 0.01);
		ImGui::End();

		for (int i = 0; i < boids.size(); i++) {
			boids[i].move();

			for (int j = 0; j < boids.size(); j++) {
				if (j != i) {
					boids[i].findNearestBoid(boids[j]);
					if (align_flag) { boids[i].align(boids[j]); }
					if (cohere_flag) { boids[i].cohere(boids[j]); }
					if (separate_flag) { boids[i].separate(boids[j]); }
					boids[i].wall(wall_switch);
				}

			}
			
		}

		w.clear();

		//draw objects here
		for (int i = 0; i < boids.size(); i++) { w.draw(boids[i].shape); }
		//draw objects here
		ImGui::SFML::Render(w);
		w.display();
	}
}





