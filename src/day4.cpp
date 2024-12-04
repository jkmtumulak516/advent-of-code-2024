#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <memory>
#include <tuple>

using matrix = std::vector<std::vector<char>>;
using coordinates = std::tuple<size_t, size_t>;

const std::string TARGET_FILE = "src/input/day4.txt";
const uint32_t LINE_COUNT = 140;

// Directions
const coordinates U = coordinates(1, 0);
const coordinates D = coordinates(-1, 0);
const coordinates L = coordinates(0, -1);
const coordinates R = coordinates(0, 1);
const coordinates UR = coordinates(1, 1);
const coordinates UL = coordinates(1, -1);
const coordinates DR = coordinates(-1, 1);
const coordinates DL = coordinates(-1, -1);
const std::vector<coordinates> DIRECTIONS{ U, D, L, R, UR, UL, DR, DL };

std::unique_ptr<std::vector<coordinates>> find_xs(const matrix &grid)
{
    std::unique_ptr<std::vector<coordinates>> xs(new std::vector<coordinates>);

    for (size_t y = 0; y < grid.size(); y++)
        for (size_t x = 0; x < grid[y].size(); x++)
            if (grid[y][x] == 'X')
                xs->push_back(coordinates(y, x));

    return std::move(xs);
}

bool inline is_in_bounds(const matrix &grid, coordinates xy)
{
    return (std::get<0>(xy) >= 0 && std::get<0>(xy) < grid.size())
        && (std::get<1>(xy) >= 0 && std::get<1>(xy) < grid[std::get<0>(xy)].size());
}

coordinates inline apply_direction(coordinates point, coordinates direction)
{
    return coordinates(
        std::get<0>(point) + std::get<0>(direction),
        std::get<1>(point) + std::get<1>(direction)
    );
}

bool inline is_char(const matrix &grid, coordinates xy, char c)
{
    return grid[std::get<0>(xy)][std::get<1>(xy)] == c;
}

uint32_t find_xmas(const matrix &grid, coordinates start)
{
    uint32_t found = 0;

    for (auto direction : DIRECTIONS)
    {
        auto m = apply_direction(start, direction);
        if (is_in_bounds(grid, m) && is_char(grid, m, 'M'))
        {
            auto a = apply_direction(m, direction);
            if (is_in_bounds(grid, a) && is_char(grid, a, 'A'))
            {
                auto s = apply_direction(a, direction);
                if (is_in_bounds(grid, s) && is_char(grid, s, 'S'))
                    found++;
            }
        }
    }

    return found;
}

// g++ src/day4.cpp -o out/day4.out && out/day4.out
int main()
{
    matrix grid(LINE_COUNT);
    {
        std::ifstream input_file(TARGET_FILE);
        if (!input_file.is_open())
        {
            std::cout << "Could not open file: " << TARGET_FILE;
            return 1;
        }

        std::string line;
        for (size_t y = 0; y < grid.size(); y++)
        {
            input_file >> line;
            grid[y] = std::vector<char>(line.size());
            for (size_t x = 0; x < line.size(); x++)
                grid[y][x] = line[x];
        }
    }

    uint32_t found = 0;
    auto xs = find_xs(grid);
    for (auto xy : *xs)
        found += find_xmas(grid, xy);

    std::cout << "Found XMAS " << found << " times!" << std::endl;
    return 0;
}