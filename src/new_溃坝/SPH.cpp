#include "ac.cpp"
#include "cellij.cpp"
#include "check_limits.cpp"
#include "correct.cpp"
#include "divide.cpp"
#include "equation_of_state.cpp"
#include "getdata.cpp"
#include "ini_divide.cpp"
#include "input.cpp"
#include "keep_list.cpp"
#include "kernel.cpp"
#include "kernel_correction.cpp"
#include "particle.cpp"
#include "self.cpp"
#include "single_step.cpp"
#include "variable_time_step.cpp"
#include "virt_part.cpp"
#include "viscosity.cpp"
#include "writevtk.cpp"
#include <iostream>

int main()
{
    void particle(str * vari);
    void getdata(str * vari);
    void keep_list(str * vari);
    void ini_divide(str * vari, int kind_p);
    void divide(str * vari, int n_start, int n_end, int kind_p);
    void virt_part(str * vari);
    void input(str * vari);
    void single_step(str * vari);
    void writevtk(str * vari, const int number, const int cc = 0);

    int timestep = 0;
    double time = 0.0;
    int ngrab = 0;
    int output = 0;

    str* vari = new str;

    if (!input_data) {
        particle(vari); //获取流动位置信息
    }
    input(vari);     //获取计算流动粒子的一些初始数据
    virt_part(vari); //获取虚粒子的位置及虚粒子的初始数据
    getdata(vari);
    ini_divide(vari, 0);
    divide(vari, vari->ntotal, vari->ntotal + vari->nvirt, 0);
    keep_list(vari);
    // std::cout << vari->ntotal << " " << vari->nvirt << std::endl;
    // std::cout << vari->ntotal << " " << vari->ncases << std::endl;

    //主循环
    vari->new_dt = 0.0001; //因为后续时间步长发生了变化
    while (time < tmax) {
        vari->visc_dt = 0.0;
        //设置每0.02s输出粒子属性相关信息到文件，用于可视化out=0.02,ngrab表示输出文件数量
        if (time - outt * ngrab >= outt) {
            output = 1;
            ngrab += 1;
        } else {
            output = 0;
        }
        single_step(vari);
        time += vari->new_dt;
        timestep += 1;
        if (output == 1) {
            writevtk(vari, ngrab, 1); //ngrab用于文件的编号,1表示输出虚粒子一起,0表示不含虚粒子输出
            std::cout << "time=" << time << "  "
                      << "dt=" << vari->new_dt << "  "
                      << "step=" << timestep << std::endl;
        }
    }
    std::cout << "撞击出计算域的粒子有" << vari->ncases << "个." << std::endl;

    return 0;
}
