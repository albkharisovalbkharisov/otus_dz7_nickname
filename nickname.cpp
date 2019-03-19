#include <cstdlib>
#include <iostream>
#include <string>
#include <set>
#include <typeinfo>

class node
{
	std::string data;
	bool is_end;
	std::set<node> nexts;

//	node& operator[](const std::string &index) const { return nexts[index]; }
//	node& operator[](const char *index) const { return (*this)[std::string(index)]; }

	auto operator[](const char *index) const { return (*this)[std::string(index)]; }

	auto operator[](const std::string &str) const {
		auto pos = data.find_first_not_of(str);
		if ((pos == std::string::npos) && (str.size() == data.size()))
		;
		if (pos == 0)
		{
			// somehow create a new node
		}
		std::string str_index(str, pos, );
		for (const auto &a : nexts) {
			std::string::size_type p;
			std::tie(, p) = a[name];	// recursion
		}
		return std::make_tuple(nexts[str], pos);
	}

public:
	node(const std::string &s) : data(s), is_end(false) {}
//	node(void) : data(""), is_end(false) {}
	node(void) = default;
	bool operator<(const node& n) const { return data < n.data; }
	bool operator!=(const node& n) const { return data != n.data; }

	void add(const std::string &name)
	{
		if (nexts.empty()) {
			std::cout << "data = " << data << " | " << name << std::endl;
			nexts.emplace(name);
			return;
		}
		for (auto &a : nexts) {
			auto pos = a.data.find_first_not_of(name);

			std::cout << "find: \"" << name << "\" in \"" << a.data << "\"" << std::endl;
			if (pos == std::string::npos) {
				std::cout << "strings are same: go deeper" << std::endl;
				return;
			}
			else {
				std::cout << "pos = " << pos << ": split string" << std::endl;
			}
		}
	}


};

int main(int argc, char ** argv)
{
	(void) argc, (void) argv;
	node head;
	for(std::string line; std::getline(std::cin, line); ) {
		head.add(line);
	}

	return 0;
}

