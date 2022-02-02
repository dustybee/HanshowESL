
void selection_sort_char(unsigned char * arr, int size){
	//sorting
	int i, j;
	for(i = 0; i < size; ++i)
	{
		for( j = i + 1; j < size; ++j)
		{
			if (arr[j] < arr[i])
			{
				unsigned char t = arr[i];
				arr[i] = arr[j];
				arr[j] = t;
			}
		}
	}
}

void selection_sort_int(unsigned int * arr, int size){
	//sorting
	int i, j;
	for(i = 0; i < size; ++i)
	{
		for( j = i + 1; j < size; ++j)
		{
			if (arr[j] < arr[i])
			{
				unsigned int t = arr[i];
				arr[i] = arr[j];
				arr[j] = t;
			}
		}
	}
}


