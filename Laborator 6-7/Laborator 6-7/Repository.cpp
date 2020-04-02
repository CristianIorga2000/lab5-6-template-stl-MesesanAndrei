//#include "Repository.h"
//
//using namespace std;
//
//RepositoryException::RepositoryException(string m) :msg{ m } {}
//
//string RepositoryException::getMsg()const {
//	return this->msg;
//}
//
//ostream& operator<<(ostream& out, const RepositoryException& ex) {
//	out << ex.msg << "\n";
//	return out;
//}
//
//
//
//
//
//template <class Entitate>
//bool Repository<Entitate>::exists(const Entitate& entitate)const {
//	try {
//		find(entitate.getId());
//		return true;
//	}
//	catch (const RepositoryException&) { return false; }
//}
//
//template <class Entitate>
//void Repository<Entitate>::add(const Entitate& entitate) {
//	if (exists(entitate)) {
//		throw RepositoryException("The entitate already exists.");
//	}
//	entitates.push_back(entitate);
//}
//
//
//template <class Entitate>
//void Repository<Entitate>::update(const Entitate& entitate) {
//	if (exists(entitate)) {
//		for (Entitate& item : entitates) {
//			if (item == entitate) {
//				item = entitate;
//			}
//		}
//		return;
//	}
//	throw RepositoryException("The entitate does not exist ");
//}
//
//
//template <class Entitate>
//void Repository<Entitate>::remove(const Entitate& entitate) {
//	if (exists(entitate) == false) {
//		throw RepositoryException("The entitate does not exist ");
//	}
//	entitates.erase(std::remove(entitates.begin(), entitates.end(), entitate), entitates.end());
//}
//
//template <class Entitate>
//const Entitate& Repository<Entitate>::find(int id) const {
//	auto result = find_if(getAll().begin(), getAll().end(), [&id](const Entitate& entitate)noexcept {
//		return entitate.getId() == id;
//		});
//	if (result == end(getAll())) {
//		throw RepositoryException("The entitate does not exist " + id);
//	}
//	return *result;
//}
//template <class Entitate>
//const vector<Entitate>& Repository<Entitate>::getAll()const noexcept {
//	return entitates;
//}