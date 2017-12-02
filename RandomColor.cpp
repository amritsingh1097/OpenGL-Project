#include "randomcolor.h"
#include "color.h"

RandomColor :: RandomColor()
{
	low=1;
	high=7;
}

void RandomColor :: set_timer_seed()
{
	time_t seed_time;
	struct tm seed_date;
	seed_time = time(0);
	seed_date = *localtime(&seed_time);
	int final_seed;
	final_seed = seed_time + seed_date.tm_mday + (seed_date.tm_mon+1) + (seed_date.tm_year+1900);
	srand((unsigned int)final_seed);
}

unsigned char* RandomColor::draw_random_color()
{
//	set_timer_seed();
	int interval = get_high() - get_low() + 1 ;
	int random_offset = rand() % interval ;
	int random_number = get_low() + random_offset ;
	cout << random_number ;

	switch(random_number)
	{
		case 1:
			return Color::RED;
		case 2:
			return Color::BLUE;
		case 3:
			return Color::BLACK;
		case 4:
			return Color::CYAN;
		case 5:
			return Color::MAGENTA;
		case 6:
			return Color::YELLOW;
		case 7:
			return Color::PURPLE;
	}
	return Color::BLACK;
}

int RandomColor :: get_high()
{
	return high ;
}

int RandomColor :: get_low()
{
	return low ;
}
