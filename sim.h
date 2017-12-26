#ifndef SIM_H
#define SIM_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include <vector>

#include "point.h"
#include "robot.h"

void edit_menu();
void stats_menu();
void options_menu();
void check_interrupt();

#endif
