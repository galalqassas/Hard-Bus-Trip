#include <iostream>

using namespace std;
#include "Company.h"
int main() {
    Company myCompany;
    const char* filename = "C:\\Users\\Galal\\CLionProjects\\Hard-Bus-Trip\\random_file.txt";
    Parameters eventParameters;
    myCompany.read_file(filename, eventParameters);
    return 0;
}
