//ProcessArray.cl
__kernel void ProcessArray(
    __global int* i_data, //input data
    __global int* o_data  //output data
){

    
    o_data[ get_global_id(0) ] =
    i_data[ get_global_id(0) ] * 2;

}

//@24:48[cl-tut-07]/[cl-vid-01]:
//"But why is it bollocks?"
//@26:38[cl-tut-07]/[cl-vid-01]:
//Debugged the kernel and code.

