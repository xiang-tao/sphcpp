#ifndef Vector_h
#define Vector_h
/*
此文件作用：创建一个数学中的向量，使用c++结构体和模板进行实现
结构体:重写拷贝构造函数，重载赋值"="函数
*/
#include <algorithm>
#include <cassert>
#include <cmath>
#include <initializer_list>
#include <iostream>

namespace PDECPP {
namespace AlgebraObject {

    template <typename F = double, typename I = int>
    class Vector {
        F* data; //管理向量中的数据

        void init(F val = 0.0)
        {
            data = new F[size];
            for (I i = 0; i < size; i++)
                data[i] = val;
        }

    public:
        I size; //控制向量的维度

        /*
     * 默认构造函数
     使用方式：Vector v;默认向量v为空。
     */
        Vector()
        {
            //data = NULL;
            data = nullptr;
            size = 0;
        }

        //有参构造函数，调用形式 Vector v(5,1);向量维度是5，初始化全为1.
        //若使用Vector v(5);则向量维度为5，初始化默认val = 0;
        //explicit作用是防止隐式转换，因为v=5似乎不符合一般看到向量的常识。见cppPlus p336页下面
        explicit Vector(I s, F val = 0.0)
        {
            size = s;
            init(val);
        }

        //initializer_list目的是为了初始化更加的灵活方便，参见https://blog.csdn.net/fengxinlinux/article/details/72614874
        //初始化方式：vector v = { 1, 2, 3, 4 };
        Vector(const std::initializer_list<F>& l)
        {
            //std::cout<<"初始化列表调用"<<std::endl;
            size = l.size();
            data = new F[size];
            I i = 0;
            for (auto& val : l) {
                data[i] = val;
                i++;
            }
        }

        /*
    此处重载 = 的原因是防止调用赋值符号时候由于类自身的浅拷贝是将地址一并拷贝，
    所以析构函数会释放同一个内存多次，有了这个重载，不同对象拷贝时候属性的地址就不一样了，
    因此不会释放同一个内存多次。
    注意:当使用Vector v1 = v2;等价于Vector v1(v2),这并不会调用重载的“=”函数，
    而是在调用拷贝构造函数,使用
    Vector v;
    v = v1;此处才会调用重载的“=”函数
    */
        Vector<F, I>& operator=(const Vector<F, I>& rhs)
        {
            //此处由于判断了维度是否一致问题，因此后续的过程是维度是
            //一致的，可以不用再次判断是否为空指针再用new新建内存，
            //这里没有必要这样做，但是在其他场合例如当维度不一致都可
            //以进行赋值时候就有必要判断是否为nullptr，再使用new。
            if (this->size != rhs.size) {
                std::cout << "维度不一致，不能赋值" << std::endl;
                assert(0); //终止程序
            } else {
                if (this != &rhs) {
                    //copy_n来自于STL中的算法头文件algorithm
                    std::copy_n(rhs.data, size, data);
                }
                return *this;
            }
        }

        //同时我们还要重写拷贝构造函数，防止当用户使用p(a)，即p=a，但是此处不会调用上面的重载“=”
        //函数，而是调用系统的拷贝构造函数，系统的浅拷贝对于指针会带来内存泄露问题，
        //因此要自己重新写。使用方式Vector v = v1; or Vector v(v1);
        Vector(const Vector& v)
        {
            //std::cout<<"拷贝构造调用"<<std::endl;
            this->size = v.size;
            this->data = new F[this->size];
            std::copy_n(v.data, v.size, this->data);
            // for(int i=0;i<this->size;i++)
            // {
            //      this->data[i] = v.data[i];
            // }
        }

        //析构函数，释放内存空间
        ~Vector()
        {
            if (data != nullptr) {
                delete[] data;
                data = nullptr;
            }
        }

        F norm() const
        {
            F sum = 0.0;
            for (I i = 0; i < size; i++)
                sum += data[i] * data[i];
            return std::sqrt(sum);
        }

        F max() const
        {
            F m = data[0];
            for (I i = 1; i < size; i++) {
                if (m < data[i])
                    m = data[i];
            }
            return m;
        }

        F& operator[](const I i)
        {
            //这里可能会存在较大的开销，故关闭最好，使用时候小心越界即可
            // if (i >= size || i < 0) {
            //     std::cout << "array out of bounds" << std::endl;
            //     assert(0);
            // }
            return data[i];
        }

