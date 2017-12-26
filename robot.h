#ifndef ROBOT_H
#define ROBOT_H

#include <cstdlib>
#include <ncurses.h>
#include "point.h"
#include <vector>
#include <iostream>

class Robot;

extern int X_size;
extern int Y_size;
extern const int base_x;
extern const int base_y;

class Robot {
	
	private:
		
		//static members
		static int overall_damages;
		static int overall_flags;
		static int overall_palladium_mined;
		static int overall_iridium_mined;
		static int overall_platinum_mined;
		static int active_robots;
		static int id_counter;
		
		//characteristics vars
		const int id;
		const int speed;
		const double access_ability;
		
		//coordinates
		int x;
		int y;
						
		//motion vars		
		int step_counter;
		char direction;
		
		//damage-related vars
		bool damaged_state;		
		int inactivity_counter;
		bool permanent_damaged;
		
		//stats vars
		int move_counter;
		int damage_counter;
		
	public:
		
		Robot(int x_coord, int y_coord);
		void move_and_op(std::vector< std::vector<Point*> >& map, std::vector<Robot*>& rb);
		virtual void operate(std::vector< std::vector<Point*> >& map, std::vector<Robot*>& rb) = 0;
		
		int get_speed();
		int get_step_counter();
		bool get_damaged_state();
		void set_damaged_state(bool d);
		bool get_permanent_damaged();
		int get_x();
		int get_y();
		void update_coord(int x_change, int y_change);
		void return_to_base();
		int get_id();
		
		int get_inactivity_counter();
		void inc_inactivity_counter();
		int get_move_counter();
		void inc_move_counter();
		int get_damage_counter(); 
		void inc_damage_counter();
		
		
		static int get_overall_damages();
		static int get_overall_flags();
		static int get_overall_palladium_mined();
		static int get_overall_iridium_mined();
		static int get_overall_platinum_mined();
		static int get_active_robots();
		
		static void inc_active_robots();
		static void dec_active_robots();
		static void inc_overall_damages();
		static void inc_overall_flags();
		static void inc_overall_palladium_mined(int x);
		static void inc_overall_iridium_mined(int x);
		static void inc_overall_platinum_mined(int x);
			
};

class ExploringRobot : public Robot {
	
	private:
	
		int flag_counter;
	
	public:
		
		ExploringRobot(int x_coord, int y_coord);
		void operate(std::vector< std::vector<Point*> >& map, std::vector<Robot*>& rb);
		
		int get_flag_counter();
	
};

class AnalysisRobot : public Robot {
	
	private:
	
		const int max_load;
		int palladium_load;
		int iridium_load;
		int platinum_load;
		int total_amount_mined;
	
	public:
	
		AnalysisRobot(int x_coord, int y_coord);
		void operate(std::vector< std::vector<Point*> >& map, std::vector<Robot*>& rb);
		
		void update_total_load_mined(int x);
		void unload_to_base();
		
		int get_max_load();
		int get_palladium_load();
		int get_iridium_load();
		int get_platinum_load();
		int get_total_load();
	
};

class RescueRobot : public Robot {
	
	private:
	
		int repair_counter;
	
	public:
		
		RescueRobot(int x_coord, int y_coord);
		void operate(std::vector< std::vector<Point*> >& map, std::vector<Robot*>& rb);
		
		int get_repair_counter();
	
};

#endif
