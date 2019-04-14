#include <cstdlib>
#include <iostream>
#include <string>
#include <set>
#include <typeinfo>

class node
{
	std::string data;
	bool is_end;
	std::unique_ptr<std::set<node>> nexts;

	void node::insert(std::string::size_type pos, const char *str);

public:
	node(const std::string &s) : data(s), is_end(false) {}
	node(void) = default;
	bool operator<(const node& n) const { return data < n.data; }
	bool operator!=(const node& n) const { return data != n.data; }
	void node::add(const char *str);

#if 0
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
#endif	// 0
};


void node::insert(std::string::size_type pos, const char *str)
{
#if 0
	std::cout << "insert: \"" << data << "\", pos = " << pos << ", str = " << str << std::endl;
	if (pos == std::string::npos) {
		
	} else if (pos == data.size()) {
		if (strlen(str) == 0) {
			std::cout << "case 1" << std::endl;
			is_end = true;
		} else {
			std::cout << "case 2" << std::endl;
			nexts->emplace(str);
		}
	} else {
		std::cout << "case 3" << std::endl;
		node tail{std::string{data.c_str, pos}};
		data.erase(pos);

		tail.nexts = nexts;		// move unique_ptr
		nexts = std::make_unique<decltype(*nexts)>(  );	// new decltype(*nexts);
		tail.is_end = is_end;
		is_end = false;
		nexts->emplace(str);
		nexts->insert(std::move(tail));		// nexts->emplace(tail);
	}
#endif // 0
}


void node::add(const char *str)
{
#if 0
	std::cout << "add: \"" << str << "\"" << std::endl;
	auto pos = data.find_first_not_of(str);
	if (pos != std::string::npos) {
		insert(pos, str + pos);
		return;
	}

	str += data.size();

	for (const auto &a : *nexts) {
		if (a.data[0] == str[0]) {	// quick way to peep is this string are candidate to match string
			a.add(str);
			return;		// all strings starts from different letters, so stop searching
		}
	}
	insert(pos, str);
#endif	// 0
}



int main(int argc, char ** argv)
{
	(void) argc, (void) argv;
	node head;
	for(std::string line; std::getline(std::cin, line); ) {
		head.add(line);
	}

	return 0;
}

