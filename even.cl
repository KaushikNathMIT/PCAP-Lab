__kernel void even(__global int* A)
{
	int id = get_global_id(0);
	int size = get_global_size(0);

	if(id % 2 == 0 && id + 1 < size)
	{
		if(A[id] > A[id + 1])
		{
			int t = A[id];
			A[id] = A[id + 1];
			A[id + 1] = t;
		}
	}
}