#pragma once
#ifndef CL_HELPER_FILE_DOT_CPP
#define CL_HELPER_FILE_DOT_CPP

#include <CL/cl.hpp>
#include <string>
#include <fstream>
#include <iostream> //std::cout 


//ABS:Absolute File Path
cl::Program make論(const std::string& ABS){
    
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
	std::string ＦＰ= ABS;
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
	

	//Ｃ:Context|論:Program |v論Ｓ:Program Sources
	//------------------------------------------//
	cl::Program::Sources v論Ｓ(
		1,
		std::make_pair(
			Ｓ.c_str(), 
			Ｓ.length() + 1 //+1:null terminator
		)
	);
	cl::Context Ｃ(Ｄ)      ;
	cl::Program 論(Ｃ,v論Ｓ);
	auto err = 論.build("-cl-std=CL1.2");
	if(CL_BUILD_SUCCESS != err){
		std::cout<<"[PROBLEM#1]"<<std::endl;
		std::exit(-1);
	}
	//------------------------------------------//
    
    return 論;
    
}

#endif