        //这里之所以重载了两个[],这里加了const目的见cppPlus p359页下面介绍
        const F& operator[](const I i) const
        {
            //这里可能会存在较大的开销，故关闭最好，使用时候小心越界即可
            // if (i >= size || i < 0) {
            //     std::cout << "array out of bounds" << std::endl;
            //     assert(0);
            // }
            return data[i];
        }
    };

    //下面是一些重载运算符的函数，之所以返回的不是引用，原因是返回的变量是一个函数
    //临时变量，返回引用不能够返回临时变量。
    //重载==与!=
    template <typename F, typename I>
    int operator==(const Vector<F, I>& v0,
        const Vector<F, I>& v1)
    {
        int as = 1;
        if (&v0 != &v1) {
            int n1 = v0.size;
            int n2 = v1.size;
            if (n1 != n2) {
                std::cout << "维度不一致，无法比较相等" << std::endl;
                assert(0);
            } else {
                for (int i = 0; i < n1; i++) {
                    if (v0[i] != v1[i]) {
                        as = 0;
                        break;
                    }
                }
            }
        }
        return as;
    }
    template <typename F, typename I>
    int operator!=(const Vector<F, I>& v0,
        const Vector<F, I>& v1)
    {
        int as = 1;
        if (v0 == v1) {
            as = 0;
        }
        return as;
    }

    //重载向量减法
    template <typename F, typename I>
    inline Vector<F, I> operator-(const Vector<F, I>& v0,
        const Vector<F, I>& v1)
    {
        Vector<F, I> r(v0.size);
        for (auto i = 0; i < v0.size; i++) {
            r[i] = v0[i] - v1[i];
        }
        return r;
    }

    template <typename F, typename I>
    inline Vector<F, I> operator-=(Vector<F, I>& v0,
        const Vector<F, I>& v1)
    {
        v0 = v0 - v1;
        return v0;
    }

    //重载向量加法
    template <typename F, typename I>
    inline Vector<F, I> operator+(const Vector<F, I>& v0,
        const Vector<F, I>& v1)
    {
        Vector<F, I> r(v0.size);
        for (auto i = 0; i < v0.size; i++) {
            r[i] = v0[i] + v1[i];
        }
        return r;
    }

    template <typename F, typename I>
    inline Vector<F, I> operator+=(Vector<F, I>& v0,
        const Vector<F, I>& v1)
    {
        v0 = v0 + v1;
        return v0;
    }

    //重载向量乘法，即数学中的点乘，对应相乘相加，相当于计算内积
    template <typename F, typename I>
    inline double operator*(const Vector<F, I>& v0,
        const Vector<F, I>& v1)
    {
        double r = 0;
        for (auto i = 0; i < v0.size; i++) {
            r += v0[i] * v1[i];
        }
        return r;
    }

    //重载数字与向量乘法，数字在左边
    template <typename F, typename I>
    inline Vector<F, I> operator*(const double& v0,
        const Vector<F, I>& v1)
    {
        Vector<F, I> r(v1.size);
        for (auto i = 0; i < v1.size; i++) {
            r[i] = v0 * v1[i];
        }
        return r;
    }

    //重载数字与向量乘法，数字在右边
    template <typename F, typename I>
    inline Vector<F, I> operator*(const Vector<F, I>& v1,
        const double& v0)
    {
        Vector<F, I> r(v1.size);
        for (auto i = 0; i < v1.size; i++) {
            r[i] = v0 * v1[i];
        }
        return r;
    }

    template <typename F, typename I>
    inline Vector<F, I> operator/(const Vector<F, I>& v1,
        const double& v0)
    {
        Vector<F, I> r(v1.size);
        for (auto i = 0; i < v1.size; i++) {
            r[i] = v1[i] / v0;
        }
        return r;
    }

    //重载左移运算符，实现向量输出自由
    template <typename F, typename I>
    std::ostream& operator<<(std::ostream& os, const Vector<F, I>& v)
    {
        std::cout << "Vector(" << v.size << ")" << std::endl;

        for (I i = 0; i < v.size; i++) {
            os << v[i] << " ";
        }
        os << std::endl;
        return os;
    }

} // end of namespace AlgebraObject

} // end of namespace PDECPP
#endif // end of Vector_h
