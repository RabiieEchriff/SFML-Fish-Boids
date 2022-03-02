#pragma once
#include "Window/Window.h"
#include "Timer.h"
#include "Sundry.h"
#include <math.h>

class Boid {
public:
	timer T;
	float t;
	sundry s;
	sf::Vector2f head;
	float angle;
	sf::ConvexShape shape;
	static int align_range;
	static int cohere_range;
	static int separate_range;

	float dist;

	sf::Vector2f direct;

	//float speed = std::stoi(s.file_input("boid_speed.txt"));
	static float speed;

	float avg_ang = 0;

	Boid(sf::Vector2f head, float angle, sf::Color color);
	void findNearestBoid(Boid other);
	void align(Boid other);
	void cohere(Boid other);
	void separate(Boid other);

	void move();

	void wall(bool switcher);
};
