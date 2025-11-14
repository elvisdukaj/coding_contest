#include "application.h"
#include <vector>
#include <string>

int main() {
    application();

    std::vector<std::string> vec;
    vec.push_back("test_package");

    application_print_vector(vec);
}
