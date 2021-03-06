
//ABOUT FILE:
//----------------------------------------------//
//Original Source: XXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//Edited By: John Mark Isaac Madison
//          (HeavyMetalCookies@Gmail.com)
//----------------------------------------------//

//Libary Imports:
//----------------------------------------------//
//Standard Lib + OpenCL:
//--  --  --  --  --  --  --  --  --  --  --  --//
#include<CL/cl.hpp>
#include<fstream> //for std::ifstream
#include<iostream> //std::cin std::cout
#include <string>
//My Libraries:
//--  --  --  --  --  --  --  --  --  --  --  --//
#include "佐03.hpp"
//----------------------------------------------//


int main() 
{
	std::cout<<"[Main:Version:3.0]"<<std::endl;

	std::string ＦＰ =
		"C:/DEV/REPO/GIT/JM_OPEN_CL/"
		"CL_KERNELS/LEARN02/KERNEL02.CL";

	auto  Ｐ = CreateProgram(ＦＰ);
	auto  Ｃ = Ｐ.getInfo<CL_PROGRAM_CONTEXT>();
	auto vＤ = Ｃ.getInfo<CL_CONTEXT_DEVICES>();
	auto  Ｄ = vＤ.front();


	//bＨ:Host-buffer|bＤ:Device-buffer|Ｆ:Flags
	//------------------------------------------//
	size_t Ｆ = CL_MEM_WRITE_ONLY     |
		        CL_MEM_HOST_READ_ONLY |
		        0;
	char    bＨ[16]; 
	size_t  sＨ = sizeof(bＨ);
	cl::Buffer bＤ(Ｃ, Ｆ, sizeof(bＨ));
	//------------------------------------------//


	//Ｋ:Kernel|Ｑ:CommandQueue 
	//------------------------------------------//
	cl::Kernel Ｋ(Ｐ,"HelloWorld");
	Ｋ.setArg(0, bＤ);
	cl::CommandQueue Ｑ(Ｃ,Ｄ);
	Ｑ.enqueueTask(Ｋ);
	Ｑ.enqueueReadBuffer(bＤ,CL_TRUE,0,sＨ,bＨ);
	//------------------------------------------//


	//Surround expected output with text so if
	//if ends up blank we have visual confirmation
	//that something went wrong.
	//------------------------------------------//
	std::cout<<"[ANYTHING BELOW?]"<<std::endl;
	std::cout<<bＨ;
	std::cout<<"[ANYTHING ABOVE?]"<<std::endl;
	//------------------------------------------//


	//Some junk to cause console to pause
	//before closing:
	//------------------------------------------//
	std::cin.get();
	getchar();
	getchar();
	//------------------------------------------//
}


