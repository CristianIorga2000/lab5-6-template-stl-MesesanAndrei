#pragma once
#include <vector>
#include <string>
#include <ostream>
#include <algorithm>
#include "RezervareCamera.h"

using namespace std;

//Clasa pentru exceptii
class RepositoryException {
	string msg;
public:
	RepositoryException(string m) :msg{ m } {}
	string getMsg()const {
		return this->msg;
	}
	friend ostream& operator<<(ostream& out, const RepositoryException& ex) {
		out << ex.msg << "\n";
		return out;
	}
};



template <class Entitate>
class Repository
{
private:
	vector<Entitate> entitates;
	bool exists(const Entitate& entitate)const {
		/*
			Verifica daca esxista deja entitatea in repository.
			in: entitate - Entitate
			out: true daca exista entitatea, false altfel
		*/
		try {
			find(entitate.getId());
			return true;
		}
		catch (const RepositoryException&) { return false; }
	}
public:
	Repository() = default;
	~Repository() {};

	void add(const Entitate& entitate) {
		/*
			Verifica daca exista entitatea, daca exista arunca o exceptie, altfel adauga entitatea.
			in: entitate - Entitate
		*/
		if (exists(entitate)) {
			throw RepositoryException("The entitate already exists.");
		}
		entitates.push_back(entitate);
	}

	void update(const Entitate& entitate)  {
		/*
			Verifica daca exista entitatea, daca exista o modifica, altfel arunca o exceptie.
			in: entitate - Entitate
		*/
		if (exists(entitate)) {
			for (Entitate& item : entitates) {
				if (item == entitate) {
					item = entitate;
				}
			}
			return;
		}
		throw RepositoryException("The entitate does not exist ");
	}

	void remove(const Entitate& entitate)  {
		/*
			Verifica daca exista entitatea, daca nu exista arunca o exceptie, altfel sterge entitatea.
			in: entitate - Entitate
		*/
		if (exists(entitate) == false) {
			throw RepositoryException("The entitate does not exist ");
		}
		entitates.erase(std::remove(entitates.begin(), entitates.end(), entitate), entitates.end());
	}

	const Entitate& find(int id) const  {
		/*
			Cauta o entitate dupa id.
			in: id - int
		*/
		auto result = find_if(getAll().begin(), getAll().end(), [&id](const Entitate& entitate)noexcept {
			return entitate.getId() == id;
			});
		if (result == end(getAll())) {
			throw RepositoryException("The entitate does not exist " + id);
		}
		return *result;
	}

	const vector<Entitate>& getAll()const noexcept {
		//Returneaza vectorul de entitati.
		return entitates;
	}
};

