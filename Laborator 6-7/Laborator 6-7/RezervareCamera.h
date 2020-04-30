#pragma once
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

class RezervareCamera {
private:
	int id;
	string numar;
	string tip;
	bool eliberata;
public:
	RezervareCamera() = default;
	RezervareCamera(int id, const string& numar, const string& tip, const bool eliberata) : id{ id }, numar{ numar }, tip{ tip }, eliberata{eliberata}{};
	RezervareCamera(const RezervareCamera& other) : id{ other.id }, numar{ other.numar }, tip{ other.tip }, eliberata{ other.eliberata }{};
	RezervareCamera(int id) : id{ id }, numar{ "" }, tip{ "" }, eliberata{ false }{};
	~RezervareCamera() {};

	const int getId() const noexcept {
		//Returneaza id-ul.
		return id;
	}

	const string getNumar() const noexcept {
		//Returneaza numarul.
		return numar;
	}

	const string getTip() const noexcept {
		//Retuneaza tipul.
		return tip;
	}

	const bool getEliberata() const noexcept {
		//Retuneaza true, sau false
		return eliberata;
	}

	void setId(int newId) noexcept {
		/*
			Seteaza un nou id.
			in: newId - int
		*/
		this->id = newId;
	}

	void setNumar(const string& value) {
		/*
			Seteaza un nou numar.
			in: value - string
		*/
		this->numar = value;
	}

	void setTip(const string& tip) {
		/*
			Seteaza un nou tip.
			in: tip - string
		*/
		this->tip = tip;
	}

	void setEliberata(const bool& value) {
		/*
			Seteaza o noua valoare pentru eliberata.
			in: value - bool
		*/
		this->eliberata = value;
	}

	bool operator==(const RezervareCamera& rezervare) const noexcept {
		/*
			Operatorul de egalitate.
			in: rezervare - RezervareCamera
			out: true daca este adevarat, false daca nu
		*/
		return this->getId() == rezervare.getId();
	}

	bool operator!=(const RezervareCamera& rezervare) const noexcept {
		/*
			Operatorul de inegalitate.
			in: rezervare - RezervareCamera
			out: true daca este adevarat, false daca nu
		*/
		return this->getId() != rezervare.getId();
	}

	RezervareCamera& operator=(const RezervareCamera& other) {
		/*
			Operator de atribuire.
			in: other - RezervareCamera
			out: continutul indicat de this
		*/
		setId(other.getId());
		setNumar(other.getNumar());
		setTip(other.getTip());
		setEliberata(other.getEliberata());
		return *this;
	}

	friend ostream& operator<<(ostream& out, const RezervareCamera& rezervare) {
		out << rezervare.getId() << " " << rezervare.getNumar() << " " << rezervare.getTip() << " " << rezervare.getEliberata() << " ";
		return out;
	}
	friend istream& operator>>(istream& in_stream, RezervareCamera& rez) {
		int id;
		string numar;
		string tip;
		bool eliberata;
		if (in_stream.eof()) {
			return in_stream;
		}
		in_stream >> id;
		rez.setId(id);
		if (in_stream.eof()) {
			return in_stream;
		}
		in_stream >> numar; 
		rez.setNumar(numar);
		if (in_stream.eof()) {
			return in_stream;
		}
		in_stream >> tip; 
		rez.setTip(tip);
		if (in_stream.eof()) {
			return in_stream;
		}
		in_stream >> eliberata;
		rez.setEliberata(eliberata);
		if (in_stream.eof()) {
			return in_stream;
		}
		return in_stream;
	}
};
