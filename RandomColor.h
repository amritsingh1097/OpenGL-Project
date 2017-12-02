#ifndef RANDOMCOLOR_H
#define RANDOMCOLOR_H

#include <bits/stdc++.h>
using namespace std;

class RandomColor
{
	int low,high;
	public :
		RandomColor();
		void set_timer_seed();
		unsigned char* draw_random_color();
		int get_high();
		int get_low();
};

#endif
