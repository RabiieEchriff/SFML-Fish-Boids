#include "Boid.h"
#include <iostream>


Boid::Boid(sf::Vector2f head, float angle, sf::Color color) :head(head), angle(angle) {

	shape.setPointCount(3);
	shape.setPoint(0, head);
	shape.setPoint(1, sf::Vector2f(head.x - 2.5, head.y + 10));
	shape.setPoint(2, sf::Vector2f(head.x + 2.5, head.y + 10));
	shape.setOrigin(sf::Vector2f(shape.getPoint(0).x, shape.getPoint(0).y + 5));
	shape.setOrigin(sf::Vector2f(head.x, head.y + 5));
	shape.setRotation(angle);
	shape.setFillColor(sf::Color(color));
	shape.setPosition(head);

	direct.x = cos(shape.getRotation()) * 2000000;
	direct.y = sin(shape.getRotation()) * 2000000;

}

void Boid::findNearestBoid(Boid other) {

	dist = sqrt(pow(shape.getPosition().x - other.shape.getPosition().x, 2) + pow(shape.getPosition().y - other.shape.getPosition().y, 2));

}


void Boid::align(Boid other) {
	
	if (dist < align_range) {
		direct.x = (direct.x + other.direct.x) / 2;
		direct.y = (direct.y + other.direct.y) / 2;
	}
	
}

void Boid::cohere(Boid other) {

	if (dist > cohere_range) {
		direct.x = (direct.x + (other.shape.getPosition().x - shape.getPosition().x));
		direct.y = (direct.y + (other.shape.getPosition().y - shape.getPosition().y));
		
	}
	
}

void Boid::separate(Boid other) {
	
	if (dist < separate_range) {
		direct.x = (direct.x + (shape.getPosition().x - other.shape.getPosition().x) * 1500);
		direct.y = (direct.y + (shape.getPosition().y - other.shape.getPosition().y) * 1500);
	}
	
}

void Boid::move() {

	t = T.accumulate_time();
	shape.move(sf::Vector2f((direct.x) * t * ((speed) / 40), (direct.y) * t * ((speed) / 40)));
	shape.setRotation((atan2(direct.y, direct.x) * 180 / 3.14) + 90);

	if (direct.x < 1000000 && direct.y < 1000000) {

		direct.x += cos(shape.getRotation()) * 2000000;
		direct.y += sin(shape.getRotation()) * 2000000;

	}

}

void Boid::wall(bool switcher) {
	int boundary = 30;
	switch(switcher){
	case true: {
		if (shape.getPosition().x < boundary) { direct.x += 1000 * (boundary - shape.getPosition().x); }
		else if (shape.getPosition().x > w.getSize().x - boundary) { direct.x += -(1000 * (boundary - (w.getSize().x - shape.getPosition().x))); }
		else if (shape.getPosition().y < boundary) { direct.y += 1000 * (boundary - shape.getPosition().y); }
		else if (shape.getPosition().y > w.getSize().y - boundary) { direct.y += -(1000 * (boundary - (w.getSize().y - shape.getPosition().y))); }
	}break;

	case false: {
		if (shape.getPosition().x < -10) { shape.setPosition(sf::Vector2f(w.getSize().x + 10, shape.getPosition().y)); }
		else if (shape.getPosition().y < -10) { shape.setPosition(sf::Vector2f(shape.getPosition().x, w.getSize().y + 10)); }
		else if (shape.getPosition().x > w.getSize().x + 10) { shape.setPosition(sf::Vector2f(-10, shape.getPosition().y)); }
		else if (shape.getPosition().y > w.getSize().y + 10) { shape.setPosition(sf::Vector2f(shape.getPosition().x, -10)); }
	}break;

	default:break;
	}
}
