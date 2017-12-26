#include "sim.h"

using namespace std;

int X_size = 50;
int Y_size = 50;
int init_num_robots = 50;
typedef std::vector< std::vector<Point*> > two_dim_vector;
two_dim_vector map(X_size, std::vector<Point*>(Y_size));
vector<Robot*> rb;

//base coordinates and other data
const int base_x = 0;
const int base_y = 0;
int base_palladium = 0;
int base_iridium = 0;
int base_platinum = 0;
const int base_palladium_target = 500;
const int base_iridium_target = 500;
const int base_platinum_target = 500;

double message_time = 1;
double iteration_time = 1;

void edit_menu() {
	printw("1) Create Robot, 2) Edit Robot, 3) Edit Map Point, 4) Go back\n");
	int option;
	cin >> option;
	printw("%d\n", option);
	switch (option) {
		case 1: 
			printw("Choose type:\n1) Exploring, 2) Analysis, 3) Rescue\n");			
			cin >> option;
			if (option == 1) {
				rb.push_back(new ExploringRobot(rand()%X_size, rand()%Y_size));
			}
			else if (option == 2) {				
				rb.push_back(new AnalysisRobot(rand()%X_size, rand()%Y_size));
			}
			else {
				rb.push_back(new RescueRobot(rand()%X_size, rand()%Y_size));
			}
			printw("New Robot has been created!\n");
			break;
		case 2:
			printw("Choose Robot to edit: (0-%d)\n", rb.size()-1);
			int rb_num;
			cin >> rb_num;
			printw("Robot_%d is damaged: %d\n", rb[rb_num]->get_id(), rb[rb_num]->get_damaged_state());
			if (rb[rb_num]->get_damaged_state() && !rb[rb_num]->get_permanent_damaged()) {
				printw("Do you want to fix robot? [y/n]\n");
				char fix;
				cin >> fix;
				if (fix == 'y') {
					rb[rb_num]->set_damaged_state(false);
					printw("Robot was fixed!\n");
					Robot::inc_active_robots();
				}
			}
			else if (!rb[rb_num]->get_damaged_state()) {
				printw("Do you want to damage robot? [y/n]\n");
				char damage;
				cin >> damage;
				if (damage == 'y') {
					rb[rb_num]->set_damaged_state(true);
					printw("Robot was damaged!\n");
					Robot::dec_active_robots();
					Robot::inc_overall_damages();
				}
			}
			else {
				printw("Robot is permanent damaged and has been removed from simulation.\n");
			}
			break;					
		case 3:
			printw("Choose x: (0-%d)\n", X_size-1);
			int x;
			cin >> x;
			printw("Choose y: (0-%d)\n", Y_size-1);
			int y;
			cin >> y;
			printw("(%d,%d):\nAccess risk: %f\nPalladium: %d\n", x, y, map[x][y]->get_access_risk(), map[x][y]->get_palladium());
			printw("Iridium: %d\nPlatinum: %d\n", map[x][y]->get_iridium(), map[x][y]->get_platinum());
			printw("Change: 1) access risk, 2) palladium, 3) iridium, 4) platinum\n");
			cin >> option;
			if (option == 1) {
				printw("Enter new access risk: (0-0.9)\n");
				double acc_risk;
				cin >> acc_risk;
				map[x][y]->set_access_risk(acc_risk);
				printw("Access risk was changed to %f.\n", map[x][y]->get_access_risk());
			}
			else if (option == 2) {
				printw("Enter new palladium amount:\n");
				int amount;
				cin >> amount;
				map[x][y]->set_palladium(amount);
			}
			else if (option == 3) {
				printw("Enter new iridium amount:\n");
				int amount;
				cin >> amount;
				map[x][y]->set_iridium(amount);
			}
			else if (option == 4) {
				printw("Enter new platinum amount:\n");
				int amount;
				cin >> amount;
				map[x][y]->set_platinum(amount);
			}	
			break;
		case 4:
			return;			
	}
	edit_menu();
}

void stats_menu() {	
	printw("Show: \nRobots: 1) Total Failures, 2) Total Flags, 3) Total Load Mined, 4) Active Robots\n");
	printw("Map: 5) Average access risk, 6) Total Palladium, 7) Total Iridium, 8) Total Platinum\n");
	printw("9) Return to global menu\n");
	int option;
	cin >> option;
	printw("%d\n", option);
	switch (option) {
		case 1:
			printw("%d total failures.\n", Robot::get_overall_damages());
			break;
		case 2:
			printw("%d total flags.\n", Robot::get_overall_flags());
			break;
		case 3:
			printw("%d total load mined.\n", Robot::get_overall_palladium_mined() + Robot::get_overall_iridium_mined() + Robot::get_overall_platinum_mined());
			break;
		case 4:
			printw("%d active robots.\n", Robot::get_active_robots());
			break;
		case 5:
			printw("%f average access risk.\n", Point::get_total_risk()/(X_size+Y_size));
			break;
		case 6:
			printw("%d total palladium.\n", Point::get_total_palladium());
			break;
		case 7:
			printw("%d total iridium.\n", Point::get_total_iridium());
			break;
		case 8:
			printw("%d total platinum.\n", Point::get_total_platinum());
			break;
		case 9:
			return;
		default:
			break;
	}
	stats_menu();
}

