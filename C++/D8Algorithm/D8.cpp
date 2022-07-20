#include "D8.h"

/*
* 参考：https://blog.csdn.net/qq_30357007/article/details/109385986
* DEM文件：https://surferhelp.goldensoftware.com/subsys/subsys_ASC_Arc_Info_ASCII_Grid.htm
* 测试数据：https://zhuanlan.zhihu.com/p/107759204
*/


int D8_main()
{
    const char* filename = "../../src/test1.txt";
    ifstream ifs;
    //判断文件是否打开成功
    ifs.open(filename, ios::in);
    if (!ifs.is_open()) {
        cout << "文件打开失败！" << endl;
        return 0;
    }
    //读取数据，并存储到数组当中
    string buf;
    vector < vector<int> > src;
    while (getline(ifs, buf))
    {
        vector<int> src_row;
        stringstream ss;
        ss << buf;
        int tmp;
        
        //从txt文件中提取DEM的值
        while (ss >> tmp) {
            src_row.push_back(tmp);
            if (ss.peek() == ',' || ss.peek() == ' ')
                ss.ignore();
        }
        if(src_row.size()!=0)
            src.push_back(src_row);
    }
    //D8算法
    //对DEM数据进行流向和河道提取
    int row = src.size(), col = src[0].size();
    vector<int> vector_tmp(col, 0);
    vector<vector<int>> Vector(row, vector_tmp);
    vector<int> Result_tmp(col, 0);
    vector<vector<int>> Result(row, Result_tmp);
    double Sqrt2;
    double S = 0, N = 0, E = 0, SE = 0, NE = 0, NW = 0, W = 0, SW = 0;
    Sqrt2 = sqrt(2);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            S = (i != (row - 1)) ? (src[i][j] - src[i + 1][j]) : -1;
            SE = (i != (row - 1) && j != (col - 1)) ? (src[i][j] - src[i + 1][j + 1]) / sqrt(2) : -1;
            N = (i != 0) ? (src[i][j] - src[i - 1][j]) : -1;
            E = (j != (col - 1)) ? (src[i][j] - src[i][j + 1]) : -1;
            NE = (i != 0 && j != (col - 1)) ? (src[i][j] - src[i - 1][j + 1]) / sqrt(2) : -1;
            NW = (i != 0 && j != 0) ? (src[i][j] - src[i - 1][j - 1]) / sqrt(2) : -1;
            W = (j != 0) ? (src[i][j] - src[i][j - 1]) : -1;
            SW = (i != (row - 1) && j != 0) ? (src[i][j] - src[i + 1][j - 1]) / sqrt(2) : -1;
            
            //坡降计算
            double M = 0;
            M = (M > S) ? M : S;
            M = (M > SE) ? M : SE;
            M = (M > N) ? M : N;
            M = (M > E) ? M : E;
            M = (M > NE) ? M : NE;
            M = (M > NW) ? M : NW;
            M = (M > W) ? M : W;
            M = (M > SW) ? M : SW;

            //取最大坡降
            if (M > 0) {
                if (M == S)
                {
                    Vector[i][j] = 4;
                }
                else if (M == SE)
                {
                    Vector[i][j] = 2;
                }
                else if (M == N)
                {
                    Vector[i][j] = 64;
                }
                else if (M == E)
                {
                    Vector[i][j] = 1;
                }
                else if (M == NE)
                {
                    Vector[i][j] = 128;
                }
                else if (M == NW)
                {
                    Vector[i][j] = 32;
                }
                else if (M == W)
                {
                    Vector[i][j] = 16;
                }
                else if (M == SW)
                {
                    Vector[i][j] = 8;
                }
                else
                {
                    Vector[i][j] = 0;
                }
            }
        }
    }

    //计算流向数据
    int i1 = 0, j1 = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            i1 = i, j1 = j;
            while (1)
            {
                int x = Vector[i1][j1];
                if (Vector[i1][j1] == 0 || i1 >= row || j1 >= col) {
                    break;
                }
                switch (x)
                {
                    //temp = 0
                    Vector[i1][j1] |= 0x100000;
                case 1:
                {
                    Result[i1][j1 + 1]++;
                    j1 = j1 + 1;
                    break;
                }
                case 2:
                {
                    Result[i1 + 1][j1 + 1]++;
                    i1 = i1 + 1;
                    j1 = j1 + 1;
                    break;
                }
                case 4: {
                    Result[i1 + 1][j1]++;
                    i1 = i1 + 1;
                    break;
                }
                case 8:
                {
                    Result[i1 + 1][j1 - 1]++;
                    i1 = i1 + 1;
                    j1 = j1 - 1; break;
                }
                case 16:
                {
                    Result[i1][j1 - 1]++;
                    j1 = j1 - 1; break;
                }
                case 32:
                {
                    Result[i1 - 1][j1 - 1]++;
                    i1 = i1 - 1;
                    j1 = j1 - 1; break;
                }
                case 64:
                {
                    Result[i1 - 1][j1]++;
                    i1 = i1 - 1; break;
                }
                case 128:
                {
                    Result[i1 - 1][j1 + 1]++;
                    i1 = i1 - 1;
                    j1 = j1 + 1; break;
                }
                default:
                    break;
                }
                if (Vector[i1][j1] == 0 || i1 >= row || j1 >= col) {
                    break;
                }
            }
        }
    }

    //保存流向结果
    ofstream ofs;
    ofs.open("./direction.txt", ios::out);

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++)
            ofs << Vector[i][j] << "  ";
        ofs << endl;
    }
    ofs.close();

    //保存汇流结果
    ofstream ofs1;
    ofs1.open("./river.txt", ios::out);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++)
            ofs1 << Result[i][j] << "  ";
        ofs1 << endl;
    }
    ofs1.close();


    return 0;
}
