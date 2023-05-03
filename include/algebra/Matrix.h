#ifndef Matrix_h
#define Matrix_h

#include <cassert>
#include <cmath>

#include <initializer_list>
#include <iostream>
#include <string>

namespace PDECPP {
namespace AlgebraObject {

    template <typename F = double, typename I = int>
    class Matrix {
        // typedef F Float;
        // typedef I Int;
        F** data;

    public:
        I shape[2]; //shape[0]:row，shape[1]:columns

        // static std::string format;

        /*
     * 默认构造函数
     */
        Matrix()
        {
            //std::cout<<"无参构造函数调用"<<std::endl;
            data = nullptr;
            shape[0] = shape[1] = 0;
        }

        Matrix(I nr, I nc, F val = 0.0)
        {
            //std::cout<<"有参构造函数调用"<<std::endl;
            shape[0] = nr;
            shape[1] = nc;
            data = new F*[shape[0]];
            for (I i = 0; i < shape[0]; i++) {
                data[i] = new F[shape[1]];
                for (I j = 0; j < shape[1]; j++)
                    data[i][j] = val;
            }
        }

        Matrix<F, I>& operator=(const Matrix<F, I>& rhs)
        {
            if (this->shape[0] != rhs.shape[0] || this->shape[1] != rhs.shape[1]) {
                std::cout << "维度不一致，不能够赋值" << std::endl;
                assert(0);
            }
            if (this != &rhs) {
                for (I i = 0; i < shape[0]; i++) {
                    for (I j = 0; j < shape[1]; j++)
                        data[i][j] = rhs.data[i][j];
                }
            }
            return *this;
        }

        //拷贝构造函数
        Matrix(const Matrix<F, I>& rhs)
        {
            this->shape[0] = rhs.shape[0];
            this->shape[1] = rhs.shape[1];

            data = new F*[shape[0]];
            for (I i = 0; i < shape[0]; i++) {
                data[i] = new F[shape[1]];
                for (I j = 0; j < shape[1]; j++)
                    this->data[i][j] = rhs.data[i][j];
            }
        }

        Matrix(const std::initializer_list<std::initializer_list<F>>& l)
        {
            shape[0] = l.size();
            shape[1] = l.begin()->size();

            data = new F*[shape[0]];
            I i = 0;
            for (auto& row : l) {
                data[i] = new F[shape[1]];
                I j = 0;
                for (auto& val : row) {
                    data[i][j] = val;
                    j++;
                }
                i++;
            }
        }

        /*
     *
     * Notes
     * -----
     *  填充矩阵的对角线元素, 为一固定的值 val.
     *
     *  目前假设矩阵是方阵
     *
     */
        void fill_diag(const F val, const I diag = 0)
        {
            I i = 0;
            I j = 0;

            if (diag >= 0) {
                j = diag;
                for (; j < shape[1]; i++, j++) {
                    data[i][j] = val;
                }
            } else {
                i = std::abs(diag);
                for (; i < shape[0]; i++, j++) {
                    data[i][j] = val;
                }
            }
        }

        void fill_diag(const F val[], const I diag = 0)
        {
            I i = 0;
            I j = 0;

            if (diag >= 0) {
                j = diag;
                for (; j < shape[1]; i++, j++) {
                    data[i][j] = val[i];
                }
            } else {
                i = std::abs(diag);
                for (; i < shape[0]; i++, j++) {
                    data[i][j] = val[i];
                }
            }
        }

        /*
         *Describe:
         用于调整矩阵形状
         nc 行
         nr 列
         * */
        Matrix<F, I> reshape(I nc, I nr)
        {
            if (nr == -1) {
                if (shape[0] * shape[1] % nc == 0) {
                    nr = shape[0] * shape[1] / nc;
                    Matrix<F, I> m(nc, nr);
                    this->fill_reshape(m);
                    return m;
                } else {
                    std::cout << "无法重新组合形状" << std::endl;
                    assert(0);
                }
            } else if (nc == -1) {
                if (shape[0] * shape[1] % nr == 0) {
                    nc = shape[0] * shape[1] / nr;
                    Matrix<F, I> m(nc, nr);
                    this->fill_reshape(m);
                    return m;
                } else {
                    std::cout << "无法重新组合形状" << std::endl;
                    assert(0);
                }
            } else {
                if (nc * nr != shape[0] * shape[1]) {
                    std::cout << "无法重新组合形状" << std::endl;
                    assert(0);
                } else {
                    Matrix<F, I> m(nc, nr);
                    this->fill_reshape(m);
                    return m;
                }
            }
        }

        ~Matrix() noexcept
        {
            //std::cout<<"析构函数调用"<<std::endl;
            for (int i = 0; i < shape[0]; i++) {
                if (data[i] != nullptr) {
                    delete[] data[i];
                    data[i] = nullptr;
                }
            }
            if (data != nullptr) {
                delete[] data;
                data = nullptr;
            }
        }

        F& operator()(const I i, const I j)
        {
            return data[i][j];
        }

        const F& operator()(const I i, const I j) const
        {
            return data[i][j];
        }

        F* operator[](const I i)
        {
            return data[i];
        }

        const F* operator[](const I i) const
        {
            return data[i];
        }

        /*
         *Describe
         将函数的行列进行交换
         * */
        Matrix<F, I> transpose()
        {
            //std::cout<<"转置函数调用"<<std::endl;
            I row = shape[0];
            I col = shape[1];
            Matrix<F, I> arr(col, row);
            for (I i = 0; i < row; i++) {
                for (I j = 0; j < col; j++)
                    arr[j][i] = this->data[i][j];
            }
            return arr;
        }

