#include "Iron.h"

int main(int argc, char *argv[]) {
	iron::Log::s()->logWarning("Test.", __LINE__, std::string(__FUNCTION__), std::string(__FILE__));
	iron::Vector2 *v = nullptr;
	iron::Vector2 v1 = iron::Vector2(1, 1);
	iron::Vector2 v2 = iron::Vector2(1, 1);
	iron::Vector2::add(v1, v2, v);
	std::cout << v1.x;
	return 0;
}