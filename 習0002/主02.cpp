
//ABOUT FILE:
//----------------------------------------------//
//Original Source: [cl-tut-06]
//https://www.youtube.com/watch?v=f8jnAuFMnPY
//Edited By: John Mark Isaac Madison
//          (HeavyMetalCookies@Gmail.com)
//----------------------------------------------//

//Library Imports:
//----------------------------------------------//
#include<CL/cl.hpp>
#include<fstream> //for std::ifstream
#include<iostream> //std::cin std::cout
#include <string>
//----------------------------------------------//


int main() 
{
	//vＤ:Device(S) |vＬ:Platform(S)|Ｌ:Platform
	//------------------------------------------//
	std::vector<cl::Platform> vＬ;
	cl::Platform::get(&vＬ);
	_ASSERT(vＬ.size() > 0);
	//--  --  --  --  --  --  --  --  --  --  --// 
	auto Ｌ = vＬ.front();
	std::vector<cl::Device> vＤ; //
	Ｌ.getDevices(CL_DEVICE_TYPE_GPU,&vＤ);
	_ASSERT(vＤ.size() > 0);
	//------------------------------------------//


	//Ｄ:Device|Ｍ:Make/Vendor|Ｒ:Revision/Version
	//------------------------------------------//
	auto Ｄ  = vＤ.front();
	auto Ｍ  =  Ｄ.getInfo<CL_DEVICE_VENDOR >();
	auto Ｒ  =  Ｄ.getInfo<CL_DEVICE_VERSION>();
	std::cout<<"Vendor :"<<Ｍ<<std::endl;
	std::cout<<"Version:"<<Ｒ<<std::endl;
	//------------------------------------------//


	//Ｈ:Hello World File|ＦＰ:FilePath|Ｓ:String
	//------------------------------------------//
	std::string ＦＰ= 
	"C:/DEV/REPO/GIT/JM_OPEN_CL/"
	"CL_KERNELS/LEARN02/KERNEL02.CL";
	std::ifstream Ｈ(ＦＰ,std::ifstream::in);
	std::string Ｓ;
	if(Ｈ){
		std::cout<<"[File Exists!]"<<std::endl;
		Ｓ.assign(
			//Input starting point of file:
			(std::istreambuf_iterator<char>(Ｈ))
			,
			//Input ending point of file:
			//Ｑ: Why is () enclosure necessary?
			//Ａ: Looks like function prototype.
			(std::istreambuf_iterator<char>())
		);		
		std::cout<<"File Contents:"<<std::endl;
		std::cout<<Ｓ<<std::endl;
	}else{
		std::cout<<"[File-Open-Fail]"<<std::endl;
	}
	//------------------------------------------//
	

	//Ｃ:Context|Ｐ:Program |vＰＳ:Program Sources
	//------------------------------------------//
	cl::Program::Sources vＰＳ(
		1,
		std::make_pair(
			Ｓ.c_str(), 
			Ｓ.length() + 1 //+1:null terminator
		)
	);
	cl::Context Ｃ(Ｄ)      ;
	cl::Program Ｐ(Ｃ,vＰＳ);
	auto err = Ｐ.build("-cl-std=CL1.2");
	if(CL_BUILD_SUCCESS != err){
		std::cout<<"[PROBLEM#1]"<<std::endl;
		std::exit(-1);
	}
	//------------------------------------------//


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
	cl::Kernel Ｋ(Ｐ,"HelloWorld",&err);
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


