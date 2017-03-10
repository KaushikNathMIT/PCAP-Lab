#include<stdio.h>
#include<stdlib.h>
#include<CL/cl.h>
#include<iostream>
using namespace std;

#define MAX_SOURCE_SIZE (0x100000)

int main6()
{
	int i, LIST_SIZE;
	printf("Enter how many elements:");
	cin>>LIST_SIZE;

	int *A = (int*)malloc(sizeof(int) * LIST_SIZE);

	cout<<"Enter "<<LIST_SIZE<<" values\n";
	for(i = 0; i < LIST_SIZE; i++)
	{
		cin>>A[i];
	}

	FILE *fp;
	char *source_str, *source_str1;
	size_t source_size, source_size1;

	fp = fopen("odd.cl", "r");

	if(!fp)
	{
		fprintf(stderr, "Failed to load kernel\n");
		getchar();
		exit(1);
	}
	
	source_str = (char*)malloc(MAX_SOURCE_SIZE);
	source_size = fread(source_str, 1, MAX_SOURCE_SIZE, fp);

	fp = fopen("even.cl", "r");

	if(!fp)
	{
		fprintf(stderr, "Failed to load kernel\n");
		getchar();
		exit(1);
	}
	
	source_str1 = (char*)malloc(MAX_SOURCE_SIZE);
	source_size1 = fread(source_str1, 1, MAX_SOURCE_SIZE, fp);

	fclose(fp);

	cl_platform_id platform_id = NULL;
	cl_device_id device_id = NULL;
	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;

	cl_int ret = clGetPlatformIDs(1, &platform_id, NULL);
	ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, NULL);

	cl_context context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);

	cl_command_queue command_queue = clCreateCommandQueue(context, device_id, NULL, &ret);

	cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_WRITE, LIST_SIZE * sizeof(int), NULL, &ret);
	//cl_mem b_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY, LIST_SIZE * sizeof(int), NULL, &ret);

	ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0, LIST_SIZE * sizeof(int), A, 0, NULL, NULL);

	cl_program program = clCreateProgramWithSource(context, 1, (const char**)&source_str, (const size_t*)&source_size, &ret);
	cl_program program1 = clCreateProgramWithSource(context, 1, (const char**)&source_str1, (const size_t*)&source_size1, &ret);
	clBuildProgram(program,1,&device_id,NULL,NULL,NULL);
	clBuildProgram(program1,1,&device_id,NULL,NULL,NULL);
	cl_kernel kernel = clCreateKernel(program, "odd", &ret);
	cl_kernel kernel1 = clCreateKernel(program1, "even", &ret);

	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&a_mem_obj);
	ret = clSetKernelArg(kernel1, 0, sizeof(cl_mem), (void*)&a_mem_obj);

	size_t global_item_size = LIST_SIZE;
	size_t local_item_size = 1;

	int* RES = (int*)malloc(sizeof(int) * LIST_SIZE);

	for(int i = 0; i < LIST_SIZE / 2; i++){
	ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_item_size, &local_item_size, 0, NULL, NULL);
    ret = clEnqueueNDRangeKernel(command_queue, kernel1, 1, NULL, &global_item_size, &local_item_size, 0, NULL, NULL);
	}

	clFinish(command_queue);
	ret = clEnqueueReadBuffer(command_queue, a_mem_obj, CL_TRUE, 0, LIST_SIZE * sizeof(int), RES, 0, NULL, NULL);

	cout<<"Sorted Array\n";
	for(int j = 0; j < LIST_SIZE; j++)
		cout<<RES[j]<<" ";
	cout<<endl;

	getchar();
	ret=clReleaseKernel(kernel);
	ret=clReleaseKernel(kernel1);
	ret=clReleaseProgram(program);
	ret=clReleaseMemObject(a_mem_obj);
	ret=clReleaseCommandQueue(command_queue);
	ret=clReleaseContext(context);

	free(A);
	free(RES);
	getchar();
	return 0;
}