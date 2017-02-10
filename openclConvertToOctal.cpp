#include <iostream>
#include <stdio.h>
#include <CL/cl.h>
#include <stdlib.h>

using namespace std;

#define MAX_SOURCE_SIZE (0x100000)

int main() {
	int i, listSize;
	cout<<"Enter the number of elements\n";
	cin>>listSize;
	int* arr = new int[listSize];
	cout<<"Enter the numbers\n";
	for(i=0; i<listSize; i++) {
		cin>>arr[i];
	}

	//Load Kenel source code into array sourceString

	FILE* fp;
	char* sourceString;
	size_t sourceSize;
	//fp = fopen("convertToOctal.cl", "r");
	fp = fopen("onesComplement.cl", "r");
	if(!fp) {
		cout<<"\nFailed to load kernel\n";
		exit(0);
	}
	sourceString = new char[MAX_SOURCE_SIZE];
	sourceSize = fread(sourceString, 1, MAX_SOURCE_SIZE, fp);
	fclose(fp);
	//----------------------------------------------------

	//Get platform and device information

	cl_platform_id platformID = NULL;
	cl_device_id deviceId = NULL;
	cl_uint numDevices, numPlatforms;
	cl_int ret = clGetPlatformIDs(1, &platformID, &numPlatforms);
	ret = clGetDeviceIDs(platformID, CL_DEVICE_TYPE_GPU, 1, &deviceId, &numDevices);
	//-------------------------------------------------------

	//Create an opencl context
	cl_context context = clCreateContext(NULL, 1, &deviceId, NULL, NULL, &ret);

	//create a command queue
	cl_command_queue commandQueue = clCreateCommandQueue(context, deviceId, NULL, &ret);

	//Create memory buffers  on the device for all the vectors
	cl_mem obj1 = clCreateBuffer(context, CL_MEM_READ_ONLY, listSize*sizeof(int), NULL, &ret);

	//copy list to respective memory buffer
	ret = clEnqueueWriteBuffer(commandQueue, obj1, CL_TRUE, 0, listSize*sizeof(int), arr, 0, NULL, NULL);

	//create a program from the kernel source
	cl_program program = clCreateProgramWithSource(context, 1, (const char**) &sourceString, (const size_t*) &sourceSize, &ret);
	
	//Build the program
	ret = clBuildProgram(program, 1, &deviceId, NULL, NULL, NULL);

	//create the opencl kernel object
	//cl_kernel kernel = clCreateKernel(program, "convertToOctal", &ret);
	cl_kernel kernel = clCreateKernel(program, "onesComplement", &ret);

	//set the arguments of the kernel
	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*) &obj1);

	size_t globalItemSize = listSize;
	size_t localItemSize = 1;

	//Execute the kernel on the device
	cl_event event;
	ret = clEnqueueNDRangeKernel(commandQueue, kernel, 1, NULL, &globalItemSize, &localItemSize, 0, NULL, NULL);
	ret = clFinish(commandQueue);

	//Read the memory buffer C on the device to the local variable c
	int* C= new int[listSize];
	ret = clEnqueueReadBuffer(commandQueue, obj1, CL_TRUE, 0, listSize*sizeof(int), C, 0, NULL, NULL);
	for(i=0;i<listSize;i++)
		cout<<C[i]<<" ";

	//Clean up
	ret = clFlush(commandQueue);
	ret = clReleaseKernel(kernel);
	ret = clReleaseProgram(program);
	ret = clReleaseMemObject(obj1);
	ret = clReleaseCommandQueue(commandQueue);
	ret = clReleaseContext(context);

	free(arr);
	int a;
	cin>>a;
	return 0;

}