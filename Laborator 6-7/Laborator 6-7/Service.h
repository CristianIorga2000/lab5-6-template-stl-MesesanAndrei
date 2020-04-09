#pragma once
#pragma once
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include "RezervareCamera.h"
#include "Repository.h"
#include <map>

using namespace std;


class Statistica {
private:
	string tip;
	float procent;
public:
	Statistica(string tip, float procent) : tip{ tip }, procent{ procent }{};
	Statistica(const Statistica &t) : tip{ t.tip }, procent{ t.procent }{};

	string getTip() {
		return tip;
	}

	float getProcent() {
		return procent;
	}
};

class Service
{
private:
	Repository<RezervareCamera>& repository;

public:
	Service() = delete;
	Service(Repository<RezervareCamera>& repository)noexcept : repository{ repository } {};
	~Service() {};

	void addRezervareCamera(int id, const string& numar, const string& tip, const bool eliberata) {
		/*
			Adauga o rezervare.
			in: id - int
				numar - const string
				tip - const string
				eliberata - const bool
		*/
		RezervareCamera newRezervareCamera{ id, numar, tip, eliberata };
		repository.add(newRezervareCamera);
	}

	void removeRezervareCamera(int id) {
		/*
			Sterge o rezervare dupa id.
			in: id - int
		*/
		RezervareCamera oldRezervareCamera{ id };
		repository.remove(oldRezervareCamera);
	}

	void updateRezervareCamera(int id, const string& numar, const string& tip, const bool eliberata) {
		/*
			Modifica o rezervare.
			in: id - int
				numar - const string
				tip - const string
				eliberata - const bool
		*/
		RezervareCamera newRezervareCamera{ id, numar, tip, eliberata };
		repository.update(newRezervareCamera);
	}

	const RezervareCamera& findRezervareCamera(int id) const {
		/*
			Returneaza o rezervare cu un id dat.
			in: id - int
			out: rc - RezervareCamera&
		*/
		const RezervareCamera& rc = repository.find(id);
		return rc;
	}

	const vector<RezervareCamera>& getAll() const noexcept {
		/*
			Returneaza toate rezervarile.
		*/
		return repository.getAll();
	}

	vector<Statistica> computePercentage() {
		vector<Statistica> result{};
		vector<RezervareCamera> rezervari = getAll();
		vector<string> tipuri_unice{};

		//Construim vectorul tipuri_unice unde cheia este tipul, iar valoarea este de tip true sau false.

		for (int i = 0; i < rezervari.size(); ++i) {
			bool contine = false;
			string tip = rezervari[i].getTip();
			for (int j = 0; j < tipuri_unice.size(); ++j) {
				if (tipuri_unice[j].compare(tip) == 0) {
					contine = true;
					break;
				}
			}
			if (contine == false) {
				tipuri_unice.push_back(tip);
			}
		}

		//Calculam procentul de camere libere pentru fiecare tip din vectorul tipuri_unice, si adaugam o statistica cu parametrii tip si procent in vectorul result.

		for (int i = 0; i < tipuri_unice.size(); ++i) {
			string tip = tipuri_unice[i];
			int nr_rezervari = count_if(rezervari.begin(), rezervari.end(), [tip](RezervareCamera& rc) {return rc.getTip().compare(tip) == 0; });
			int nr_rezervari_eliberate = count_if(rezervari.begin(), rezervari.end(), [tip](RezervareCamera& rc) {return rc.getTip().compare(tip) == 0 && rc.getEliberata() == true; });
			float procent = nr_rezervari_eliberate * 100 / nr_rezervari;
			result.push_back(Statistica{ tip, procent });
		}
		
		//Ordonam crescator vectorul result in functie de procentajul camerelor libere pentru fiecare tip de camera.

		sort(result.begin(), result.end(), [](Statistica& st1, Statistica& st2) {
			return st1.getProcent() < st2.getProcent();
		});
		return result;
	}
};