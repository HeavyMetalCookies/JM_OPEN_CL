 

//main.cpp for openCL tests:
//[setting-up-open-cl

#include<CL/cl.hpp>

int main()
{
	//cl::Platform platform;
	std::vector<cl::Platform> platforms;
	cl::Platform::get(&platforms);
	_ASSERT(platforms.size() > 0);
	
	auto platform = platforms.front();
	std::vector<cl::Device> vＤ; //
	platform.getDevices(CL_DEVICE_TYPE_GPU,&vＤ);
	_ASSERT(vＤ.size() > 0);

	//Ｄ:Device Ｍ:Make/Vendor Ｒ:Revision/Version
	auto Ｄ  = vＤ.front();
	auto Ｍ  =  Ｄ.getInfo<CL_DEVICE_VENDOR >();
	auto Ｒ  =  Ｄ.getInfo<CL_DEVICE_VERSION>();

}


