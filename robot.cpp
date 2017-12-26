#include "robot.h"

using namespace std;

int Robot::overall_damages = 0;
int Robot::overall_flags = 0;
int Robot::overall_palladium_mined = 0;
int Robot::overall_iridium_mined = 0;
int Robot::overall_platinum_mined = 0;
int Robot::active_robots = 0;
int Robot::id_counter = 0;

Robot::Robot(int x_coord, int y_coord) : id(Robot::id_counter++), speed(rand()%3 + 1), access_ability((double) rand()/RAND_MAX) {
	x = x_coord;
	y = y_coord;
	damaged_state = false;
	step_counter = 0;
	inactivity_counter = 0;
	permanent_damaged = false;
	move_counter = 0;
	damage_counter = 0;
	active_robots++;
}

void Robot::move_and_op(vector< vector<Point*> >& map, vector<Robot*>& rb) {
	
	if (!get_damaged_state()) {
		inactivity_counter = 0;
		//if robot is ok
		if (step_counter == 0) {
			//if it's reached the new destination
			operate(map, rb); //do your thing
			//and then choose new direction
			if (get_x() == 0 && get_y() == 0) {
				int new_direction = rand()%2;
				switch (new_direction) {
					case 0:
						direction = 'd';
						break;
					case 1:
						direction = 'r';
				}
			}
			else if (get_x() == 0 && get_y() == Y_size-1) {
				int new_direction = rand()%2;
				switch (new_direction) {
					case 0:
						direction = 'l';
						break;
					case 1:
						direction = 'd';
				}				
			}
			else if (get_x() == X_size-1 && get_y() == 0) {
				int new_direction = rand()%2;
				switch (new_direction) {
					case 0:
						direction = 'u';
						break;
					case 1:
						direction = 'r';
				}	
			}
			else if (get_x() == X_size-1 && get_y() == Y_size-1) {
				int new_direction = rand()%2;
				switch (new_direction) {
					case 0:
						direction = 'l';
						break;
					case 1:
						direction = 'u';
				}
			}
			else if (y == 0) {								
				int new_direction = rand()%3;
				switch (new_direction) {
					case 0:
						direction = 'd';
						break;
					case 1:
						direction = 'u';
						break;
					case 2:
						direction = 'r';
				}
			}
			else if (get_x() == 0) {
				int new_direction = rand()%3;
				switch (new_direction) {
					case 0:
						direction = 'l';
						break;
					case 1:
						direction = 'd';
						break;
					case 2:
						direction = 'r';
				}
			}
			else if (get_x() == X_size-1) {
				int new_direction = rand()%3;
				switch (new_direction) {
					case 0:
						direction = 'l';
						break;
					case 1:
						direction = 'u';
						break;
					case 2:
						direction = 'r';
				}
			}
			else if (y == Y_size-1) {
				int new_direction = rand()%3;
				switch (new_direction) {
					case 0:
						direction = 'l';
						break;
					case 1:
						direction = 'd';
						break;
					case 2:
						direction = 'u';
				}
			}
			else {
				int new_direction = rand()%4;
				switch (new_direction) {
					case 0:
						direction = 'l';
						break;
					case 1:
						direction = 'd';
						break;
					case 2:
						direction = 'u';
						break;
					case 3:
						direction = 'r';
				}
			}
		}
				
		if (step_counter == speed) {
			//if robot has covered all the steps
			int x_change = 0;
			int y_change = 0;
			switch (direction) {
				case 'l': //move left
					y_change = -1;
					break;
				case 'd': //move down
					x_change = 1;
					break;
				case 'u': //move up
					x_change = -1;
					break;
				case 'r': //move right
					y_change = 1;
			}
			//check if there is a flag in the point you're about to enter
			if (map[get_x()+x_change][get_y()+y_change]->get_danger_flag() == true) {
				printw("Robot_%d can't move to (%d,%d), it's too dangerous.\n", get_id(), get_x()+x_change, get_y()+y_change);
			}
			else { //enter new point
				update_coord(x_change, y_change);
				printw("Robot_%d moves to (%d,%d).\n", get_id(), get_x(), get_y());
				move_counter++;			
				if ((map[get_x()][get_y()]->get_access_risk())*(1 - access_ability) > ((double) rand()/RAND_MAX)) {
					set_damaged_state(true);
					inc_damage_counter();
					inc_overall_damages();
					dec_active_robots();
					printw("\tFailure during move.\n");
				}
			}
			
			//reset counter in any case
			step_counter = 0;
			
		}
		//robot is in intermediate position (moving)
		else {
			printw("Robot_%d is moving.\n", get_id());
			step_counter++;
		}
				
	}
	else {
		//if it's damaged
		inactivity_counter++;
		if (inactivity_counter == 15) {
			permanent_damaged = true;
		}
	}
}

int Robot::get_speed() {
	return speed;
}

bool Robot::get_damaged_state() {
	return damaged_state;
}

void Robot::set_damaged_state(bool d) {
	damaged_state = d;
}

bool Robot::get_permanent_damaged() {
	return permanent_damaged;
}

int Robot::get_id() {
	return id;
}

int Robot::get_x() {
	return x;
}

int Robot::get_y() {
	return y;
}

void Robot::update_coord(int x_change, int y_change) {
	x += x_change;
	y += y_change;
}

void Robot::return_to_base() {
	x = base_x;
	y = base_y;
}

void Robot::inc_inactivity_counter() {
	inactivity_counter++;
}

void Robot::inc_move_counter() {
	move_counter++;
}

int Robot::get_move_counter() {
	return move_counter;
}

void Robot::inc_damage_counter() {
	damage_counter++;
}

int Robot::get_damage_counter() {
	return damage_counter;
}