void options_menu() {
	printw("Options: 1) Show Statistics,  2) Change World Parameters, 3) View Robot, 4) View Map\n");
	printw("5) Change message time 6) Change iteration time 7) Continue 8) Quit\n");
	int option;
	cin >> option;
	printw("%d\n", option);
	if (option == 1) {
		stats_menu();
		options_menu();	
	}
	else if (option == 2) {
		edit_menu();
		options_menu();
	}
	else if (option == 3) {
		printw("%d Robots. Choose number (0-%d) to view:\n", rb.size(), rb.size()-1);
		int rb_num;
		cin >> rb_num;
		printw("Robot_%d:\n", rb[rb_num]->get_id());
		printw("%d total damages\n", rb[rb_num]->get_damage_counter());
		printw("%d total moves\n", rb[rb_num]->get_move_counter());
		printw("Damaged state: %d\n", rb[rb_num]->get_damaged_state());
		printw("Permanent Damaged: %d\n", rb[rb_num]->get_permanent_damaged());
		printw("Current Position: (%d,%d)\n", rb[rb_num]->get_x(), rb[rb_num]->get_y());
		printw("\n");
		options_menu();
	}
	else if (option == 4) {
		printw("Choose x: (0-%d)\n", X_size-1);
		int x;
		cin >> x;
		printw("Choose y: (0-%d)\n", Y_size-1);
		int y;
		cin >> y;
		printw("(%d,%d):\nAccess risk: %f\nPalladium: %d\n", x, y, map[x][y]->get_access_risk(), map[x][y]->get_palladium());
		printw("Iridium: %d\nPlatinum: %d\n", map[x][y]->get_iridium(), map[x][y]->get_platinum());
		options_menu();		
	}		
	else if (option == 5) {
		printw("Enter new message time:");
		cin >> message_time;
		printw("\n");
		options_menu();
	}
	else if (option == 6) {
		printw("Enter new iteration time:");
		cin >> iteration_time;
		printw("\n");
		options_menu();
	}
	else if (option == 7) {
		printw("Continuing...\n");
		sleep(1);
		return;
	}
	else if (option == 8) {
		printw("Quitting...\n");
		sleep(1);
		endwin();
		exit(0);
	}
	
}

void check_interrupt() {
	char key;
	if ((key = getch()) == 'q') {
		printw("Quitting...");
		sleep(1);
		endwin();
		exit(0);
	}
	else if (key == 'p') {
		printw("Pausing...\n");
		options_menu();
	}
}


int main(int argc, char** argv) {
		
	if (argc != 4) {
		cout << "Wrong number of arguments. Using default values...\n" << endl;
		sleep(1);
	}		
	else if (argc == 4) {
		X_size = atoi(argv[1]);
		Y_size = atoi(argv[2]);
		init_num_robots = atoi(argv[3]);
	}
		
		
	//curses initialization
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, true);
	nodelay(stdscr, true);
	scrollok(stdscr, true);
	immedok(stdscr, true);	
		
	//random seed
	srand(time(NULL));
	
	//create point objects	
	for (int i = 0; i < X_size; i++) {
		for (int j = 0; j < Y_size; j++) {
			map[i][j] = new Point();
		}
	}	
	
	//create robots	
	for (int i = 0; i < init_num_robots; i++) {
		int type = rand()%5;
		if (type == 0) {
			rb.push_back(new ExploringRobot(rand()%X_size, rand()%Y_size));
		}
		else if (type == 1 || type == 2 || type == 3) {
			rb.push_back(new AnalysisRobot(rand()%X_size, rand()%Y_size));
		}
		else {
			rb.push_back(new RescueRobot(rand()%X_size, rand()%Y_size));
		}
	}
	
	int iteration = 0;	
	while(1) {		
		check_interrupt();
		iteration++;
		printw("---------------------Iteration %d--------------------------\n", iteration);
		sleep(iteration_time);			
		//move and operate robots
		for (vector<Robot*>::size_type i = 0; i < rb.size(); i++) {
			check_interrupt();
			if (!rb[i]->get_permanent_damaged()) {
				rb[i]->move_and_op(map, rb);
				sleep(message_time);
				if (Robot::get_overall_palladium_mined() >= base_palladium_target && Robot::get_overall_iridium_mined() >= base_iridium_target && Robot::get_overall_platinum_mined() >= base_platinum_target) {
					printw("Successful operation! Press any key to quit...\n");
					cin.ignore();
					endwin();
					exit(0);
				}
				if (Robot::get_active_robots() == 0) {
					printw("All robots are damaged! Press any key to quit...\n");
					cin.ignore();
					endwin();
					exit(1);
				}
			}
		}		
	}
			
}
