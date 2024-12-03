#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>

const std::string TARGET_FILE = "src/input/day2.txt";
const uint32_t LINE_COUNT = 1000;
const std::string DELIMITER = " ";

std::unique_ptr<std::vector<std::int32_t>> parse_report(std::string report)
{
    std::unique_ptr<std::vector<int32_t>> levels(new std::vector<int32_t>);
    std::string level;
    size_t i = 0;
    while ((i = report.find(DELIMITER)) != std::string::npos)
    {
        level = report.substr(0, i);
        levels->push_back(std::stoi(level));
        report = report.substr(i + DELIMITER.length());
    }
    levels->push_back(std::stoi(report)); // last level of report

    return std::move(levels);
}

// g++ src/day2.cpp -o out/day2.out && out/day2.out
int main()
{
    std::vector<std::string> reports(1000);
    {
        std::ifstream input_file(TARGET_FILE);
        if (!input_file.is_open())
        {
            std::cout << "Could not open file: " << TARGET_FILE;
            return 1;
        }

        std::string line;
        uint16_t i = 0;
        while (std::getline(input_file, line))
        {
            reports[i] = line;
            i++;
        }
    }

    uint16_t safe = 0;
    for (auto report : reports)
    {
        auto levels = parse_report(report);
        bool decreasing = true;
        bool increasing = true;
        bool proximity = true;

        int32_t previous = -1;
        for (const auto level : *levels)
        {
            if (previous == -1)
            {
                previous = level;
                continue;
            }
            int32_t diff = abs(previous - level);

            if (diff == 0 || diff > 3)
                proximity = false;
            if (decreasing && previous <= level)
                decreasing = false;
            if (increasing && previous >= level)
                increasing = false;

            if (!decreasing && !increasing && !proximity)
                break;

            previous = level;
        }

        if ((decreasing || increasing) && proximity)
            safe++;
    }
    std::cout << "The number of safe reports is: " << safe << std::endl;

    return 0;
}