int Robot::get_overall_damages() {
	return overall_damages;
}

int Robot::get_overall_flags() {
	return overall_flags;
}

int Robot::get_overall_palladium_mined() {
	return overall_palladium_mined;
}

int Robot::get_overall_iridium_mined() {
	return overall_iridium_mined;
}

int Robot::get_overall_platinum_mined() {
	return overall_platinum_mined;
}

void Robot::inc_overall_damages() {
	overall_damages++;
}

void Robot::inc_overall_flags() {
	overall_flags++;
}

void Robot::inc_overall_palladium_mined(int x) {
	overall_palladium_mined += x;
}

void Robot::inc_overall_iridium_mined(int x) {
	overall_iridium_mined += x;
}

void Robot::inc_overall_platinum_mined(int x) {
	overall_platinum_mined += x;
}

int Robot::get_active_robots() {
	return active_robots;
}

void Robot::inc_active_robots() {
	active_robots++;
}

void Robot::dec_active_robots() {
	active_robots--;
}


//ExploringRobot

ExploringRobot::ExploringRobot(int x_coord, int y_coord) : Robot::Robot(x_coord, y_coord) {
	flag_counter = 0;
}


void ExploringRobot::operate(vector< vector<Point*> >& map, vector<Robot*>& rb) {
	printw("ExploringRobot_%d operates in (%d,%d).\n", get_id(), get_x(), get_y());
	double risk = map[get_x()][get_y()]->get_access_risk();
	if (risk > 0.6) {
		map[get_x()][get_y()]->set_danger_flag();
		printw("\tPut flag.\n");
		flag_counter++;
		inc_overall_flags();
	}
}

int ExploringRobot::get_flag_counter() {
	return flag_counter;
}


//AnalysisRobot

AnalysisRobot::AnalysisRobot(int x_coord, int y_coord) : Robot::Robot(x_coord, y_coord), max_load(rand()%50+30) {
	palladium_load = 0;
	iridium_load = 0;
	platinum_load = 0;
	total_amount_mined = 0;
}

void AnalysisRobot::operate(vector< vector<Point*> >& map, vector<Robot*>& rb) {
			
	printw("AnalysisRobot_%d operates in (%d,%d).\n", get_id(), get_x(), get_y());
	int mined;
	
	//extract palladium
	if (map[get_x()][get_y()]->get_palladium() + get_total_load() >= max_load) {
		mined = max_load - get_total_load();
		printw("\t%d palladium mined.\n");
		printw("\tMax load reached. Returning to base.\n");
		return_to_base();
		unload_to_base();
	}
	else {
		mined = map[get_x()][get_y()]->get_palladium();
		printw("\t%d palladium mined.\n");
	}
	palladium_load += mined;
	map[get_x()][get_y()]->update_palladium(mined);
	total_amount_mined += mined;
	inc_overall_palladium_mined(mined);
	
	
	//extract iridium
	if (map[get_x()][get_y()]->get_iridium() + get_total_load() >= max_load) {
		mined = max_load - get_total_load();
		printw("\t%d iridium mined.\n");
		printw("\tMax load reached. Returning to base.\n");
		return_to_base();
		unload_to_base();
	}
	else {
		mined = map[get_x()][get_y()]->get_iridium();
		printw("\t%d iridium mined.\n");
	}
	iridium_load += mined;
	map[get_x()][get_y()]->update_iridium(mined);
	total_amount_mined += mined;
	inc_overall_iridium_mined(mined);
	
	
	//extract platinum
	if (map[get_x()][get_y()]->get_platinum() + get_total_load() >= max_load) {
		mined = max_load - get_total_load();
		printw("\t%d platinum mined.\n");
		printw("\tMax load reached. Returning to base.\n");
		return_to_base();
		unload_to_base();
	}
	else {
		printw("\t%d platinum mined.\n");
		mined = map[get_x()][get_y()]->get_platinum();
	}
	platinum_load += mined;
	map[get_x()][get_y()]->update_platinum(mined);
	total_amount_mined += mined;
	inc_overall_platinum_mined(mined);
	
	//check for failure during mining
	if (((double)(rand()%1000)/1000) * ((double) get_total_load()/get_max_load()) > 0.7) {
		set_damaged_state(true);
		inc_damage_counter();
		inc_overall_damages();
		dec_active_robots();
		printw("\tFailure during mining.\n");
	}
	
}


void AnalysisRobot::unload_to_base() {
	palladium_load = 0;
	iridium_load = 0;
	platinum_load = 0;
}

int AnalysisRobot::get_total_load() {
	return palladium_load + iridium_load + platinum_load;
}
	
int AnalysisRobot::get_max_load() {
	return max_load;
}

void AnalysisRobot::update_total_load_mined(int x) {
	total_amount_mined += x;
}

//RescueRobot

RescueRobot::RescueRobot(int x_coord, int y_coord) : Robot::Robot(x_coord, y_coord) {
	repair_counter = 0;
}

void RescueRobot::operate(vector< vector<Point*> >& map, vector<Robot*>& rb) {
	
	printw("RescueRobot_%d operates in (%d,%d).\n", get_id(), get_x(), get_y());
	
	for (unsigned int i = 0; i < rb.size(); i++) {
		if (rb[i]->get_x() == get_x() && rb[i]->get_y() == get_y() && rb[i]->get_damaged_state() && rb[i]->get_id() != get_id() && !rb[i]->get_permanent_damaged()) {
			rb[i]->set_damaged_state(false);
			printw("\tFixed %d robot.\n", rb[i]->get_id());
			repair_counter++;
			inc_active_robots();
		}
	}
		
}

int RescueRobot::get_repair_counter() {
	return repair_counter;
}
