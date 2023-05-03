#ifndef linalg_h
#define linalg_h
#include <iostream>
#include <math.h>

namespace PDECPP {
namespace AlgebraAlgrithom {

    //jacobi迭代
    template <typename Matrix, typename Vector>
    void jacobi(const Matrix& A, const Vector& b, Vector& x,
        int times = 5000, double tol = 1e-6)
    {
        int size = x.size;
        double d;
        Vector x1(size);
        for (int i = 0; i < times; i++) {
            for (int j = 0; j < size; j++) {
                x1[j] = b[j];
                for (int k = 0; k < size; k++) {
                    if (k == j)
                        d = A[j][j];
                    else
                        x1[j] -= A[j][k] * x[k];
                }
                x1[j] = x1[j] / d;
            }
            x = x1;
            auto err = b - A * x;
            auto err_norm = err.norm();
            if (err_norm < tol) {
                // std::cout << "jco-successful" << std::endl;
                // std::cout << i << std::endl;
                break;
            }
        }
    }

    //GS迭代
    template <typename Matrix, typename Vector>
    void GS(const Matrix& A, const Vector& b, Vector& x,
        int times = 5000, double tol = 1e-6)
    {
        int size = x.size;
        double d;
        Vector x1(size);
        for (int i = 0; i < times; i++) {
            for (int j = 0; j < size; j++) {
                x1[j] = b[j];
                for (int k = 0; k < size; k++) {
                    if (k == j)
                        d = A[j][j];
                    else if (k < j)
                        x1[j] -= A[j][k] * x1[k];
                    else
                        x1[j] -= A[j][k] * x[k];
                }
                x1[j] = x1[j] / d;
            }
            x = x1;
            auto err = b - A * x;
            auto err_norm = err.norm();
            if (err_norm < tol) {
                // std::cout << "GS-successful" << std::endl;
                // std::cout << i << std::endl;
                break;
            }
        }
    }

    //CG迭代,b作为x0开始
    template <typename Matrix, typename Vector>
    void CG(const Matrix& A, const Vector& b, Vector& x,
        int times = 500, double tol = 1e-10)
    {
        int size = x.size;
        x = b; //b作为x0开始计算
        double rho = 0.0, rho0 = 1.0, um = 0.0, cci = 0;
        Vector r = b - A * b;
        Vector p(size);
        Vector q(size);
        double beta = r.norm();
        if (beta < tol) {
            times = 0; //停止后面的循环计算
        }
        for (int m = 1; m < times; m++) {
            rho = r * r;
            if (m > 1) {
                um = rho / rho0;
                p = r + um * p;
            } else {
                p = r;
            }
            q = A * p;
            cci = rho / (p * q);
            x = x + cci * p;
            r = r - cci * q;
            beta = r.norm();
            if (beta < tol) {
                std::cout << "CG迭代了" << m << "次" << std::endl;
                break;
            }
            rho0 = rho;
        }
    }

    template <typename Matrix>
    void LU(const Matrix& A, Matrix& L, Matrix& U)
    {
        int n = A.shape[0];
        Matrix B = A;
        for (int i = 0; i < n; i++) {
            U[0][i] = B[0][i];
        }
        for (int k = 0; k < n - 1; k++) {
            for (int i = k + 1; i < n; i++) {
                L[i][k] = B[i][k] / B[k][k];
            }
            for (int i = k + 1; i < n; i++) {
                for (int j = k + 1; j < n; j++) {
                    B[i][j] = B[i][j] - L[i][k] * U[k][j];
                }
            }
            for (int j = k + 1; j < n; j++) {
                U[k + 1][j] = B[k + 1][j];
            }
        }
    }

    template <typename Matrix>
    void Cholesky(const Matrix& A, Matrix& L)
    {
        int n = A.shape[0];
        int sum = 0;
        int sum1 = 0;
        for (int j = 0; j < n; j++) {
            sum = 0;
            for (int k = 0; k < j; k++) {
                sum += L[j][k] * L[j][k];
            }
            L[j][j] = sqrt(A[j][j] - sum);
            for (int i = j + 1; i < n; i++) {
                sum1 = 0;
                for (int k = 0; k < j; k++)
                    sum1 += L[i][k] * L[j][k];
                L[i][j] = (A[i][j] - sum1) / L[j][j];
            }
        }
    }

