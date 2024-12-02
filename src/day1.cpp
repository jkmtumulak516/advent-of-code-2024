#include <iostream>
#include <stdint.h>
#include <vector>
#include <fstream>
#include <string>
#include <bits/stdc++.h>

const std::string TARGET_FILE = "src/input/day1.txt";
const uint32_t LINE_COUNT = 1000;

// g++ src/day1.cpp -o out/day1.out && out/day1.out
int main()
{
    std::vector<int32_t> l(LINE_COUNT), r(LINE_COUNT);

    {
        std::ifstream input_file(TARGET_FILE);

        if (!input_file.is_open())
        {
            std::cout << "Could not open file: " << TARGET_FILE;
            return 0;
        }

        int32_t a, b, i = 0;
        while (input_file >> a >> b)
        {
            l[i] = a;
            r[i] = b;
            i++;
        }
    }

    std::stable_sort(l.begin(), l.end());
    std::stable_sort(r.begin(), r.end());

    int32_t distance = 0;
    for (uint32_t i = 0; i < LINE_COUNT; i++)
        distance += abs(l[i] - r[i]);

    std::cout << "Distance between lists: " << distance << std::endl;

    return 0;
}