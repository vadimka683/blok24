#include<iostream>
#include<iomanip>

int main() {
	tm timer;
	std::cout << "Input how much time to record MIN/SEC: ";
	std::cin >> std::get_time(&timer, "%M/%S");
	time_t time_start = time(nullptr);
	time_t time_end = time_start + (timer.tm_min * 60) + timer.tm_sec;
	time_t real_time = time_start;
	time_t remainder = (timer.tm_min * 60) + timer.tm_sec;
	while (real_time != time_end) {
		real_time = time(nullptr);
		if (time_end - real_time == remainder - 1) {
			if ((time_end - real_time) / 60 != 0) {
				std::cout << (time_end - real_time) / 60 << " min " << (time_end - real_time) % 60 << " sec\n";
			}
			else {
				std::cout << (time_end - real_time) % 60 << " sec\n";
			}
			remainder--;
		}
	}
	std::cout << "DING! DING! DING!";
}