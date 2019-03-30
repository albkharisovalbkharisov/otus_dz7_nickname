#include <cstdlib>
#include <iostream>
#include <string>
#include <set>
#include <typeinfo>

class node
{
	std::string data;
	bool is_end;
	std::shared_ptr<std::set<node>> nexts;

//	node& operator[](const std::string &index) const { return nexts[index]; }
//	node& operator[](const char *index) const { return (*this)[std::string(index)]; }

	/*
	auto insert(const char *str) const {
		if (0 == data.size())
			return *this;
		auto pos = data.find_first_not_of(str);
		if (pos != std::string::npos)
			return *this;
		if (nexts.empty())
			nexts.emplace("");
		for (auto &a : nexts) {
			auto b = a[str + pos];
			if (b != nullptr)
				return;
		}
		return nullptr;
	}
*/


	void insert(size_t pos, const char *str)
	{
		std::string p{};

	}


	auto add(const char *str) const
	{
		auto pos = data.find_first_not_of(str);
		if (pos != std::string::npos) {
			;
			return this;
		}

		for (const auto &a : *nexts) {
			if (a.data[0] == str[pos])
				return a.add(str + pos);
		}
		return this;
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

