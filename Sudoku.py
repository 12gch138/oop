class Grid:
    def __init__(self, row, col):
        """构造函数，根据行列数生成二维矩阵"""
        self.matrix = [[0 for _ in range(col)] for _ in range(row)]

    def __copy__(self):
        """拷贝构造函数"""
        return Grid(self.rows(), self.cols(), self.matrix)

    def get_data(self, row, col):
        """获取某个坐标的值"""
        return self.matrix[row][col]

    def cell_change(self, row, col, num):
        """将matrix中(row, col)坐标的数值更改为num"""
        self.matrix[row][col] = num

    def get_row(self, row):
        """获取二维矩阵的第row行"""
        return self.matrix[row]

    def get_col(self, col):
        """获取二维矩阵的第col列"""
        return [row[col] for row in self.matrix]

    def get_box(self, row, col):
        """根据坐标获取所在box的数据"""
        data = []
        row_begin = (row // 3) * 3
        col_begin = (col // 3) * 3
        for i in range(row_begin, row_begin + 3):
            for j in range(col_begin, col_begin + 3):
                data.append(self.matrix[i][j])
        return data

    def display(self):
        """展示二维矩阵的数据"""
        for row in self.matrix:
            print("| " + " | ".join(map(str, row)) + " |")

    def rows(self):
        """返回矩阵行数"""
        return len(self.matrix)

    def cols(self):
        """返回矩阵列数"""
        return len(self.matrix[0]) if self.matrix else 0

    def serialize(self):
        """串行化"""
        result = f"{self.rows()} {self.cols()}\n"
        for row in self.matrix:
            result += " ".join(map(str, row)) + "\n"
        return result

    def deserialize(self, str_data):
        """反串行化"""
        lines = str_data.strip().split("\n")
        r, c = map(int, lines[0].split())
        self.matrix = [[0 for _ in range(c)] for _ in range(r)]
        for i in range(r):
            self.matrix[i] = list(map(int, lines[i + 1].split()))


class Sudoku:
    def __init__(self, input_str):
        """初始化Sudoku，输入字符串必须为81个字符"""
        self.cells = Grid(9, 9)
        if len(input_str) != 81:
            raise ValueError("The string length is invalid!")
        for i in range(81):
            ch = input_str[i]
            if ch < '0' or ch > '9':
                raise ValueError("The char is invalid!")
            self.cells.cell_change(i // 9, i % 9, int(ch))

    def get_candidates(self, row, col):
        """获取确定坐标的候选值"""
        row_data = self.cells.get_row(row)
        row_set = set(row_data)
        col_data = self.cells.get_col(col)
        col_set = set(col_data)
        box_data = self.cells.get_box(row, col)
        box_set = set(box_data)

        candidates = []
        for i in range(1, 10):
            if i not in row_set and i not in col_set and i not in box_set:
                candidates.append(i)
        return candidates

    def candidates_display(self):
        """展示每个空单元格的候选值"""
        print("Below are the candidate values for the spaces:")
        for row in range(9):
            for col in range(9):
                if self.cells.get_data(row, col) == 0:
                    candidate = self.get_candidates(row, col)
                    print(f"({row + 1}, {col + 1}) :", " ".join(map(str, candidate)))

    def solution(self):
        """展示数独解"""
        print("The original Sudoku table is displayed!")
        self.cells.display()
        print("The matrix is indexed from 1 to 81 from left to right and top to bottom!")
        self.candidates_display()


if __name__ == "__main__":
    input_str = "017903600000080000900000507072010430000402070064370250701000065000030000005601720"
    """
    字符串长度不足81位报错测试：79036000000800009000005070720104300004020700643702
    字符串包含异常字符报错测试：01790360000008000090000050707201043000040207006437025070100006500003000000560172a
    其余正常测试案例：005060900000500000000807050090043078001000400840700080060204000000008000003010700
    """
    
    try:
        sudoku = Sudoku(input_str)
        sudoku.solution()
    except ValueError as err:
        print(err)
