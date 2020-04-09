#pragma once
#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <iterator>
#include <sstream>
#include "RezervareCamera.h"
#include "Repository.h"
#include "Service.h"


using namespace std;


class ConsoleException {
	string msg;
public:
	ConsoleException(string m) :msg{ m } {}
	string getMsg()const {
		return this->msg;
	}
	friend ostream& operator<<(ostream& out, const ConsoleException& ex) {
		out << ex.msg << "\n";
		return out;
	}
};

class Console
{

public:
	Console() = delete;
	Console(Service& service)noexcept : service{ service } {}
	Console(const Console& ot) = delete;
	~Console() {};

	void run() {
		string command;
		printMenu();
		while (true) {
			command = readCommand();
			istringstream iss(command);
			vector<string> params{ istream_iterator<string>{iss}, istream_iterator<string>{} };
			try {
				if (params.at(0) == "exit") {
					return;
				}
				else if (params.at(0) == "print_rezervari") {
					printRezervari(params);
				}
				else if (params.at(0) == "add_rezervare") {
					addRezervare(params);
				}
				else if (params.at(0) == "update_rezervare") {
					updateRezervare(params);
				}
				else if (params.at(0) == "remove_rezervare") {
					removeRezervare(params);
				}
				else if (params.at(0) == "find_rezervare") {
					findRezervare(params);
				}
				else if (params.at(0) == "statistici") {
					printStatistici(params);
				}
			}
			catch (const RepositoryException& exc) {
				cout << exc << "\n";
			}
			catch (const ConsoleException& exc) {
				cout << exc << "\n";
			}
		}
	}
private:
	Service& service;

	const string readCommand() {
		cout << "> ";
		string command;
		getline(cin, command);
		return command;
	}

	void printMenu() {
		//system("cls");
		cout << "Available commands: \n";
		cout << "\t 1. print_rezervari \n";
		cout << "\t 2. add_rezervare \n";
		cout << "\t 3. update_rezervare \n";
		cout << "\t 4. remove_rezervare \n";
		cout << "\t 5. find_rezervare \n";
		cout << "\t 6. statistici \n";
		cout << "\t 7. exit\n\n\n";
	}

	void printRezervari(vector<string> params) {
		if (params.size() != 1) {
			throw ConsoleException{ "Invalid no of parameters. This command takes no parameters.\n" };
		}
		for (const RezervareCamera& item : service.getAll()) {
			cout << "\t" << item << "\n";
		}
		cout << "\n";
	}

	void addRezervare(vector<string> params) {
		if (params.size() != 5) {
			throw ConsoleException{ "Invalid no of parameters.'.\n" };
		}
		int id = stoi(params.at(1));
		const string numar = params.at(2);
		const string tip = params.at(3);
		const bool eliberata = stoi(params.at(4));
		service.addRezervareCamera(id, numar, tip, eliberata);
		cout << "\n";
	}

	void updateRezervare(vector<string> params) {
		if (params.size() != 5) {
			throw ConsoleException{ "Invalid no of parameters.\n" };
		}
		int id = stoi(params.at(1));
		const string numar = params.at(2);
		const string tip = params.at(3);
		const bool eliberata = stoi(params.at(4));
		service.updateRezervareCamera(id, numar, tip, eliberata);
		cout << "\n";
	}

	void removeRezervare(vector<string> params) {
		if (params.size() != 2) {
			throw ConsoleException{ "Invalid no of parameters'.\n" };
		}
		int id = stoi(params.at(1));
		service.removeRezervareCamera(id);
		cout << "\n";
	}

	void findRezervare(vector<string> params) {
		if (params.size() != 2) {
			throw ConsoleException{ "Invalid no of parameters.\n" };
		}
		int id = stoi(params.at(1));
		const RezervareCamera& RezervareCamera = service.findRezervareCamera(id);
		cout << RezervareCamera << "\n";
		cout << "\n";
	}

	void printStatistici(vector<string> params) {
		if (params.size() != 1) {
			throw ConsoleException{ "Invalid no of parameters.\n" };
		}
		vector<Statistica> result = service.computePercentage();
		for (int i = 0; i < result.size(); ++i) {
			cout << result[i].getTip() << " " << result[i].getProcent() << "%\n";
		}
	}
};
