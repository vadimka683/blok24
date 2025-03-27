#include<iostream>
#include<ctime>
#include<map>
#include<fstream>

struct Task
{
	std::string name;
	std::time_t time_start = 0;
	std::time_t time_finish = 0;
	time_t task_time_h = 0;
	time_t task_time_m = 0;
	time_t task_time_s = 0;
};

void end_task(std::map<int, Task>& task_history, int& count) {
	std::map<int, Task>::iterator it = task_history.find(count);
	if (it->second.time_finish != 0) {
		std::cout << "Task closed, imposible comand\n";
		return;
	}
	it->second.time_finish = time(nullptr);
	it->second.task_time_h = (it->second.time_finish - it->second.time_start) / 3600;
	it->second.task_time_m = ((it->second.time_finish - it->second.time_start) % 3600) / 60;
	it->second.task_time_s = ((it->second.time_finish - it->second.time_start) % 3600) % 60;
}

void begin_task(std::map<int, Task>& task_history, int& count) {
	if (count != 0 && task_history.find(count)->second.time_finish == 0) {
		end_task(task_history, count);
	}
	count++;
	Task task_temp;
	std::cout << "Input task name: ";
	std::cin >> task_temp.name;
	task_temp.time_start = time(nullptr);
	task_history.insert(std::make_pair(count, task_temp));
}

void print_status(std::map<int, Task>& task_history, int& count) {
	for (std::map<int, Task>::iterator it = task_history.begin(); it != task_history.end(); it++) {
		if (it == task_history.find(count)) {
			if (it->second.time_finish == 0) {
				return;
			}
		}
		char buffer[26];
		tm local;
		std::cout << it->first << ". " << it->second.name << ":\n";
		localtime_s(&local, &it->second.time_start);
		asctime_s(buffer, sizeof(buffer), &local);
		std::cout << "Date start task: " << buffer << "\n";
		localtime_s(&local, &it->second.time_finish);
		asctime_s(buffer, sizeof(buffer), &local);
		std::cout << "Date finish task: " << buffer << "\n";
		std::cout << "Task time: " << it->second.task_time_h << " h. " << it->second.task_time_m << " m. " << it->second.task_time_s << " s.\n";
	}
}

void save_history(std::map<int, Task>& task_history) {
	std::ofstream save("Task history.BIN", std::ios::binary);
	for (std::map<int, Task>::iterator it = task_history.begin(); it != task_history.end(); it++) {
		size_t name_leght = it->second.name.length();
		save.write(reinterpret_cast<char*>(&name_leght), sizeof(name_leght));
		save.write(it->second.name.data(), name_leght);
		save.write(reinterpret_cast<char*>(&it->second.task_time_h), sizeof(it->second.task_time_h));
		save.write(reinterpret_cast<char*>(&it->second.task_time_m), sizeof(it->second.task_time_m));
		save.write(reinterpret_cast<char*>(&it->second.task_time_s), sizeof(it->second.task_time_s));
		save.write(reinterpret_cast<char*>(&it->second.time_finish), sizeof(it->second.time_finish));
		save.write(reinterpret_cast<char*>(&it->second.time_start), sizeof(it->second.time_start));
		int i = it->first;
		save.write(reinterpret_cast<char*>(&i), sizeof(i));
	}
}

void load_history(std::map<int, Task>& task_history) {
	std::ifstream load("Task history.BIN", std::ios::binary);
	while (true) {
		size_t name_leght;
		Task task_temp;
		if (!load.read(reinterpret_cast<char*>(&name_leght), sizeof(name_leght))) {
			break;
		}
		task_temp.name.resize(name_leght);
		if (!load.read(&task_temp.name[0], name_leght)) {
			break;
		}
		load.read(reinterpret_cast<char*>(&task_temp.task_time_h), sizeof(task_temp.task_time_h));
		load.read(reinterpret_cast<char*>(&task_temp.task_time_m), sizeof(task_temp.task_time_m));
		load.read(reinterpret_cast<char*>(&task_temp.task_time_s), sizeof(task_temp.task_time_s));
		load.read(reinterpret_cast<char*>(&task_temp.time_finish), sizeof(task_temp.time_finish));
		load.read(reinterpret_cast<char*>(&task_temp.time_start), sizeof(task_temp.time_start));
		int count;
		load.read(reinterpret_cast<char*>(&count), sizeof(count));
		task_history.insert(std::make_pair(count, task_temp));
	}
}

int main() {
	std::map<int, Task> task_history;
	std::string answer;
	int counter = 0;
	do {
		std::cout << "Input comand: Exit or Begin or End or Status or Load or Save: ";
		std::cin >> answer;
		if (answer == "Exit") {
			return 0;
		}
		else if (answer == "Begin") {
			begin_task(task_history, counter);
		}
		else if (answer == "End") {
			end_task(task_history, counter);
		}
		else if (answer == "Status") {
			print_status(task_history, counter);
		}
		else if (answer == "Save") {
			save_history(task_history);
		}
		else if (answer == "Load") {
			load_history(task_history);
		}
	} while (true);
}