    private:
        /*
         *Describe:
         当外界调用reshape函数时候，使用此函数讲调用对象的值填入到返回的矩阵中
         * */
        void fill_reshape(Matrix<F, I>& m2) const
        {
            I nc = m2.shape[0];
            I nr = m2.shape[1];
            I k1 = 0;
            I k2 = 0;
            for (I i = 0; i < nc; i++)
                for (I j = 0; j < nr; j++) {
                    m2[i][j] = this->data[k1][k2];
                    k2++;
                    if (k2 == this->shape[1]) {
                        k1++;
                        k2 = 0;
                    }
                }
        }
    };

    template <typename F, typename I>
    int operator==(const Matrix<F, I>& m0,
        const Matrix<F, I>& m1)
    {
        int as = 1;
        if (&m0 != &m1) {
            int n1 = m0.shape[0];
            int n2 = m0.shape[1];
            int n3 = m1.shape[0];
            int n4 = m1.shape[1];
            if (n1 != n3 || n2 != n4) {
                std::cout << "维度不一致，无法比较相等" << std::endl;
                assert(0);
            } else {
                for (int i = 0; i < n1; i++) {
                    for (int j = 0; j < n2; j++) {
                        if (m0[i][j] != m1[i][j]) {
                            as = 0;
                            break;
                        }
                    }
                }
            }
        }
        return as;
    }

    template <typename F, typename I>
    int operator!=(const Matrix<F, I>& m0,
        const Matrix<F, I>& m1)
    {
        int as = 1;
        if (m0 == m1) {
            as = 0;
        }
        return as;
    }
    //重载矩阵的乘法
    template <typename F, typename I>
    inline Matrix<F, I> operator*(const Matrix<F, I>& m0,
        const Matrix<F, I>& m1)
    {
        auto nr = m0.shape[0];
        auto nc = m1.shape[1];
        auto n = m0.shape[1];
        Matrix<F, I> c(nr, nc);
        for (auto i = 0; i < nr; i++) {
            for (auto j = 0; j < nc; j++) {
                for (auto k = 0; k < n; k++)
                    c[i][j] += m0[i][k] * m1[k][j];
            }
        }
        return c;
    }

    //重载矩阵的减法
    template <typename F, typename I>
    inline Matrix<F, I> operator-(const Matrix<F, I>& m0,
        const Matrix<F, I>& m1)
    {
        auto nr = m0.shape[0];
        auto nc = m0.shape[1];

        Matrix<F, I> c(nr, nc);
        for (auto i = 0; i < nr; i++) {
            for (auto j = 0; j < nc; j++) {
                c[i][j] = m0[i][j] - m1[i][j];
            }
        }
        return c;
    }

    //实现-A，即矩阵的相反数
    template <typename F, typename I>
    inline Matrix<F, I> operator-(const Matrix<F, I>& m0)
    {
        auto nr = m0.shape[0];
        auto nc = m0.shape[1];

        Matrix<F, I> c(nr, nc);
        for (auto i = 0; i < nr; i++) {
            for (auto j = 0; j < nc; j++) {
                c[i][j] = -m0[i][j];
            }
        }
        return c;
    }
    //重载矩阵的加法
    template <typename F, typename I>
    inline Matrix<F, I> operator+(const Matrix<F, I>& m0,
        const Matrix<F, I>& m1)
    {
        auto nr = m0.shape[0];
        auto nc = m0.shape[1];

        Matrix<F, I> c(nr, nc);
        for (auto i = 0; i < nr; i++) {
            for (auto j = 0; j < nc; j++) {
                c[i][j] = m0[i][j] + m1[i][j];
            }
        }
        return c;
    }

    //重载矩阵的数乘，数在左边
    template <typename F, typename I>
    inline Matrix<F, I> operator*(const double& m0,
        const Matrix<F, I>& m1)
    {
        // auto nr = m1.shape[0];
        // auto nc = m1.shape[1];
        //
        // Matrix<F, I> c(nr, nc);
        // for (auto i = 0; i < nr; i++) {
        //     for (auto j = 0; j < nc; j++) {
        //         c[i][j] = m0 * m1[i][j];
        //     }
        // }
        // return c;
        return m1 * m0;
    }

    //重载矩阵的数乘，数在右边
    template <typename F, typename I>
    inline Matrix<F, I> operator*(const Matrix<F, I>& m1,
        const double& m0)
    {
        auto nr = m1.shape[0];
        auto nc = m1.shape[1];

        Matrix<F, I> c(nr, nc);
        for (auto i = 0; i < nr; i++) {
            for (auto j = 0; j < nc; j++) {
                c[i][j] = m0 * m1[i][j];
            }
        }
        return c;
    }

    //重载矩阵乘向量
    template <typename F, typename I, typename Vector>
    inline Vector operator*(const Matrix<F, I>& m1,
        const Vector& v0)
    {
        auto nr = m1.shape[0];
        auto nc = v0.size;

        Vector c(nr);
        for (auto i = 0; i < nr; i++) {
            for (auto j = 0; j < nc; j++) {
                c[i] += m1[i][j] * v0[j];
            }
        }
        return c;
    }

    template <typename F, typename I>
    std::ostream& operator<<(std::ostream& os, const Matrix<F, I>& m)
    {
        std::cout << "Matrix(" << m.shape[0] << ","
                  << m.shape[1] << "):" << std::endl;
        for (I i = 0; i < m.shape[0]; i++) {
            for (I j = 0; j < m.shape[1]; j++) {
                os << m[i][j] << " ";
            }
            os << "\n";
        }
        return os;
    }

} // end of namespace AlgebraObject

} // end of namespace PDECPP
#endif // end of Matrix_h
