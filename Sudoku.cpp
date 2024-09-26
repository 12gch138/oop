#include <iostream>
#include <string>
#include <vector>

class Grid
{
private:
/*matrix*/
    std::vector<std::vector<int>> matrix;
public:
    Grid()
    {
        matrix.resize(9, std::vector<int>(9, 0));
    };
    ~Grid();
};


class Sudoku
{
private:
    /* data */
public:
    Sudoku(/* args */);
    ~Sudoku();
};

int main(int argc, char const *argv[])
{
    std::string Data_string;
    std::cin >> Data_string;
    try
    {
        std::cout << "Hello World!" << std::endl;
    }
    catch(const std::exception& err)
    {
        std::cerr << err.what() << '\n';
    }
    
    return 0;
}