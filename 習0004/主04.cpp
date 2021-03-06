

#include "佐04.hpp"
#include <iostream>
#include <array> 

namespace cl{
    typedef Program      論;
    typedef Buffer       器;
    typedef Kernel       苗;
	typedef CommandQueue 軍;
}

int main(){
    
    //論:Program|Ｃ:Context|vＤ:Devices|Ｄ:Device
    //ＦＰ:File-Path
    //------------------------------------------//
    auto ＦＰ =
        "C:/DEV/REPO/GIT/JM_OPEN_CL/"
        "CL_KERNELS/LEARN04/KernelFile04.cl";
    cl::論 論 = make論(ＦＰ);
    auto  Ｃ = 論.getInfo<CL_PROGRAM_CONTEXT>();
    auto vＤ = Ｃ.getInfo<CL_CONTEXT_DEVICES>();
    auto  Ｄ =vＤ.front();
    //------------------------------------------//
    
    //Create multi-dimensional array:
    //------------------------------------------//
    // int arr[3][2]:
    //NOTE: The extra "{}" arrounding the array
    //creation statement is likely an error with
    //visual studio.
    //--  --  --  --  --  --  --  --  --  --  --//
    //c:count/number-of | Ａ:array | aｉ:int-array
    //cＲ:c-rows|cＣ:c-columns|cＴ:c-total
    //--  --  --  --  --  --  --  --  --  --  --//
    const int cＲ = 3;
    const int cＣ = 2;
    const int cＴ = cＲ*cＣ;
    std::array<std::array<int, cＣ>,cＲ> Ａ =
    {{{1,1}, {2,2}, {3,3}}};
    //------------------------------------------//
    
    //Load Buffer(器) using Array(Ａ):
    //------------------------------------------//
    //sＡ:sizeof-array | pＡ:pointer-to-array
    //Ｆ:flags | 器:buffer [Ｃ:context]
    //--  --  --  --  --  --  --  --  --  --  --//
    auto sＡ = sizeof(int) * cＴ;
    auto pＡ = Ａ.data();
    auto Ｆ = 
        CL_MEM_READ_WRITE     |
        CL_MEM_HOST_READ_ONLY |
        CL_MEM_COPY_HOST_PTR  |
    0;
    cl::器 器(Ｃ,Ｆ,sＡ,pＡ);
    //------------------------------------------//
    
    //Create Kernel and set arguments:
    //------------------------------------------//
    //苗FN:Kernel-Func-Name|苗:Kernel|器:Buffer
    //--  --  --  --  --  --  --  --  --  --  --//
    auto 苗FN = "ProcMultiDimArr";
    cl::苗 苗(論,苗FN);
    苗.setArg(0, 器);
    //------------------------------------------//
    
    //???????????
    //------------------------------------------//
    //軍:command-queue|Ｔ:true|a:?|b?
    //--  --  --  --  --  --  --  --  --  --  --//
    cl::軍 軍(Ｃ,Ｄ);
    auto Ｔ = CL_TRUE;
    auto a = cl::NullRange;
    auto b = cl::NDRange(2,3);
    軍.enqueueNDRangeKernel(苗,a,b);
    軍.enqueueReadBuffer(器,Ｔ,0,sＡ,pＡ);
    //------------------------------------------//
    
    std::cin.get();
}