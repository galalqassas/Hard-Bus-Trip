#include <iostream>

using namespace std;
#include "Company.h"
int main() {
    Company myCompany;
    const char* filename = "C:\\Users\\LENOVO\\CLionProjects\\Hard-Bus-Trip\\random_file.txt";
    Parameters eventParameters;
    ArrivalEvent *ae;
    LeaveEvent *le;
    myCompany.read_file(filename, eventParameters,ae,le);

    return 0;


}
