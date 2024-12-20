#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <chrono>
#include <string>



extern "C" {

	void get_date() {
		setlocale(LC_ALL, "Russian");
		time_t rawtime;
		struct tm* timeinfo;

		time(&rawtime);
		timeinfo = localtime(&rawtime);

		char buffer[80];
		strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeinfo);
		std::cout << "Текущая дата: " << buffer << std::endl;
	}

	void get_time() {

		auto start = std::chrono::system_clock::now();
		// Some computation here
		auto end = std::chrono::system_clock::now();

		std::chrono::duration<double> elapsed_seconds = end - start;
		std::time_t end_time = std::chrono::system_clock::to_time_t(end);

		std::cout << "Сейчас: " << std::ctime(&end_time)<< std::endl;
	}
	void Out_int(int num) {
		setlocale(LC_ALL, "Russian");
		std::cout << "Вывод целочисленного значения: ";
		std::cout << num << std::endl;
	}
	void Out_char(char chr) {
		setlocale(LC_ALL, "Russian");
		std::cout << "Вывод символьного значения: ";
		std::cout << chr << std::endl;
	}
	void Out_bool(bool logic) {
		setlocale(LC_ALL, "Russian");
		std::cout << "Вывод логического значения: ";
		std::cout << logic << std::endl;
	}

}

