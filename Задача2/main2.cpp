#include<iostream>
#include<iomanip>
#include<vector>
#include<map>
#include<sstream>

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

int main() {
	std::map<std::string, std::vector<tm>> list;
	push_list(list);
	print_list(list);
}