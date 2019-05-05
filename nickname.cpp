#include <cstdlib>
#include <iostream>
#include <string>
//#include <unordered_map>
#include <map>
#include <typeinfo>
#include <memory>
#include <forward_list>
#include <string.h>
#include <list>
#include <functional>


// Works for C-style strings.


// First I thought find_first_if_not() compares 2 strings
// and returns first mismatch, but I was surprised it dont.
// Now I'm in train, there are no internet, so I writing my
// own bycycle. Isn't it what training courses is all about?
//
// Seems "std::mismatch" can do the same.
//
// returns	npos if no different chars found
//		number of first mismatch character
//
static auto correct_compare(const std::string &s1, const char *s2)
{
	std::string::size_type i = 0;

	for ( ; (i != s1.size()) && s2[i]; ++i) {
		if (s1[i] != s2[i])
			break;
	}

	if (i == s1.size())
		return std::string::npos;

	return i;
}


class node
{
	using charind = std::map<char, node>;

	std::string data;
	bool is_end;
	std::unique_ptr<charind> nexts;

	void insert(std::string::size_type pos, const char *str);
	void print_accumulated(const std::list<const std::string *> &fls) const;

public:
	node(const std::string &s)	: data(s), is_end(true), nexts(std::make_unique<charind>()) {}
	node(const char *s)		: data(s), is_end(true), nexts(std::make_unique<charind>()) {}
	node(void)			: data(),  is_end(false), nexts(std::make_unique<charind>()) {}
	bool operator<(const node& n) const { return data < n.data; }
	bool operator!=(const node& n) const { return data != n.data; }
	void add(const char *str);
	void show_elements(void) const;
	void show_structure(void) const;
};


void node::insert(std::string::size_type pos, const char *str)
{
	if (pos == std::string::npos) {
		if (data.empty() && !is_end && nexts->empty()) {
			data = str;
			is_end = true;
		} else if (strlen(str) == 0) {
			is_end = true;
		} else {
			nexts->emplace(str[0], str);
		}
	} else {
		node tail{std::string{data.c_str(), pos, std::string::npos}};
		data.erase(pos);

		tail.nexts = std::move(nexts);
		nexts = std::make_unique<charind>();
		tail.is_end = is_end;
		nexts->emplace(tail.data[0], std::move(tail));
		if (strlen(str) > 0) {
			nexts->emplace(str[0], str);
			is_end = false;
		} else {
			is_end = true;
		}
	}
}


void node::add(const char *str)
{
	auto pos = correct_compare(data, str);
	if (pos != std::string::npos) {
		insert(pos, str + pos);
		return;
	}

	str += data.size();

	auto it = nexts->find(str[0]);
	if (it != nexts->end()) {
		it->second.add(str);
		return;
	}
	insert(pos, str);
}

void node::print_accumulated(const std::list<const std::string *> &fls) const
{
	for (auto a : fls)
		std::cout << *a;
	std::cout << data;
	std::cout << " ";

	for (auto a : fls)
		std::cout << *a;
	if (nexts->empty())
		std::cout << data[0] << std::endl;
	else
		std::cout << data << std::endl;
}

void node::show_elements(void) const
{
	std::list<const std::string *> fls;

	std::function<void(const node &)> f = [&fls, &f] (const node &n) {
		if (n.is_end)
			n.print_accumulated(fls);

		if (n.nexts->empty())
			return;

		fls.push_back(&n.data);
		for (auto& a : *(n.nexts))
			f(a.second);
		fls.pop_back();
	};

	f(*this);
}


void node::show_structure(void) const
{
	static std::string offset{};
	std::cout << offset << "\"" << data << "\"" << (is_end ? "$" : "") << std::endl;

	offset += "  ";
	for (auto &a : *nexts) {
		a.second.show_structure();
	}
	offset.pop_back();
	offset.pop_back();
}


int main(int argc, char ** argv)
{
	(void) argc, (void) argv;

	node head{};
	for(std::string line; std::getline(std::cin, line); ) {
		head.add(line.c_str());
	}

	head.show_structure();
	head.show_elements();

	return 0;
}

