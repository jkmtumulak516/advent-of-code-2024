#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include <sstream>
#include <span>
#include <iterator>


const std::string TARGET_FILE = "src/input/day3.txt";
const uint32_t LINE_COUNT = 6;
const std::string INSTRUCTION_PATTERN = "mul\\((\\d+),(\\d+)\\)";
const std::string VARIABLE_PATTERN = "mul\\((\\d+),(\\d+)\\)";

int32_t sum_of_line(std::string line)
{
    int32_t sum = 0;
    std::regex instruction_pattern(INSTRUCTION_PATTERN);
    std::regex variable_pattern(VARIABLE_PATTERN);

    std::smatch instructions;

    while (std::regex_search(line, instructions, instruction_pattern))
    {
        int32_t product = 1;
        auto it_instructions = std::next(instructions.begin(), 1);

        while (it_instructions != instructions.end())
        {
            auto num = *it_instructions;
            product *= std::stoi(num);
            it_instructions = std::next(it_instructions);
        }
        // for (auto instruction : instructions.)
        //     std::cout << instruction << std::endl;
        sum += product;
        line = instructions.suffix().str();
    }


    return sum;
}

// g++ src/day3.cpp -o out/day3.out && out/day3.out
int main()
{
    std::vector<std::string> memory(LINE_COUNT);
    {
        std::ifstream input_file(TARGET_FILE);
        if (!input_file.is_open())
        {
            std::cout << "Could not open file: " << TARGET_FILE;
            return 1;
        }

        std::string line;
        size_t i = 0;
        while (std::getline(input_file, line))
        {
            memory[i] = line;
            i++;
        }
    }

    int32_t sum = 0;
    for (auto memory_line : memory)
        sum +=  sum_of_line(memory_line);

    std::cout << "The sum is: " << sum << std::endl;

    return 0;
}