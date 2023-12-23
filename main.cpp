#include <iostream>

using namespace std;
#include "Company.h"
int main() {
    // Create an instance of the Company class
    Company myCompany;

    // Define the filename from which you want to load data
    const char* filename = "random_file.txt"; // Replace with your actual file name

    // Parameters object to store data loaded from the file
    Parameters eventParameters;

    // Call the load function
    myCompany.read_file(filename, eventParameters);

    // Perform other operations or simulations using the loaded data

    return 0;
}
