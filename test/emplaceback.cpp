#include <fastvec.hpp>

struct A {
	int x, y,z;
	A(int x, int y, int z) : x(x), y(y), z(z) {}
};

int main() {
	FastVec<A> vec;

	A& a = vec.emplace_back(10, 20, 30);

	assert(
		a.x == 10 &&
		a.y == 20 &&
		a.z == 30
	);

	assert(
		vec.size() == 1 &&
		&a == vec.begin()
	);

	return 0;
}
