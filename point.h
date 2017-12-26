#ifndef POINT_H
#define POINT_H

#include <cstdlib>
#include <ctime>

class Point {
	
	private:
		
		double access_risk;
		int palladium;
		int iridium;
		int platinum;
		
		bool danger_flag;
		
		static double total_risk;
		static int total_palladium;
		static int total_iridium;
		static int total_platinum;

	public:

		Point(); //constructor		
		
		void update_palladium(int mined);
		void update_iridium(int mined);
		void update_platinum(int mined);
		void set_access_risk(double acc_risk);
		void set_danger_flag();
		
		int get_palladium();
		int get_iridium();
		int get_platinum();
		void set_palladium(int amount);
		void set_iridium(int amount);
		void set_platinum(int amount);
		
		double get_access_risk();
		bool get_danger_flag();
		
		static double get_total_risk();
		static int get_total_palladium();
		static int get_total_iridium();
		static int get_total_platinum();
		
};

#endif
