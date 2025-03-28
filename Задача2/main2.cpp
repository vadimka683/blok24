#include<iostream>
#include<iomanip>
#include<vector>
#include<map>
#include<sstream>
#include<fstream>

void push_list(std::map<std::string, std::vector<tm>>& list) {
	std::string answer;
	do {
		std::cout << "Input name and date: Day/Monf/Year ";
		std::getline(std::cin, answer);
		std::stringstream answer_1(answer);
		std::string name;
		tm local;
		time_t T = time(nullptr);
		localtime_s(&local, &T);
		answer_1 >> name >> std::get_time(&local, "%d/%m/%Y");
		if (name == "end" || name == "End") {
			break;
		}
		std::map<std::string, std::vector<tm>>::iterator it = list.find(name);
		if (it != list.end()) {
			it->second.push_back(local);
		}
		else {
			std::vector<tm> temp;
			temp.push_back(local);
			list.insert(std::make_pair(name, temp));
		}
	} while (true);
}

void print_list(std::map<std::string, std::vector<tm>>& list) {
	std::map<std::string, std::vector<tm>>::iterator it = list.begin();
	for (it; it != list.end(); it++) {
		for (int i = 0; i < it->second.size(); i++) {
			std::cout << it->first << " : " << std::put_time(&it->second[i], "%d/%m/%Y") << "\n";
		}
	}
}

void check_birth(std::map<std::string, std::vector<tm>>& list) {
	time_t temp = time(nullptr);
	tm real_time;
	tm temp_1;
	std::vector<std::string> surname_temp_1;
	localtime_s(&real_time, &temp);
	temp_1 = real_time;
	std::map<std::string, std::vector<tm>>::iterator it = list.begin();
	bool chek = false;
	for (it; it != list.end(); it++) {
		for (int i = 0; i < it->second.size(); i++) {
			if (it->second[i].tm_mon == real_time.tm_mon && it->second[i].tm_mday == real_time.tm_mday) {
				std::cout << "Today " << it->first << " Birthday : " << std::put_time(&it->second[i], "%d/%m") << "\n";
				continue;
			}
			if (it->second[i].tm_mon < real_time.tm_mon || 
					(it->second[i].tm_mon == real_time.tm_mon && it->second[i].tm_mday < real_time.tm_mday)) {
				continue;
			}
			else {
				if (chek == false) {
					temp_1 = it->second[i];
					surname_temp_1.push_back(it->first);
					chek = true;
					continue;
				}
				if (it->second[i].tm_mon > temp_1.tm_mon || 
						(it->second[i].tm_mon == temp_1.tm_mon && it->second[i].tm_mday > temp_1.tm_mday)) {
					continue;
				}
				else if (it->second[i].tm_mon == temp_1.tm_mon && it->second[i].tm_mday == temp_1.tm_mday) {
					surname_temp_1.push_back(it->first);
				}
				else {
					surname_temp_1.clear();
					surname_temp_1.push_back(it->first);
					temp_1 = it->second[i];
				}
			}
		}
	}
	for (int i = 0; i < surname_temp_1.size(); i++) {
		std::cout << "Next birthday is " << surname_temp_1[i] << " : " << std::put_time(&temp_1, "%d/%m") << "\n";
	}
}

int main() {
	std::map<std::string, std::vector<tm>> list;
	push_list(list);
	print_list(list);
	check_birth(list);
}