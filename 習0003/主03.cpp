
//ABOUT FILE:
//----------------------------------------------//
//Original Source: 
//https://www.youtube.com/watch?v=N0H0NCoOTUA
//Edited By: John Mark Isaac Madison
//          (HeavyMetalCookies@Gmail.com)
//----------------------------------------------//

//Libary Imports:
//----------------------------------------------//
//Standard Lib:
//--  --  --  --  --  --  --  --  --  --  --  --//
#include <iostream>
//My Libraries:
//--  --  --  --  --  --  --  --  --  --  --  --//
#include "佐03.hpp" 
//----------------------------------------------//

//forward-declaration:
void fnM(std::string err_msg);

int main()
{
   
    //ＦＰ:File-Path | Ｐ:Program  | v:vector --//
    //Ｃ:Context|vＤ:Device-Vector|Ｄ:Device --//
    //------------------------------------------//
    std::string ＦＰ = 
        "C:/DEV/REPO/GIT/JM_OPEN_CL/"
		"CL_KERNELS/LEARN03/ProcessArray03.cl";
    auto  Ｐ = CreateProgram(ＦＰ);
	auto  Ｃ = Ｐ.getInfo<CL_PROGRAM_CONTEXT>();
	auto vＤ = Ｃ.getInfo<CL_CONTEXT_DEVICES>();
	auto& Ｄ = vＤ.front();
    //------------------------------------------//
    
    
    //Ｖ:Vector | sＶ:size of Ｖ in bytes.
    //------------------------------------------//
    std::vector<int> Ｖ(16); //1024
    size_t sＶ = sizeof(int) * Ｖ.size();
    
    //std::fill(Ｖ.begin(),Ｖ.end(),1);
    //------------------------------------------//
    
    
    //iＦ:input-Flags | oＦ:output-Flags
    //------------------------------------------//
    auto iＦ = //-------------//
        CL_MEM_READ_ONLY      |
        CL_MEM_HOST_NO_ACCESS |
        CL_MEM_COPY_HOST_PTR  |
    0;//----------------------//
    //--  --  --  --  --  --  --  --  --  --  --//
    auto oＦ = //-------------//
        CL_MEM_WRITE_ONLY      |
        CL_MEM_HOST_READ_ONLY  |
    0;//----------------------//
    //------------------------------------------//
    
    
    //iＢ:input-buffer | oＢ:output-buffer
    //Ｅi:Error-iＢ|Ｅo:Error-oＢ|Ｎp:null pointer
    //------------------------------------------//
    auto   Ｎp = nullptr ;
    cl_int Ｅi = CL_FALSE;
    cl_int Ｅo = CL_FALSE;
    cl::Buffer iＢ(Ｃ,iＦ,sＶ,Ｖ.data(),&Ｅi);
    cl::Buffer oＢ(Ｃ,oＦ,sＶ,Ｎp      ,&Ｅo);
    //------------------------------------------//
    
    
    //Ｋ:Kernel | Ｋn:Kernel Func Name in .cl file.
    //Ｅk0:Error-KernelArg#0
    //Ｅk1:Error-KernelArg#1
    //------------------------------------------//
    cl_int Ｅk0 = CL_FALSE;
    cl_int Ｅk1 = CL_FALSE;
    char const * Ｋn = "ProcessArray";
    cl::Kernel  Ｋ(Ｐ,Ｋn);
    Ｅk0 = Ｋ.setArg(0, iＢ);
    Ｅk1 = Ｋ.setArg(1, oＢ);
    //------------------------------------------//
    
    
    //Ｇ:Global-size||Ｆ:False|Ｏ:offset
    //Ｌ:Local WorkGroup Size
    //------------------------------------------//
    auto Ｏ = cl::NullRange;
    auto Ｇ = cl::NDRange(Ｖ.size());
    auto Ｆ = CL_FALSE;
    auto Ｌ = 4;
    //------------------------------------------//
    
    
    //Ｑ:Queue
	//------------------------------------------//
	cl::CommandQueue Ｑ(Ｃ,Ｄ);
	//------------------------------------------//


	//Fill the buffer with dummy data:
	//--  --  --  --  --  --  --  --  --  --  --//
	//Ｆ:Fill|Ｆo:Offset|Ｆv:Value|Ｅf:Error
	//Ｆi:Start-Index|Ｆl:Length-Of-Fill
	//--  --  --  --  --  --  --  --  --  --  --//
	auto Ｆo = 10;
	auto Ｆv = 3 ;
	auto Ｆi = sizeof(int)*Ｆo;
	auto Ｆl = sizeof(int)*(Ｖ.size() - Ｆo);
	auto Ｅf =
	Ｑ.enqueueFillBuffer(iＢ,Ｆv,Ｆi,Ｆl);
	//------------------------------------------//


    //Ｅq0:Error-Queue-Submission #0
    //Ｅq1:Error-Queue-Submission #1
    //------------------------------------------//
    auto Ｅq0 =
    //Ｑ.enqueueNDRangeKernel(Ｋ,Ｏ,Ｇ,Ｌ);
	Ｑ.enqueueNDRangeKernel(Ｋ,Ｏ,Ｇ);
    auto Ｅq1 = 
    Ｑ.enqueueReadBuffer(oＢ,Ｆ,0,sＶ,Ｖ.data());
    //------------------------------------------//
    

    //Consolodate all error checking here:
    //------------------------------------------//
    //hＥ:has-Error?
    //------------------------------------------//
    cl_int hＥ = CL_FALSE;
	hＥ = Ｅi|Ｅo|Ｅk0|Ｅk1|Ｅq0|Ｅq1|Ｅf;
	//--  --  --  --  --  --  --  --  --  --  --//
	if(CL_SUCCESS != Ｅi ){fnM("[Ei_]");}
	if(CL_SUCCESS != Ｅo ){fnM("[Eo_]");}
    //--  --  --  --  --  --  --  --  --  --  --//
    if(CL_SUCCESS != Ｅk0){fnM("[Ek0]");}
    if(CL_SUCCESS != Ｅk1){fnM("[Ek1]");}
	//------------------------------------------//
	if(CL_SUCCESS != Ｅf ){fnM("[Ef_]");}
    //--  --  --  --  --  --  --  --  --  --  --//
    if(CL_SUCCESS != Ｅq0){fnM("[Eq0]");}
    if(CL_SUCCESS != Ｅq1){fnM("[Eq1]");}
    //--  --  --  --  --  --  --  --  --  --  --//
    if(hＥ!=0){
		std::exit(-1);
	}
    //------------------------------------------//
    

    //Create A Memory Fence with cl::finish(),
    //then pause the console so we can see the
    //resulting output.
    //------------------------------------------//
    cl::finish();
    std::cin.get();
    //------------------------------------------//
}

//fnM:Function.Message
void fnM(std::string err_msg){
	std::cout<<err_msg<<std::endl;
}