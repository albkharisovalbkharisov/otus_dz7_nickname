#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include <memory>
#include <forward_list>
#include <string.h>

class node
{
	std::string data;
	bool is_end;
	std::unique_ptr<std::vector<node>> nexts;

	void insert(std::string::size_type pos, const char *str);

public:
	node(const std::string &s)	: data(s), is_end(false), nexts(std::make_unique<std::vector<node>>()) {}
	node(const char *s)		: data(s), is_end(false), nexts(std::make_unique<std::vector<node>>()) {}
	node(void)			: data(),  is_end(false), nexts(std::make_unique<std::vector<node>>()) {}
	bool operator<(const node& n) const { return data < n.data; }
	bool operator!=(const node& n) const { return data != n.data; }
	void add(const char *str);
	void show_all(void);
};


void node::insert(std::string::size_type pos, const char *str)
{
	std::cout << "insert: \"" << data << "\", pos = " << pos << ", str = " << str << std::endl;
	if (pos == std::string::npos) {
		if (strlen(str) == 0) {
			std::cout << "case 1" << std::endl;
			is_end = true;
		} else {
			std::cout << "case 2" << std::endl;
			nexts->emplace_back(str);
		}
	} else {
		std::cout << "case 3" << std::endl;
		node tail{std::string{data.c_str(), pos}};
		data.erase(pos);

		tail.nexts = std::move(nexts);
		nexts = std::make_unique<std::vector<node>>();
		tail.is_end = is_end;
		is_end = false;
		nexts->emplace_back(str);
		nexts->emplace_back(std::move(tail));
	}
}


void node::add(const char *str)
{
	std::cout << "add: \"" << str << "\"" << std::endl;
	auto pos = data.find_first_not_of(str);
	if (pos != std::string::npos) {
		std::cout << "stop searching1" << std::endl;
		insert(pos, str + pos);
		return;
	}

	std::cout << "nexts->size = " << nexts->size() << std::endl;
	str += data.size();

	for (node &a : *nexts) {
		std::cout << "compare to... \"" << a.data << "\"" << std::endl;
		if (a.data[0] == str[0]) {	// quick way to peep is this string candidate to match
			std::cout << "go deeper..." << std::endl;
			a.add(str);
			return;		// all strings starts from different letters, so stop searching
		}
	}
	std::cout << "stop searching1" << std::endl;
	insert(pos, str);
}

void node::show_all(void)
{
//	std::forward_list<std::string *> fls;
	std::list<std::string *> fls;
//	auto head = fls.before_begin();
	
	auto f = [&](node & n)
	{
		fls.push_back(&n.data);
		for (auto & a : *nexts) {
			f(a);
		}
		fls.erase(fls.rbegin());
	};
	
	f(it, *this);
}

int main(int argc, char ** argv)
{
	(void) argc, (void) argv;
	node head{};
	for(std::string line; std::getline(std::cin, line); ) {
		head.add(line.c_str());
	}

	return 0;
}

