
__kernel void ProcMultiDimArr(
    global int* data
){
    //Index==(Y*Width)+X
    //---------------------------//
    size_t Y  = get_global_id  (1);
    size_t X  = get_global_id  (0);
    size_t W  = get_global_size(0);
    size_t i = (Y*W)+X;
    //---------------------------//
                 
    data[i] = data[i] * 2;
}