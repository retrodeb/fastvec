#include <fastvec.hpp>

#define QTY 1000

int main() {
	FastVec<int> fv;

	for (int i=0; i<QTY; i++) {
		fv.push_back(i);
	}

	std::cout << fv << std::endl;
	if (fv.capacity() != 1024) {
		std::cerr << "invalid capacity" << std::endl;
		return 1;
	}

	for (int i=0; i<QTY; i++) {
		auto v = fv.pop_back();
		std::cout << v << std::endl;
		if (v != QTY -i-1) return 1;
	}

	return 0;
}
