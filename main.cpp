#include <iostream>

using namespace std;
#include "Company.h"
int main() {
    Company myCompany;
    const char* filename = "C:\\Users\\PC\\CLionProjects\\Hard-Bus-Trip-v2\\random_file.txt";
    Parameters eventParameters;
    myCompany.read_file(filename, eventParameters);

    return 0;


}
