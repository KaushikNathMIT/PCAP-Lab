__kernel void str_find (__global char *words, __global int *pos, __global int *found, __global char *search)
{
	int tid=get_global_id(0);
	int this_pos=pos[tid];
	int i=0;
	int flag=0;
	while(words[this_pos]!=' ' && words[this_pos]!='\0' && search[i]!='\0')
	{
		if (words[this_pos]!=search[i])
		{
			flag=-1;
			break;
		}
		i++;
		this_pos++;
	}
	if (flag<0)found[tid]=-1;
	else found[tid]=tid;
}