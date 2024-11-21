#include <fastvec.hpp>

#define QTY 1000

int main() {
	FastVec<int> vec;

	for (int i=0; i<QTY; i++) {
		vec.push_back(i);
	}

	std::cout << vec << std::endl;
	assert(vec.capacity() == 1024);

	for (int i=0; i<QTY; i++) {
		assert(vec.pop_back() == QTY -i-1);
	}

	return 0;
}
