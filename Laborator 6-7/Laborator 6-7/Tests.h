#pragma once
#include "RezervareCamera.h"
#include "Repository.h"
#include "Service.h"
#include <assert.h>
#include <iostream>

void testDomain(){
	RezervareCamera r1{ 1, "nr1", "tip1", false };
	RezervareCamera r2{ 2, "nr2", "tip1", true };
	RezervareCamera r3{ 3, "nr3", "tip2", true };
	RezervareCamera r4{ 4 };
	RezervareCamera r5{r1 };
	assert(r1 == r5);
	assert(r1 != r2);
	r2 = r1;
	assert(r2 == r1);

	assert(r3.getId() == 3);
	assert(r3.getNumar() == "nr3");
	assert(r3.getTip() == "tip2");
	assert(r3.getEliberata() == true);

	r3.setId(2);
	r3.setNumar("a");
	r3.setTip("a");
	r3.setEliberata(false);
	assert(r3.getId() == 2);
	assert(r3.getNumar() == "a");
	assert(r3.getTip() == "a");
	assert(r3.getEliberata() == false);

	stringstream ss;
	ss << r3;
	string s = ss.str();
	//cout << s;
	assert(s == "2 a a 0 ");

}

void testRepository(){
	//Repository<RezervareCamera> repo{};
	FileRepository<RezervareCamera> repo("C:\\Users\\Andrei\\source\\repos\\lab5-6-template-stl-MesesanAndrei\\Laborator 6-7\\Laborator 6-7\\date_text.txt");


	RezervareCamera r1{ 1, "nr1", "tip1", false };
	RezervareCamera r2{ 2, "nr2", "tip1", true };
	RezervareCamera r3{ 3, "nr3", "tip2", true };
	RezervareCamera r4{ 4, "nr4", "tip2", false };
	RezervareCamera r5{ 5, "nr5", "tip3", true };

	// adaug r1
	try {
		repo.add(r1);
		assert(true);
	}
	catch (const RepositoryException& exception) {
		assert(false);
	}

	// arunca exc pt ca r1 exista deja
	try {
		repo.add(r1);
		assert(false);
	}
	catch (const RepositoryException& exception) {
		assert(true);
	}

	// adaug r2
	try {
		repo.add(r2);
		assert(true);
	}
	catch (const RepositoryException& exception) {
		assert(false);
	}

	assert(repo.getAll().size() == 2);


	// incerc sa sterg r5, care nu exista -> exceptie
	try {
		repo.remove(r5);
		assert(false);
	}
	catch (const RepositoryException& exception) {
		assert(true);
	}
	try {
		repo.remove(r1);
		assert(true);
	}
	catch (const RepositoryException& exception) {
		assert(false);
	}

	assert(repo.getAll().size() == 1);
	r2.setNumar("numar_nou_r2");
	try {
		repo.update(r2);
		assert(true);
	}
	catch (const RepositoryException& exception) {
		assert(false);
	}
	try {
		repo.update(r5);
		assert(false);
	}
	catch (const RepositoryException& exception) {
		assert(true);
	}
	repo.remove(r2);
}

void testService() {
	Repository<RezervareCamera> repo{};
	Service service{ repo };
	RezervareCamera r1{ 1, "nr1", "tip1", false };
	RezervareCamera r2{ 2, "nr2", "tip1", true };
	RezervareCamera r3{ 3, "nr3", "tip2", true };
	RezervareCamera r4{ 4, "nr4", "tip2", true };
	RezervareCamera r5{ 5, "nr5", "tip3", false };

	assert(service.getAll().size() == repo.getAll().size());

	try {
		service.addRezervareCamera(r1.getId(), r1.getNumar(), r1.getTip(), r1.getEliberata());
		assert(true);
	}
	catch (RepositoryException& e) {
		assert(false);
	}
	try {
		service.addRezervareCamera(r1.getId(), r1.getNumar(), r1.getTip(), r1.getEliberata());
		assert(false);
	}
	catch (RepositoryException& e) {
		assert(true);
	}

	try {
		r1.setNumar("nr_nou");
		service.updateRezervareCamera(r1.getId(), r1.getNumar(), r1.getTip(), r1.getEliberata());
		RezervareCamera f = service.findRezervareCamera(r1.getId());
		assert(f.getNumar().compare(r1.getNumar())==0);
	}
	catch (RepositoryException& e) {
		assert(false);
	}

	try {
		service.removeRezervareCamera(r1.getId());
		assert(true);
	}
	catch (RepositoryException& e) {
		assert(false);
	}
	try {
		service.removeRezervareCamera(r1.getId());
		assert(false);
	}
	catch (RepositoryException& e) {
		assert(true);
	}


	try {
		service.addRezervareCamera(r1.getId(), r1.getNumar(), r1.getTip(), r1.getEliberata());
		service.addRezervareCamera(r2.getId(), r2.getNumar(), r2.getTip(), r2.getEliberata());
		service.addRezervareCamera(r3.getId(), r3.getNumar(), r3.getTip(), r3.getEliberata());
		service.addRezervareCamera(r4.getId(), r4.getNumar(), r4.getTip(), r4.getEliberata());
		service.addRezervareCamera(r5.getId(), r5.getNumar(), r5.getTip(), r5.getEliberata());
		vector<Statistica> procente = service.computePercentage();
		Statistica st1{ procente[0] };
		Statistica st2{ procente[1] };
		Statistica st3{ procente[2].getTip(),  procente[2].getProcent()};
		assert(st1.getTip().compare("tip3") == 0);
		assert(st1.getProcent() == 0);
		assert(st2.getTip().compare("tip1") == 0);
		assert(st2.getProcent() == 50);
		assert(st3.getTip().compare("tip2") == 0);
		assert(st3.getProcent() == 100);
	}
	catch (RepositoryException& e) {
		assert(false);
	}

}