#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
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
	std::string data;
	bool is_end;
	std::unique_ptr<std::vector<node>> nexts;

	void insert(std::string::size_type pos, const char *str);

public:
	node(const std::string &s)	: data(s), is_end(true), nexts(std::make_unique<std::vector<node>>()) {}
	node(const char *s)		: data(s), is_end(true), nexts(std::make_unique<std::vector<node>>()) {}
	node(void)			: data(),  is_end(false), nexts(std::make_unique<std::vector<node>>()) {}
	bool operator<(const node& n) const { return data < n.data; }
	bool operator!=(const node& n) const { return data != n.data; }
	void add(const char *str);
	void show_all(void);
	void help(void);
};


void node::insert(std::string::size_type pos, const char *str)
{
	if (pos == std::string::npos) {
		if (data.empty() && !is_end) {
			data = str;
			is_end = true;
		} else if (strlen(str) == 0) {
			is_end = true;
		} else {
			nexts->emplace_back(str);
			is_end = true;
		}
	} else {
		node tail{std::string{data.c_str(), pos, std::string::npos}};
		data.erase(pos);

		tail.nexts = std::move(nexts);
		nexts = std::make_unique<std::vector<node>>();
		tail.is_end = is_end;
		nexts->emplace_back(std::move(tail));
		if (strlen(str) > 0) {
			nexts->emplace_back(str);
			is_end = false;
		}
		else {
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

	for (node &a : *nexts) {
		if (a.data[0] == str[0]) {	// quick way to peep is this string candidate to match
			a.add(str);
			return;		// all strings starts from different letters, so stop searching
		}
	}
	insert(pos, str);
}

void node::show_all(void)
{
	std::list<std::string *> fls;

	std::function<void(node &)> f = [&fls, &f] (node &n) {
		if (n.is_end) {
			for (auto a : fls)
				std::cout << *a;
			std::cout << n.data << std::endl;
		}
		if (n.nexts->empty())
			return;

		fls.push_back(&n.data);
		for (auto& a : *(n.nexts)) {
			f(a);
		}
		fls.pop_back();
	};

	f(*this);
}

void node::help(void)
{
	static int tabs = 0;
	for (int i = 0; i < tabs; ++i) std::cout << "\t";
	std::cout << "data: \"" << data << "\"" << std::endl;
	for (int i = 0; i < tabs; ++i) std::cout << "\t";
	std::cout << "is_end: " << is_end << std::endl;

	std::cout << "{" << std::endl;
	++tabs;
	for (auto &a : *nexts) {
		a.help();
	}
	--tabs;
	std::cout << "}" << std::endl;
}


int main(int argc, char ** argv)
{
	(void) argc, (void) argv;

	node head{};
	for(std::string line; std::getline(std::cin, line); ) {
		head.add(line.c_str());
		std::cout << "============= tree ===========" << std::endl;
		head.show_all();
		std::cout << "=======================" << std::endl;
		head.help();
		std::cout << "=======================" << std::endl;
	}

	return 0;
}

