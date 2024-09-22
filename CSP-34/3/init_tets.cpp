#include <vector>

int main() {
    int x = 1, y = 2, z = 3;
    
    std::vector<int> vec;
	vec.assign({x, y, z});
    
    // Alternatively, you can also use:
    // std::vector<int> vec{x, y, z};

    return 0;
}
