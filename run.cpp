// agee aita run korbo

/*
g++ -o run run.cpp
g++ -o correct correct.cpp
g++ -o wrong wrong.cpp
g++ -o generator generator.cpp

clang++ -std=c++17 run.cpp -o run
./run

 */

#include <iostream>
#include <random>
#include <chrono>
#include <bits/stdc++.h>
using namespace std;

const int ITER = 100; // select the number of iterations

// populate and save the correct, wrong, and generator files
int32_t main()
{
    // Compile the correct, wrong, and generator programs
    string correct = "g++ -o correct correct.cpp";
    system(correct.c_str()); // compiling the correct solution

    string wrong = "g++ -o wrong wrong.cpp";
    system(wrong.c_str()); // compiling the wrong solution

    string generator = "g++ -o generator generator.cpp";
    system(generator.c_str()); // compiling the generator

    auto st = clock();
    for (int t = 1; t <= ITER; t++)
    {
        cerr << "Trying for the " << t << "-th time :((\n";

        // Generate input case
        string in = "input.txt";
        string gen_command = "./generator > input.txt"; // Ensure the generator runs from current directory
        system(gen_command.c_str());

        // Run correct solution
        string correct_solution = "./correct < input.txt > correct_solution.txt"; // Ensure the correct solution runs
        system(correct_solution.c_str());

        // Run wrong solution
        string wrong_solution = "./wrong < input.txt > wrong_solution.txt"; // Ensure the wrong solution runs
        system(wrong_solution.c_str());

        // Read the correct solution output
        ifstream correct_file;
        correct_file.open("correct_solution.txt"); // opening correct solution file
        string correct_output = "", line;
        while (getline(correct_file, line))
        { // read every line, no need to use '.' as delimiter
            correct_output += line + "\n";
        }

        // Read the wrong solution output
        ifstream wrong_file;
        wrong_file.open("wrong_solution.txt"); // opening wrong solution file
        string wrong_output = "";
        while (getline(wrong_file, line))
        { // read every line
            wrong_output += line + "\n";
        }

        // Check if the outputs match
        if (correct_output != wrong_output)
        {
            cout << "MISMATCH FOUND while running test case " << t << "\n\n";
            cerr << "MISMATCH FOUND while running test case " << t << "\n\n";
            cout << "Check the input.txt file to find the case, correct_solution.txt to find the correct output and similarly check the wrong_solution.txt\n";
            cerr << "Time taken = " << 1.0 * (clock() - st) / CLOCKS_PER_SEC << "s\n";
            exit(0); // Stop execution if there's a mismatch
        }

        // Close files
        correct_file.close();
        wrong_file.close();
    }

    // No mismatches found after all iterations
    cout << "No cases found!\n";
    cerr << "No cases found!\n";
    cerr << "Time taken = " << 1.0 * (clock() - st) / CLOCKS_PER_SEC << "s\n";

    return 0;
}
