#pragma once
#include "RezervareCamera.h"
#include "Repository.h"
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
	Repository<RezervareCamera> repo{};


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

}

