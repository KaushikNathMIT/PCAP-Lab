__kernel void onesComplement(__global int* arr) {
	int i=get_global_id(0);
	arr[i] = ~arr[i];
}