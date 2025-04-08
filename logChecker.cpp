// #include <iostream>
// #include <fstream>
// #include <string>

// int main() {
//     std::ifstream file1("Task1/output.txt");
//     std::ifstream file2("test19.txt");

//     if (!file1.is_open() || !file2.is_open()) {
//         std::cerr << "Error: Could not open one or both files." << std::endl;
//         return 1;
//     }

//     std::string line1, line2;
//     std::string prevLine1, prevLine2;
//     int lineNum = 0;

//     while (std::getline(file1, line1) && std::getline(file2, line2)) {
//         ++lineNum;
//         if (line1 != line2) {
//             std::cout << "Files differ at line " << lineNum << ":\n";

//             if (lineNum > 1) {
//                 std::cout << "Previous line from file1: " << prevLine1 << "\n";
//                 std::cout << "Previous line from file2: " << prevLine2 << "\n";
//             } else {
//                 std::cout << "No previous line exists (difference at first line)." << std::endl;
//             }

//             std::cout << "file1: " << line1 << "\n";
//             std::cout << "file2: " << line2 << "\n";
//             return 0;
//         }

//         prevLine1 = line1;
//         prevLine2 = line2;
//     }

//     if (std::getline(file1, line1) || std::getline(file2, line2)) {
//         std::cout << "Files differ in length at line " << (lineNum + 1) << ":\n";
//         std::cout << "Previous line from file1: " << prevLine1 << "\n";
//         std::cout << "Previous line from file2: " << prevLine2 << "\n";
//         std::cout << "file1: " << (file1 ? line1 : "EOF") << "\n";
//         std::cout << "file2: " << (file2 ? line2 : "EOF") << "\n";
//         return 0;
//     }

//     std::cout << "Files are identical." << std::endl;
//     return 0;
// }
