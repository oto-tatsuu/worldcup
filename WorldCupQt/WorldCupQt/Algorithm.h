#pragma once
#define SORT_LIMIT 28
class Algorithm
{
public:
	Algorithm();
	~Algorithm();
	template<typename Record>
	Record **CreateArray(Record*src,int size);
	template<typename Record>
	void DeleteArray(Record **array,int size);
	template<typename Record,typename Member>
    Record** InsertSort(Record*array,Member function,int src_size,bool descending=true);
	template<typename Record, typename Member>
	Record** MergeSort(Record*array, Member function, int src_size, bool descending = true);
	
private:
	template<typename Record>
	void Swap(Record** src, int a, int b);
	template<typename Record, typename Member>
	void MergeSort(Record** array, Member , Record** t, int left, int right, bool descending = true);
	template<typename Record, typename Member>
	void Merge(Record** array,Member function,Record** t,int left,int right,bool descending=true);
};

inline Algorithm::Algorithm()
{
}
inline Algorithm::~Algorithm()
{
}

template<typename Record>
inline Record ** Algorithm::CreateArray(Record *src,int size)
{
	Record**a = new Record*[size];
	for (int i = 0; i < size; i++) 
	{
		a[i] = &src[i];
	}
	return a;
}

template<typename Record>
inline void Algorithm::DeleteArray(Record ** array,int size)
{
	for (int i = 0; i < size; i++) 
	{
		array[i] = nullptr;
	}
	delete[]array;
}

template<typename Record, typename Member>
inline Record** Algorithm::InsertSort(Record * array, Member function, int src_size, bool descending)
{
	Record**r = CreateArray(array,src_size);
	
	if (descending) 
	{
		for (int i = 0; i < src_size; i++)
		{
			Record*temp=r[i];
			int j = i - 1;
			for (; j >= 0 && (temp->*function)() > (r[j]->*function)(); j--)
			{
				r[j + 1] = r[j];
			}
			r[j+1] = temp;
		}
	}
	else
	{
		for (int i = 0; i < src_size; i++)
		{
			Record*temp = r[i];
			int j = i - 1;
			for (; j >= 0 && (temp->*function)() < (r[j]->*function)(); j--)
			{
				r[j + 1] = r[j];
			}
			r[j + 1] = temp;
		}
	}
	return r;
}

template<typename Record, typename Member>
inline Record** Algorithm::MergeSort(Record * array, Member function, int src_size, bool descending)
{
	Record**t = new Record*[src_size];
	Record**src = CreateArray(array,src_size);
	MergeSort(src,function, t, 0, src_size - 1,descending);
	DeleteArray(t, src_size);
	return src;
}

template<typename Record>
inline void Algorithm::Swap(Record ** src, int a, int b)
{
	Record*temp=src[a];
	arc[a] = src[b];
	src[b] = temp;
}

template<typename Record, typename Member>
inline void Algorithm::MergeSort(Record ** array, Member function, Record ** t, int left, int right, bool descending)
{
	int middle;
	if (left < right)
	{
		middle = (left + right) / 2;
		MergeSort(array, function, t, left, middle, descending);
		MergeSort(array, function, t, middle + 1, right, descending);
		Merge(array, function, t, left, right, descending);//¹é²¢
	}
}

template<typename Record, typename Member>
inline void Algorithm::Merge(Record ** array, Member function, Record ** t, int left, int right, bool descending)
{
	int middle = (left + right) / 2;
	int index1 = left, index2 = right;
	for (int i = left; i <= middle; i++)
		t[i] = array[i];
	for (int j = 1; j <= right - middle; j++)
		t[right - j + 1] = array[middle + j];
	for (int i = left; i <= right; i++)
	{
		if (descending)
		{
			if ((t[index1]->*function)() < (t[index2]->*function)())
				array[i] = t[index2--];
			else
				array[i] = t[index1++];
		}
		else 
		{
			if ((t[index1]->*function)() > (t[index2]->*function)())
				array[i] = t[index2--];
			else
				array[i] = t[index1++];
		}
	}
}




