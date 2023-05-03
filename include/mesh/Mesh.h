#pragma once
#include "algebra/Algebra_kernel.h"
#include <iostream>
using namespace std;

namespace fem1 {

class IntervalMesh {
public:
    IntervalMesh();
    IntervalMesh(int left, int right, int N);

private:
    int m_left;
    int m_right;
    int m_N;
};

IntervalMesh::IntervalMesh()
{
    m_left = 0;
    m_right = 0;
    m_N = 0;
}
IntervalMesh::IntervalMesh(int left, int right, int N)
{
    m_left = left;
    m_right = right;
    m_N = N;
}

}
