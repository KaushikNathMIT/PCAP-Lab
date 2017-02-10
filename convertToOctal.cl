__kernel void convertToOctal(__global int* arr) {
	int i=get_global_id(0);
	int num=arr[i];

	long int rem[50],j=0,length=0;
	while(num>0)
	{
		rem[j]=num%8;
		num=num/8;
		j++;
		length++;
	}
	int res=0;
    for(j=length-1;j>=0;j--)
		res=res*10+rem[j];
	arr[i]= res;
}