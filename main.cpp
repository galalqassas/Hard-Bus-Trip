#include <iostream>

using namespace std;
#include "Company.h"
int main() {
    Company myCompany;
    const char* filename = "C:\\Users\\LENOVO\\CLionProjects\\Hard-Bus-Trip\\random_file.txt";

    ArrivalEvent *ae;
    LeaveEvent *le;
    myCompany.read_file(filename, ae, le);

    return 0;


}
