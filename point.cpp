#include "point.h"

double Point::total_risk = 0;
int Point::total_palladium = 0;
int Point::total_iridium = 0;
int Point::total_platinum = 0;

Point::Point() {
	
	access_risk = (double) (rand()%90000)/100000;
	palladium = rand()%100;
	iridium = rand()%100;
	platinum = rand()%100;
	
	danger_flag = false;
	
	total_risk += access_risk;
	total_palladium += palladium;
	total_iridium += iridium;
	total_platinum += platinum;
}


int Point::get_palladium() {
	return palladium;
}

int Point::get_iridium() {
	return iridium;
}

int Point::get_platinum() {
	return platinum;
}

void Point::set_palladium(int amount) {
	palladium = amount;
}

void Point::set_iridium(int amount) {
	iridium = amount;
}

void Point::set_platinum(int amount) {
	platinum = amount;
}

double Point::get_access_risk() {
	return access_risk;
}

void Point::set_access_risk(double acc_risk) {
	access_risk = acc_risk;
}

bool Point::get_danger_flag() {
	return danger_flag;
}

void Point::set_danger_flag() {
	danger_flag = true;
}

void Point::update_palladium(int mined) {
	palladium -= mined;
}

void Point::update_iridium(int mined) {
	iridium -= mined;
}

void Point::update_platinum(int mined) {
	platinum -= mined;
}

double Point::get_total_risk() {
	return total_risk;
}

int Point::get_total_palladium() {
	return total_palladium;
}

int Point::get_total_iridium() {
	return total_iridium;
}

int Point::get_total_platinum() {
	return total_platinum;
}
