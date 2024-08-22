#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>

using namespace std;

struct DirectoryReconstruction {
    int total_files = 0;        // Tracks the total number of files in the system
    int total_depth = 0;        // Tracks the total depth of all files encountered so dfar
    int max_depth = 0;          // Tracks the size of directory with max depth
    string deepest_path = "/";  // Tracks the current deepest path
    string current_path = "/";  // Track the current path as a single string
    int current_depth = 0;      // Track the current depth

    void processCommand(const string& command) {
        if (command.substr(0, 5) == "$ cd ") {
            string dir = command.substr(5);
            if (dir == "/") {
                // Reset to root directory
                current_path = "/";
                current_depth = 0;
            } else if (dir == "..") {
                if (current_depth > 0) {
                    // Remove the last directory from the path
                    size_t pos = current_path.find_last_of('/', current_path.length() - 2);
                    current_path = current_path.substr(0, pos + 1);
                    current_depth--;
                }
            } else {
                // Move into a new directory
                current_path += dir + "/";
                current_depth++;
            }
        } else if (command.substr(0, 4) == "$ ls") {
            // No action needed for ls command
        } else {
            // This is a file or directory entry
            istringstream iss(command);
            string first_part, file_name;
            iss >> first_part >> file_name;
            if (first_part != "dir") {
                // This is a file entry
                total_files++;
                total_depth += current_depth;
                
                if (current_depth > max_depth) {
                    max_depth = current_depth;
                    deepest_path = current_path + file_name;
                }
            }
        }
    }

    void printResults() {
        double average_depth = total_files ? (double)total_depth / total_files : 0.0;
        cout << total_files << ",\"" << deepest_path << "\"," << average_depth << endl;
    }
};

int main() {
    DirectoryReconstruction dr;
    string command;
    vector<string> input_commands;

    ifstream inputFile("input.txt");
    while (getline(inputFile, command)) {
        input_commands.push_back(command);
    }
    inputFile.close();

    for (const string& cmd : input_commands) {
        dr.processCommand(cmd);
    }
    dr.printResults();
    return 0;
}
