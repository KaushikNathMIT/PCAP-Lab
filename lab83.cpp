#include <stdio.h>
#include <time.h>
#include <CL/cl.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#define MAX_SOURCE_SIZE (0x100000)

int main(void)
{
	char tempstr[100];
	int n=0, i;
	printf("Enter words: ");
	gets(tempstr);
	int len=strlen(tempstr);
	len++;
	char word[10];
	int wordpos[20];
	wordpos[0]=0;
	printf("Enter search word: ");
	scanf("%s", word);
	for (i=0;i<len;i++)
	{
		if (tempstr[i]==' ' || tempstr[i]=='\0')
		{
			n++;
			wordpos[n]=i+1;
		}
	}
	FILE *fp;
	char *source_str;
	size_t source_size;
	fp=fopen("q3.cl","r");
	if (!fp)
	{
		printf("Failed to load kernel");
		fflush(stdout);
		exit(1);
	}
	source_str=(char*)malloc(MAX_SOURCE_SIZE);
	source_size=fread(source_str, 1, MAX_SOURCE_SIZE, fp);
	fclose(fp);
	cl_platform_id platform_id=NULL;
	cl_device_id device_id=NULL;
	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;
	
	cl_int ret=clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
	ret=clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, &ret_num_devices);
	cl_context context=clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);
	cl_command_queue command_queue=clCreateCommandQueue(context, device_id, CL_QUEUE_PROFILING_ENABLE, &ret);
	
	cl_mem string_a=clCreateBuffer(context, CL_MEM_READ_ONLY, len*sizeof(char),NULL, &ret);
	cl_mem arr_n=clCreateBuffer(context, CL_MEM_READ_ONLY, n*sizeof(int), NULL, &ret);
	cl_mem is_found=clCreateBuffer(context, CL_MEM_WRITE_ONLY, n*sizeof(int), NULL, &ret);
	cl_mem search=clCreateBuffer(context, CL_MEM_READ_ONLY, strlen(word),NULL, &ret);
	ret=clEnqueueWriteBuffer(command_queue, string_a, CL_TRUE, 0, len*sizeof(char), tempstr, 0, NULL, NULL);
	ret=clEnqueueWriteBuffer(command_queue, arr_n, CL_TRUE, 0, n*sizeof(int), wordpos, 0, NULL, NULL);
	ret=clEnqueueWriteBuffer(command_queue, search, CL_TRUE, 0, strlen(word), word, 0, NULL, NULL);
	cl_program program=clCreateProgramWithSource(context, 1, (const char **) &source_str, (const size_t*)&source_size, &ret);
	ret=clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
	cl_kernel kernel=clCreateKernel(program, "str_find", &ret);
	ret=clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&string_a);
	ret=clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&arr_n);
	ret=clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&is_found);
	ret=clSetKernelArg(kernel, 3, sizeof(cl_mem), (void *)&search);
	size_t global_item_size=n;
	size_t local_item_size=1;
	cl_event event;
	ret=clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_item_size, &local_item_size, 0, NULL, &event);
	ret=clFinish(command_queue);
	int *res=(int *)malloc(n*sizeof(int));
	ret=clEnqueueReadBuffer(command_queue, is_found, CL_TRUE, 0, n*sizeof(int), res, 0, NULL, NULL);
	for (i=0;i<n;i++)
	{
		if (res[i]>=0)
			printf("Word found at %d", wordpos[i]);
		//else printf("Word not found");
	}
	fflush(stdout);
	ret=clReleaseKernel(kernel);
	ret=clReleaseProgram(program);
	ret=clReleaseMemObject(string_a);
	ret=clReleaseMemObject(arr_n);
	ret=clReleaseMemObject(is_found);
	ret=clReleaseCommandQueue(command_queue);
	ret=clReleaseContext(context);
	//free(tempstr);
	//free(strres);
	getch();
	return 0;
}