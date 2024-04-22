#pragma once
#include "head.h"
#include <fstream>
#include <iomanip> // 包含格式控制符相关的头文件
#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;
void writevtk(str* vari, const int number, const int cc = 0, const int gate = 1)
{
    int nn;
    if (gate == 1) {
        nn = vari->n_gate;
    } else {
        nn = 0;
    }
    // cout << "nn=" << nn << endl;

    ofstream dataFile;
    string name = "PART";
    string srffix = ".vtu";
    const int desiredSize = 8; // 8是固定大小
    // 使用 std::to_string 将数字转换为字符串
    string numberString = to_string(number);
    // 计算需要补足的零的个数
    int zerosToAdd = desiredSize - name.length() - numberString.length();
    // 指定文件夹路径，文件可以不存在，系统自动创建，但是文件夹必须提前创建，否则报错
    string folderPath = "vtu/"; //路径为相对路径

    // 构建新的字符串
    std::string resultString = folderPath + name + std::string(zerosToAdd, '0') + numberString + srffix;
    dataFile.open(resultString, ofstream::app);
    fstream file(resultString, ios::out);

    // 设置输出格式，确保整数和小数部分宽度一致，不够的用 '0' 填充
    dataFile << fixed << setprecision(8) << setw(16) << setfill('0');

    dataFile << "<?xml version=\"1.0\"?>" << endl;
    dataFile << "<VTKFile type= \"UnstructuredGrid\"  version= \"0.1\"  byte_order= \"BigEndian\">" << endl;
    dataFile << "<UnstructuredGrid>" << endl;
    dataFile << "<Piece NumberOfPoints=\"" << vari->ntotal + vari->nvirt + nn << "\" NumberOfCells=\"" << vari->ntotal + vari->nvirt + nn << "\">" << endl;

    dataFile << "<PointData Scalars=\"Pressure\" Vectors=\"Velocity\">" << endl;
    dataFile << "<DataArray type=\"Float32\" Name=\"Pressures\" format=\"ascii\">" << endl;
    for (int i = 0; i < vari->ntotal + vari->nvirt + nn; i++) {
        dataFile << "      " << vari->p[i] << endl;
    }
    dataFile << "</DataArray>" << endl;
    dataFile << "<DataArray type=\"Float32\" Name=\"Density\" format=\"ascii\">" << endl;
    for (int i = 0; i < vari->ntotal + vari->nvirt + nn; i++) {
        dataFile << "      " << vari->rho[i] << endl;
    }
    dataFile << "</DataArray>" << endl;
    dataFile << "<DataArray type=\"Float32\" Name=\"u-Velocity\" format=\"ascii\">" << endl;
    for (int i = 0; i < vari->ntotal + vari->nvirt + nn; i++) {
        dataFile << "      " << vari->v[0][i] << endl;
    }
    dataFile << "</DataArray>" << endl;
    dataFile << "<DataArray type=\"Float32\" Name=\"w-Velocity\" format=\"ascii\">" << endl;
    for (int i = 0; i < vari->ntotal + vari->nvirt + nn; i++) {
        dataFile << "      " << vari->v[1][i] << endl;
    }
    dataFile << "</DataArray>" << endl;
    dataFile << "<DataArray type=\"Float32\" Name=\"Scalarplot\" format=\"ascii\">" << endl;
    for (int i = 0; i < vari->ntotal + vari->nvirt + nn; i++) {
        dataFile << vari->itype[i] << endl;
    }
    dataFile << "</DataArray>" << endl;
    dataFile << "</PointData>" << endl;
    dataFile << "<Points>" << endl;
    dataFile << "<DataArray type=\"Float32\" NumberOfComponents=\"3\" format=\"ascii\">" << endl;
    if (cc == 1) {
        if (dim == 2) {
            for (int i = 0; i < vari->ntotal + vari->nvirt + nn; i++) {
                dataFile << "      " << vari->x[0][i] << "      " << 0.0 << "      " << vari->x[1][i] << endl;
            }
        }
        if (dim == 3) {
            for (int i = 0; i < vari->ntotal + vari->nvirt + nn; i++) {
                dataFile << vari->x[0][i] << " " << vari->x[1][i] << " " << vari->x[2][i] << endl;
            }
        }
    } else {
        if (dim == 2) {
            for (int i = 0; i < vari->ntotal + nn; i++) {
                dataFile << vari->x[0][i] << " " << vari->x[1][i] << endl;
            }
        }
        if (dim == 3) {
            for (int i = 0; i < vari->ntotal + nn; i++) {
                dataFile << vari->x[0][i] << " " << vari->x[1][i] << " " << vari->x[2][i] << endl;
            }
        }
    }
    dataFile << "</DataArray>" << endl;
    dataFile << "</Points>" << endl;
    dataFile << "<Cells>" << endl;
    dataFile << "<DataArray type=\"Int32\" Name=\"connectivity\" format=\"ascii\">" << endl;
    if (cc == 1) {
        for (int i = 0; i < vari->ntotal + vari->nvirt + nn; i++) {
            dataFile << i << endl;
        }
    } else {
        for (int i = 0; i < vari->ntotal + nn; i++) {
            dataFile << i << endl;
        }
    }
    dataFile << "</DataArray>" << endl;
    dataFile << "<DataArray type=\"Int32\" Name=\"offsets\" format=\"ascii\">" << endl;
    if (cc == 1) {
        for (int i = 0; i < vari->ntotal + vari->nvirt + nn; i++) {
            dataFile << i + 1 << endl;
        }
    } else {
        for (int i = 0; i < vari->ntotal + nn; i++) {
            dataFile << i + 1 << endl;
        }
    }
    dataFile << "</DataArray>" << endl;
    dataFile << "<DataArray type=\"Int32\" Name=\"types\" format=\"ascii\">" << endl;
    if (cc == 1) {
        for (int i = 0; i < vari->ntotal + vari->nvirt + nn; i++) {
            dataFile << 1 << endl;
        }
    } else {
        for (int i = 0; i < vari->ntotal + nn; i++) {
            dataFile << 1 << endl;
        }
    }
    dataFile << "</DataArray>" << endl;
    dataFile << "</Cells>" << endl;
    dataFile << "</Piece>" << endl;
    dataFile << "</UnstructuredGrid>" << endl;
    dataFile << "</VTKFile>" << endl;
    dataFile.close();
}
