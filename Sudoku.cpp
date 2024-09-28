#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <sstream>

class Grid
{
private:
    /*二维矩阵变量matrix*/
    std::vector<std::vector<int>> matrix;
public:
    /*构造函数，根据行列数生成二维矩阵*/
    Grid(int row, int col)
    {
        matrix.resize(row, std::vector<int>(col, 0));
    };

    /*构造函数，根据二维矩阵生成Grid对象*/
    Grid(const std::vector<std::vector<int>>& initMatrix)
    {
        matrix = initMatrix;
    }

    /*拷贝构造函数*/
    Grid(const Grid& initGrid)
    {
        matrix = initGrid.matrix;
    }

    /*析构函数*/
    ~Grid(){};

    /*获取某个坐标的值*/
    int getData(int row, int col){
        return matrix[row][col];
    }

    /*将matrix中(row, col)坐标的数值更改为num*/
    void CellChange(int row, int col, int num)
    {
        matrix[row][col] = num;
    }

    /*获取二维矩阵的第row行*/
    std::vector<int> getRow(int row)
    {
        return matrix[row];
    }

    /*获取二维矩阵的第col列*/
    std::vector<int> getCol(int col)
    {
        std::vector<int> data;
        for(auto &row: matrix)
        {
            data.push_back(row[col]);
        }
        return data;
    }

    /*根据坐标获取所在box的数据*/
    std::vector<int> getBox(int row, int col)
    {
        std::vector<int> data;
        int rowBegin = row / 3 * 3, colBegin = col / 3 * 3;
        for(int i=rowBegin; i<rowBegin+3; ++i)
        {
            for(int j=colBegin; j<colBegin+3; ++j)
            {
                data.push_back(matrix[i][j]);
            }
        }
        return data;
    }

    /*展示二维矩阵的数据*/
    void display()
    {
        for(auto &row: matrix)
        {
            std::cout << "| ";
            for(int &num: row){
                std::cout << num << " | ";
            }
            std::cout << std::endl;
        }
    }

    int rows() const{
        return matrix.size();
    }

    int cols() const{
        return matrix[0].size();
    }

    /*串行化*/
    std::string serialize() const {
        std::ostringstream oss;
        oss << rows() << " " << cols() << "\n"; // 首先写入行列信息
        for (const auto& row : matrix) {
            for (int val : row) {
                oss << val << " ";
            }
            oss << "\n"; // 每行结束后换行
        }
        return oss.str();
    }

    /*反串行化*/
    void deserialize(const std::string& str) {
        std::istringstream iss(str);
        int r, c;
        iss >> r >> c; // 读取行列信息
        matrix.resize(r, std::vector<int>(c, 0));

        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                iss >> matrix[i][j]; // 逐个读取矩阵元素
            }
        }
    }
};


class Sudoku
{
private:
    /*存储数据表格数据的变量cells*/
    Grid cells;
public:
    Sudoku(std::string input): cells(9, 9)
    {
        if(input.size() != 81){
            throw "The string length is invalid!";
        }
        for(int i=0;i<81;++i)
        {
            char ch = input[i];
            if(ch < '0' || ch > '9'){
                throw "The char is invalid!";
            }
            cells.CellChange(i/9, i%9, ch-'0');
        }
    }

    /*析构函数*/
    ~Sudoku(){};

    /*获取确定坐标的候选值*/
    std::vector<int> getCandidates(int row, int col)
    {
        std::vector<int> data = cells.getRow(row);
        std::set<int> rowSet(data.begin(), data.end());
        data = cells.getCol(col);
        std::set<int> colSet(data.begin(), data.end());
        data = cells.getBox(row, col);
        std::set<int> boxSet(data.begin(), data.end());

        while(!data.empty())
        {
            data.pop_back();
        }

        for(int i=1; i<=9; ++i)
        {
            if(!rowSet.count(i) && !colSet.count(i) && !boxSet.count(i)){
                data.push_back(i);
            }
        }

        return data;
    }

    void candidates_dispaly()
    {
        std::cout << "Below are the candidate values for the spaces:" << std::endl;
        for(int row=0; row<9; ++row)
        {
            for(int col=0; col<9; ++col)
            {
                if(cells.getData(row, col) == 0)
                {
                    std::vector<int> candidate = getCandidates(row, col);
                    std::cout << "(" << row+1 << ", " << col+1 << ") :";
                    for(int &num: candidate)
                    {
                        std::cout << num << " ";
                    } 
                    std::cout << std::endl;
                }
            }
        }
    }

    /*解决函数*/
    void Solution()
    {
        std::cout << "The original Sudoku table is displayed!" << std::endl;
        cells.display();
        std::cout << "The matrix is indexed from 1 to 81 from left to right and top to bottom!" << std::endl;
        candidates_dispaly();
    }
};

int main(int argc, char const *argv[])
{
    /*测试代码*/
    std::string input = "017903600000080000900000507072010430000402070064370250701000065000030000005601720";
    /*
    字符串长度不足81位报错测试：79036000000800009000005070720104300004020700643702
    字符串包含异常字符报错测试：01790360000008000090000050707201043000040207006437025070100006500003000000560172a
    其余正常测试案例：005060900000500000000807050090043078001000400840700080060204000000008000003010700
    */

    try
    {
        Sudoku answer(input);
        answer.Solution();
    }
    catch(const char *err)
    {
        std::cerr << err << '\n';
    }
    
    system("pause");
    return 0;
}