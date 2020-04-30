#pragma once
#include <vector>
#include <string>
#include <ostream>
#include <iostream>
#include <fstream>
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
class RepositoryInterface
{
private:
	virtual bool exists(const Entitate& apartment)const = 0;
public:
	virtual ~RepositoryInterface() {};
	virtual void add(const Entitate& entitate) = 0;

	virtual void update(const Entitate& entitate) = 0;

	virtual void remove(const Entitate& entitate) = 0;

	virtual const Entitate& find(int id) const = 0;

	virtual const vector<Entitate>& getAll()const noexcept = 0;
};


template <class Entitate>
class Repository: RepositoryInterface<Entitate>
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

template <class Entitate>
class FileRepository : public Repository<Entitate> {
private:
	string __fileName;
	void __loadData() {
		ifstream file_read(__fileName);
		/*if (!file_read.is_open()) {
			throw RepositoryException("Ërror: Unable to open file: " + __fileName);
		}*/
		while (!file_read.eof()) {
			Entitate entitate{};

			file_read >>entitate;
			if (entitate.getId() > 0) {
				Repository<Entitate>::add(entitate);
			}
		}
		file_read.close();
	}
	void __saveData() {
		ofstream file_write(__fileName);
		/*if (!file_write.is_open()) {
			throw RepositoryException("Ërror: Unable to open file: " + __fileName);
		}*/
		for (const Entitate& entitate : Repository<Entitate>::getAll()) {
			file_write << entitate<<"\n";
		}
		file_write.close();
	}
public:
	FileRepository(string fileName) : Repository<Entitate>(), __fileName{ fileName } {
		__loadData();
	};

	void add(const Entitate& entitate) override{
		Repository<Entitate>::add(entitate);
		__saveData();
	}

	void update(const Entitate& entitate)override  {
		Repository<Entitate>::update(entitate);
		__saveData();
	}

	void remove(const Entitate& entitate)override {
		Repository<Entitate>::remove(entitate);
		__saveData();
	}
};