    /*
     *请注意，下面的gm_col和gm_row分别表示获取矩阵的某列和某行数据，但是模板中使用了Matrix和Vector
     *两个数据类型，如果在函数的参数列表中，例如gm_col中只使用了Matrix数据类型，而Vector类型没有
     只是出现在了返回类型中时，直接使用gm_col（A，r），系统会报错，无法找到该函数，原因是由于Vector
     未出现在函数参数列表中时，直接使用gm_col(A,r)他无法自动推导出Vector数据类型，因此需要告诉他的
     函数模板类型，即正确的使用方式是gm_col<matrix,Vector>(A,r)
     * */
    //获取矩阵某一列
    template <typename Matrix, typename Vector>
    Vector gm_col(const Matrix& A, int r)
    {
        int row = A.shape[0];
        int col = A.shape[1];
        Vector v(row);
        for (int i = 0; i < row; i++) {
            if (r >= col) {
                std::cout << "列标越界" << std::endl;
                break;
            } else {
                v[i] = A[i][r];
            }
        }
        return v;
    }

    //获取矩阵某一行
    template <typename Matrix, typename Vector>
    Vector gm_row(const Matrix& A, int r)
    {
        int row = A.shape[0];
        int col = A.shape[1];
        Vector v(col);
        for (int i = 0; i < col; i++) {
            if (r >= row) {
                std::cout << "行标越界" << std::endl;
                break;
            } else {
                v[i] = A[r][i];
            }
        }
        return v;
    }

    //获取矩阵某一列的一部分
    template <typename Matrix, typename Vector>
    Vector gm_col_part(const Matrix& A, int r, int l)
    {
        int row = A.shape[0];
        int col = A.shape[1];
        Vector v(row - l);
        for (int i = l; i < row; i++) {
            if (r >= col) {
                std::cout << "列标越界" << std::endl;
                break;
            } else {
                v[i - l] = A[i][r];
            }
        }
        return v;
    }

    //获取矩阵某一行的一部分
    template <typename Matrix, typename Vector>
    Vector gm_row_part(const Matrix& A, int r, int l)
    {
        int row = A.shape[0];
        int col = A.shape[1];
        Vector v(col - l);
        for (int i = l; i < col; i++) {
            if (r >= row) {
                std::cout << "行标越界" << std::endl;
                break;
            } else {
                v[i - l] = A[r][i];
            }
        }
        return v;
    }

    //将一个维度低的方阵从右下角开始填充单位矩阵
    template <typename Matrix>
    Matrix fill_I_H(const Matrix& I, const Matrix& h)
    {
        int rmi = I.shape[0];
        int lmi = I.shape[1];
        Matrix m = I;
        int rmh = h.shape[0];
        int lmh = h.shape[1];
        int r = rmi - rmh;
        int l = lmi - lmh;
        for (int i = r; i < rmi; i++) {
            for (int j = l; j < lmi; j++) {
                m[i][j] = h[i - r][j - l];
            }
        }
        return m;
    }

    //计算向量的内积
    template <typename Vector>
    double inner(const Vector& v, const Vector& u)
    {
        int n1 = v.size;
        int n2 = u.size;
        double inn = 0;
        if (n1 == n2) {
            for (int i = 0; i < n1; i++) {
                inn += v[i] * u[i];
            }
            return inn;
        } else {
            std::cout << "error,维度不一致无法内积计算" << std::endl;
            return 0;
        }
    }

