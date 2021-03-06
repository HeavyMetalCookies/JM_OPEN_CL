#pragma once
#ifndef CL_HELPER_HEADER_DOT_HPP
#define CL_HELPER_HEADER_DOT_HPP
//佐 : "Assistant" / ~Open Cl Helper Class~

#include <CL/cl.hpp>
#include <string>

#ifndef _WIN32
#include "佐03.cpp"
#endif

//ABS:Absolute Path To open_cl kernel file:
cl::Program CreateProgram(const std::string& ABS); 

#endif