    //计算列向量与行向量相乘=矩阵
    //get:m=vv*
    template <typename Matrix, typename Vector>
    Matrix vv(Vector v1, Vector v2)
    {
        int n = v1.size;
        int n1 = v2.size;
        Matrix m(n, n);
        if (n1 != n) {
            std::cout << "维度不一致无法计算向量与向量转置乘积" << std::endl;
            return m;
        } else {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    m[i][j] = v1[i] * v2[j];
                }
            }
            return m;
        }
    }

    //使用修正的施密特正交化计算A=QR分解，目前仅仅适用计算A是列满秩（含非奇异的方正），因为对于
    //奇异的矩阵，对于扩展基还未实现该功能，理论详细见矩阵计算讲义P82-83页。
    //注意这里跟上面一样要使用qr_mgs<Matrix,Vector>(A,Q,R)才不会报错
    template <typename Matrix, typename Vector>
    void qr_mgs(const Matrix& A, Matrix& Q, Matrix& R)
    {
        int n1 = A.shape[0];
        int n2 = A.shape[1];
        Vector zeros(n1);
        Vector a = gm_col<Matrix, Vector>(A, 0);
        Vector qk(n1);
        Vector qi(n1);
        if (a != zeros) {
            R[0][0] = sqrt(inner(a, a));
            for (int i = 0; i < n1; i++) {
                Q[i][0] = A[i][0] / R[0][0];
            }
        }
        for (int k = 1; k < n2; k++) {
            a = gm_col<Matrix, Vector>(A, k);
            qk = a;
            for (int i = 0; i < k; i++) {
                qi = gm_col<Matrix, Vector>(Q, i);
                R[i][k] = inner(qi, qk);
                qk -= R[i][k] * qi;
            }
            if (qk != zeros) {
                R[k][k] = sqrt(inner(qk, qk));
                qk = qk / R[k][k];
            }
            for (int i = 0; i < n1; i++) {
                Q[i][k] = qk[i];
            }
        }
    }

    //计算householder向量，理论P76-78.
    //H=I-2/|v|**2 vv*   do:Hx=|x|e1, e1=(1,0,0.....)
    template <typename Vector>
    Vector get_hhv(const Vector& x)
    {
        Vector v = x;
        int n = x.size;
        double sigm = 0;
        double alpha = 0;
        for (int i = 1; i < n; i++) {
            sigm += x[i] * x[i];
        }
        if (sigm == 0) {
            if (x[0] < 0) {
                v[0] = 2 * x[0];
            } else {
                v[0] = 0;
            }
        } else {
            alpha = sqrt(x[0] * x[0] + sigm);
            if (x[0] < 0) {
                v[0] = x[0] - alpha;
            } else {
                v[0] = -sigm / (x[0] + alpha);
            }
        }
        return v;
    }

    //计算householder矩阵
    template <typename Matrix, typename Vector>
    Matrix get_hhH(const Vector& x)
    {
        Vector v = x;
        int n = x.size;
        Matrix H(n, n);
        Matrix I(n, n);
        I.fill_diag(1);
        double beta = 0;
        double sigm = 0;
        double alpha = 0;
        for (int i = 1; i < n; i++) {
            sigm += x[i] * x[i];
        }
        if (sigm == 0) {
            if (x[0] < 0) {
                v[0] = 2 * x[0];
                beta = 2 / (v[0] * v[0]);
            } else {
                v[0] = 0;
                beta = 0;
            }
        } else {
            alpha = sqrt(x[0] * x[0] + sigm);
            if (x[0] < 0) {
                v[0] = x[0] - alpha;
            } else {
                v[0] = -sigm / (x[0] + alpha);
            }
            beta = 2 / (v[0] * v[0] + sigm);
        }
        H = I - beta * vv<Matrix>(v, v);
        return H;
    }

    //基于householder的qr分解,这里仅对方阵成立，即m=n情形，其余情况未做测试
    template <typename Matrix, typename Vector>
    void qr_house(const Matrix& A, Matrix& Q, Matrix& R)
    {
        int r = A.shape[0];
        int l = A.shape[1];
        Matrix I(r, r);
        I.fill_diag(1);
        R = A;
        Q = I;
        for (int i = 0; i < l - 1; i++) {
            Vector v = gm_col_part<Matrix, Vector>(R, i, i);
            Matrix h = get_hhH<Matrix, Vector>(v);
            Matrix H = fill_I_H(I, h);
            R = H * R;
            Q = Q * H;
        }
        //注意，在householder变换过程中只进行了n-1次，即A的最后一列向量未进行变换，原因是最后一列不用变换就已经是一个上
        //三角矩阵了，但是QR分解要求上三角阵的主对角线为正数，如果不对最后一列的最后一个元素（即主对角线最后一个元素）
        //进行正负性判断则可能得到主对角元素的最后一个为负数，因此需要进行判断。判断就是如果最后一个主对角元素为负
        //则将R的最后一行都添加一个负号，从而Q的最后一列也要对应加上一个负号。
        if (R[r - 1][l - 1] < 0) {
            for (int i = 0; i < r; i++) {
                R[r - 1][i] = -R[r - 1][i];
                Q[i][l - 1] = -Q[i][l - 1];
            }
        }
    }

    //获取givens矩阵
    template <typename Matrix>
    Matrix get_givens(const int w, const int r, const int l, const double c, const double s)
    {
        Matrix G(w, w);
        G.fill_diag(1);
        G[r][r] = c;
        G[l][l] = c;
        G[r][l] = -s;
        G[l][r] = s;
        return G;
    }

    int sign(int num)
    {
        int a = 0;
        if (num > 0)
            a = 1;
        if (num == 0)
            a = 0;
        if (num < 0)
            a = -1;
        return a;
    }

    //Givens变换,这里也是只对非奇异的方阵A进行了QR分解，对奇异或者不是方阵情形未做测试.
    template <typename Matrix>
    void qr_givens(const Matrix& A, Matrix& Q, Matrix& R)
    {
        int r = A.shape[0];
        int l = A.shape[1];
        Matrix G(r, l);
        double c = 0, s = 0, tau = 0;
        Matrix I(r, l);
        I.fill_diag(1);
        R = A;
        Q = I;
        double a = 0, b = 0;
        for (int i = 0; i < l - 1; i++) {
            for (int j = i + 1; j < r; j++) {
                a = R[i][i];
                b = R[j][i];
                if (b == 0) {
                    if (a >= 0) {
                        c = 1, s = 0;
                        G = get_givens<Matrix>(r, j, i, c, s);
                        R = G * R;
                        Q = G * Q;
                    } else {
                        c = -1, s = 0;
                        G = get_givens<Matrix>(r, j, i, c, s);
                        R = G * R;
                        Q = G * Q;
                    }
                } else {
                    if (abs(b) > abs(a)) {
                        tau = a / b, s = sign(b) / sqrt(1 + tau * tau), c = s * tau;
                        G = get_givens<Matrix>(r, j, i, c, s);
                        R = G * R;
                        Q = G * Q;
                    } else {
                        tau = b / a, c = sign(a) / sqrt(1 + tau * tau), s = c * tau;
                        G = get_givens<Matrix>(r, j, i, c, s);
                        R = G * R;
                        Q = G * Q;
                    }
                }
            }
        }
        Q = Q.transpose();

        //注意，givens与householder变换一样，即A的最后一列向量未进行变换，原因是最后一列不用变换就已经是一个上
        //三角矩阵了，但是QR分解要求上三角阵的主对角线为正数，如果不对最后一列的最后一个元素（即主对角线最后一个元素）
        //进行正负性判断则可能得到主对角元素的最后一个为负数，因此需要进行判断。判断就是如果最后一个主对角元素为负
        //则将R的最后一行都添加一个负号，从而Q的最后一列也要对应加上一个负号。
        if (R[r - 1][l - 1] < 0) {
            for (int i = 0; i < r; i++) {
                R[r - 1][i] = -R[r - 1][i];
                Q[i][l - 1] = -Q[i][l - 1];
            }
        }
    }

    //上三角阵方程求解（QR）中R是一个上三角阵。
    template <typename Matrix, typename Vector>
    void solve_ssj(const Matrix& A, Vector& x, Vector& b)
    {
        int n = x.size;
        x[n - 1] = b[n - 1] / A[n - 1][n - 1];
        for (int i = n - 2; i > -1; i--) {
            for (int j = i + 1; j < n; j++) {
                b[i] = b[i] - A[i][j] * x[j];
            }
            x[i] = b[i] / A[i][i];
        }
    }

} // end of PDECPP
} //end of AlgebraAlgrithom
#endif // end of linalg_h
