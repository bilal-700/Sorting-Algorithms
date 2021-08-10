#include <iostream>
#include <string>
#include <chrono>
#include <list>
#include <vector>
#include <math.h>
using namespace std;

template <class T>
class SortAlgos
{
public:
	int s = 0;
	int sizeofarray, choice, order;
	void print(T a[], int n)
	{
		cout << "The sorted array is:" << endl;
		cout << "  -> ";
		for (int i = 0; i < n; i++)
		{
			cout << a[i] << " ";
		}
	}

	void selectionsort(T data[], int n, int order)
	{
		for (int i = 0, j, least; i < n - 1; i++)
		{
			for (j = i + 1, least = i; j < n; j++)
			{
				if (order == 1)
				{
					if (data[j] < data[least])
						least = j;
				}
				else
				{
					if (data[j] > data[least])
						least = j;
				}
			}
			swap(data[least], data[i]);
		}
	}
	void merge(T* a, int p, int q, int r, int order)
	{
		int i, j, k;
		int n1 = q - p + 1;
		int n2 = r - q;

		T* L = new T[n1];
		T* R = new T[n2];

		for (i = 0; i < n1; i++)
		{
			L[i] = a[p + i];
		}
		for (j = 0; j < n2; j++)
		{
			R[j] = a[q + 1 + j];
		}

		i = 0;
		j = 0;
		k = p;
		while (i < n1 && j < n2)
		{
			if (order == 1)
			{
				if (L[i] <= R[j])
				{
					a[k] = L[i];
					i++;
				}
				else
				{
					a[k] = R[j];
					j++;
				}
			}
			else {
				if (L[i] >= R[j])
				{
					a[k] = L[i];
					i++;
				}
				else
				{
					a[k] = R[j];
					j++;
				}
			}
			k++;
		}
		while (i < n1)
		{
			a[k] = L[i];
			i++;
			k++;
		}
		while (j < n2)
		{
			a[k] = R[j];
			j++;
			k++;
		}

		delete[] L, R;
	}
	// merge sort function
	void mergeSort(T a[], int p, int r, int order)
	{
		int q;
		if (p < r)
		{
			q = (p + r) / 2;
			mergeSort(a, p, q, order);
			mergeSort(a, q + 1, r, order);
			merge(a, p, q, r, order);
		}

	}

	int partition(T a[], int p, int r, int order)
	{
		int i = (p - 1);
		for (int j = p; j <= r - 1; j++)
		{
			if (order == 1)
			{
				if (a[j] <= a[r])
				{
					i++;
					swap(a[i], a[j]);
				}
			}
			else
			{
				if (a[j] >= a[r])
				{
					i++;
					swap(a[i], a[j]);
				}
			}
		}
		swap(a[i + 1], a[r]);
		return (i + 1);
	}

	void quicksort(T a[], int p, int r, int order)
	{
		if (p < r)
		{
			int q;
			q = partition(a, p, r, order);
			quicksort(a, p, q - 1, order);
			quicksort(a, q + 1, r, order);
		}
	}

	class RadixSortAlgo
	{
	public:
		string* r_List;
		int r_size;
		RadixSortAlgo()
		{

		}
		RadixSortAlgo(int l)
		{
			r_size = l;
			r_List = new string[l];
		}

		size_t getMax(string a[], int sizeofarray)
		{
			size_t max = a[0].size();
			for (int i = 1; i < sizeofarray; i++)
			{
				if (a[i].size() > max)
					max = a[i].size();
			}
			return max;
		}

		void countSort(string a[], int size, size_t k)
		{
			string* b = NULL; int* c = NULL;
			b = new string[size];
			c = new int[257];

			for (int i = 0; i < 257; i++)
				c[i] = 0;
			for (int j = 0; j < size; j++)
				c[k < a[j].size() ? (int)(unsigned char)a[j][k] + 1 : 0]++;
			for (int f = 1; f < 257; f++)
				c[f] += c[f - 1];
			for (int r = size - 1; r >= 0; r--) {
				b[c[k < a[r].size() ? (int)(unsigned char)a[r][k] + 1 : 0] - 1] = a[r];
				c[k < a[r].size() ? (int)(unsigned char)a[r][k] + 1 : 0]--;
			}
			for (int l = 0; l < size; l++)
				a[l] = b[l];
			delete[] b;
			delete[] c;
		}

		void radixSortLong(long* a, int n, int max)
		{
			int i, j, m = 0, p = 1, index, temp, count = 0;
			list<long> pocket[10];      //radix of decimal number is 10
			for (i = 0; i < max; i++)
			{
				m = pow(10, i + 1);
				p = pow(10, i);
				for (j = 0; j < n; j++)
				{
					temp = (int)a[j] % m;
					index = temp / p;      //find index for pocket array
					pocket[index].push_back(a[j]);
				}
				count = 0;
				for (j = 0; j < 10; j++)
				{
					//delete from linked lists and store to array
					while (!pocket[j].empty()) {
						a[count] = *(pocket[j].begin());
						pocket[j].erase(pocket[j].begin());
						count++;
					}
				}
			}
		}
		void radixSortF(float* a, int sizeofarray, int max)
		{
			int i, j, m = 0, p = 1, index, temp, count = 0;
			list<float> pocket[10];      //radix of decimal number is 10
			for (i = 0; i < max; i++)
			{
				m = pow(10, i + 1);
				p = pow(10, i);
				for (j = 0; j < sizeofarray; j++)
				{
					temp = (int)a[j] % m;
					index = temp / p;      //find index for pocket array
					pocket[index].push_back(a[j]);
				}
				count = 0;
				for (j = 0; j < 10; j++)
				{
					//delete from linked lists and store to array
					while (!pocket[j].empty())
					{
						a[count] = *(pocket[j].begin());
						pocket[j].erase(pocket[j].begin());
						count++;
					}
				}
			}
		}

		void radixSortS(string b[], int r)
		{
			size_t max = getMax(b, r);
			for (size_t digit = max; digit > 0; digit--)
				countSort(b, r, digit - 1);
		}
		void print(long a[], int n, int order)
		{
			if (order == 1)
			{
				cout << "The sorted array is:" << endl;
				cout << "  -> ";
				for (int i = 0; i < n; i++)
				{
					cout << a[i] << " ";
				}
			}
			else if (order == 2)
			{
				cout << "The sorted array is:" << endl;
				cout << "  -> ";
				for (int i = n - 1; i >= 0; i--)
				{
					cout << a[i] << " ";
				}
			}
		}
		void print(float a[], int n, int order)
		{
			if (order == 1)
			{
				cout << "The sorted array is:" << endl;
				cout << "  -> ";
				for (int i = 0; i < n; i++)
				{
					cout << a[i] << " ";
				}
			}
			else
			{
				cout << "The sorted array is:" << endl;
				cout << "  -> ";
				for (int i = n - 1; i >= 0; i--)
				{
					cout << a[i] << " ";
				}
			}

		}
		void print(string a[], int n, int order)
		{
			if (order == 1)
			{
				cout << "The sorted array is:" << endl;
				cout << "  -> ";
				for (int i = 0; i < n; i++)
				{
					cout << a[i] << " ";
				}
			}
			else if (order == 2)
			{
				cout << "The sorted array is:" << endl;
				cout << "  -> ";
				for (int i = n - 1; i >= 0; i--)
				{
					cout << a[i] << " ";
				}
			}
		}

	};
	int Choice()
	{
		cout << "Select the type of sort: " << endl;
		cout << "1) Selection Sort\n2) Merge Sort\n3) Quick Sort\n4) Radix Sort\n5) All mentioned above" << endl;
		cout << "  Choice->";
		cin >> choice;
		cout << "---------------------------------------------------" << endl;
		cout << "Select the order you want to sort the array: " << endl;
		cout << "1) Ascending Order\n2) Descending Order" << endl;
		cout << "  Order Choice->";
		cin >> order;
		cout << "---------------------------------------------------" << endl;
		cout << "Enter the size of array:\n  Size->";
		cin >> sizeofarray;
		s = sizeofarray;
		while (sizeofarray > 100)
		{
			cout << "Max. size of array is 100. Enter the size in the limit again.\n";
				cin >> sizeofarray;
		}
		cout << "---------------------------------------------------" << endl;
		return choice;
	}

	void Options(int choiceOfDataType)
	{
		int choice2;
		int choiceOfSort;
		SortAlgos<T> s;
		while (1)
		{
			choiceOfSort = Choice();
			if (choiceOfSort == 1 || choiceOfSort == 2 || choiceOfSort == 3 || choiceOfSort == 5)
			{
				T* a = new T[sizeofarray];
				cout << "Enter the array to be sorted: " << endl;
				cout << "  Array->";
				for (int i = 0; i < sizeofarray; i++)
				{
					cin >> a[i];
				}
				cout << "---------------------------------------------------" << endl;
				while (1)
				{
					if (choice == 1)
					{
						cout << "Time complexity for selection sort with array size " << sizeofarray << " is:" << endl;
						auto start = chrono::high_resolution_clock::now();
						s.selectionsort(a, sizeofarray, order);
						auto finish = chrono::high_resolution_clock::now();
						chrono::duration<double> elapsed = finish - start;
						cout << "  Time complexity->" << elapsed.count();
						cout << "\n---------------------------------------------------" << endl;
						print(a, sizeofarray);
						cout << "\n---------------------------------------------------" << endl;
						break;
					}
					else if (choice == 2)
					{
						cout << "Time complexity for merge sort with array size " << sizeofarray << " is:" << endl;
						auto start = chrono::high_resolution_clock::now();
						s.mergeSort(a, 0, (sizeofarray - 1), order);
						auto finish = chrono::high_resolution_clock::now();
						chrono::duration<double> elapsed = finish - start;
						cout << "  Time complexity->" << elapsed.count();
						cout << "\n---------------------------------------------------" << endl;
						print(a, sizeofarray);
						cout << "\n---------------------------------------------------" << endl;
						break;
					}
					else if (choice == 3)
					{
						cout << "Time complexity for quick sort with array size " << sizeofarray << " is:" << endl;
						auto start = chrono::high_resolution_clock::now();
						s.quicksort(a, 0, (sizeofarray - 1), order);
						auto finish = chrono::high_resolution_clock::now();
						chrono::duration<double> elapsed = finish - start;
						cout << "  Time complexity->" << elapsed.count();
						cout << "\n---------------------------------------------------" << endl;
						print(a, sizeofarray);
						cout << "\n---------------------------------------------------" << endl;
						break;
					}

					else if (choice == 5)
					{
						cout << "Time complexity for selection sort with array size " << sizeofarray << " is:" << endl;
						auto start1 = chrono::high_resolution_clock::now();
						s.selectionsort(a, sizeofarray, order);
						auto finish1 = chrono::high_resolution_clock::now();
						chrono::duration<double> elapsed1 = finish1 - start1;
						cout << "  Time complexity->" << elapsed1.count();
						cout << "\n\t\t----------------------" << endl;

						cout << "Time complexity for merge sort with array size " << sizeofarray << " is:" << endl;
						auto start2 = chrono::high_resolution_clock::now();
						s.mergeSort(a, 0, (sizeofarray - 1), order);
						auto finish2 = chrono::high_resolution_clock::now();
						chrono::duration<double> elapsed2 = finish2 - start2;
						cout << "  Time complexity->" << elapsed2.count();
						cout << "\n\t\t----------------------" << endl;

						cout << "Time complexity for radix sort with array size " << sizeofarray << " is:" << endl;
						auto start3 = chrono::high_resolution_clock::now();
						s.selectionsort(a, sizeofarray , order);
						s.selectionsort(a, sizeofarray , order);
						auto finish3 = chrono::high_resolution_clock::now();
						chrono::duration<double> elapsed3 = finish3 - start3;
						cout << "  Time complexity->" << elapsed3.count();
						cout << "\n\t\t----------------------" << endl;

						cout << "Time complexity for quick sort with array size " << sizeofarray << " is:" << endl;
						auto start4 = chrono::high_resolution_clock::now();
						s.quicksort(a, 0, (sizeofarray - 1), order);
						auto finish4 = chrono::high_resolution_clock::now();
						chrono::duration<double> elapsed4 = finish4 - start4;
						cout << "  Time complexity->" << elapsed4.count();
						cout << "\n\t\t----------------------" << endl;
						print(a, sizeofarray);
						cout << "\n---------------------------------------------------" << endl;
						break;
					}
				}
			}
			else if (choiceOfSort == 4)
			{
				RadixSortAlgo obj;
				int max = 0;
				if (choiceOfDataType == 1)
				{
					long* arr = new long[sizeofarray];
					cout << "Length of Array  (digits wise):";
					cin >> max;
					cout << "Enter the array to be sorted: " << endl;
					cout << "  Array->";
					for (int i = 0; i < sizeofarray; i++)
					{
						cin >> arr[i];
					}
					cout << "---------------------------------------------------" << endl;
					cout << "Time complexity for radix sort with array size " << sizeofarray << " is:" << endl;
					auto start = chrono::high_resolution_clock::now();
					obj.radixSortLong(arr, (sizeofarray), max);
					auto finish = chrono::high_resolution_clock::now();
					chrono::duration<double> elapsed = finish - start;
					cout << "  Time complexity->" << elapsed.count();
					cout << "\n---------------------------------------------------" << endl;
					obj.print(arr, sizeofarray, order);
					cout << "\n---------------------------------------------------" << endl;

				}
				else if (choiceOfDataType == 2)
				{
					float* arr = new float[sizeofarray];
					cout << "Length of Array  (digits wise):";
					cin >> max;
					cout << "Enter the array to be sorted: " << endl;
					cout << "  Array->";
					for (int i = 0; i < sizeofarray; i++)
					{
						cin >> arr[i];
					}
					cout << "---------------------------------------------------" << endl;
					cout << "Time complexity for radix sort with array size " << sizeofarray << " is:" << endl;
					auto start = chrono::high_resolution_clock::now();
					obj.radixSortF(arr, (sizeofarray), max);
					auto finish = chrono::high_resolution_clock::now();
					chrono::duration<double> elapsed = finish - start;
					cout << "  Time complexity->" << elapsed.count();
					cout << "\n---------------------------------------------------" << endl;
					obj.print(arr, sizeofarray, order);
					cout << "\n---------------------------------------------------" << endl;
				}
				else if (choiceOfDataType == 3)
				{
					string* arr = new string[sizeofarray];
					cout << "Length of Array  (digits wise):";
					cin >> max;
					cout << "Enter the array to be sorted: " << endl;
					cout << "  Array->";
					for (int i = 0; i < sizeofarray; i++)
					{
						cin >> arr[i];
					}
					cout << "---------------------------------------------------" << endl;
					cout << "Time complexity for radix sort with array size " << sizeofarray << " is:" << endl;
					auto start = chrono::high_resolution_clock::now();
					obj.radixSortS(arr, (sizeofarray));
					auto finish = chrono::high_resolution_clock::now();
					chrono::duration<double> elapsed = finish - start;
					cout << "  Time complexity->" << elapsed.count();
					cout << "\n---------------------------------------------------" << endl;
					obj.print(arr, sizeofarray, order);
					cout << "\n---------------------------------------------------" << endl;
				}

			}
			cout << "\t\t     Exit Menu?" << endl;
			cout << "1-Exit\n2-Return to previous Menu\n";
			cout << "  Choice->";
			cin >> choice2;
			cout << "---------------------------------------------------" << endl;
			if (choice2 == 2)
			{
				system("cls");
			}

			if (choice2 == 1)
			{
				cout << "Thank you for having our service :)\n";
				cout << "---------------------------------------------------" << endl;
				break;
			}
			else
			{
				continue;
			}
		}
	}
};


int main()
{
	int choice;
	cout << "Main Menu for displaying time complexity of diff. Algos." << endl;
	cout << "---------------------------------------------------" << endl;
	cout << "Select the type in which you want to sort:\n1- Long\n2- Float\n3- String\n";
Again:
	cout << "   Type->";
	cin >> choice;
	cout << "---------------------------------------------------" << endl;
	if (choice == 1)
	{
		SortAlgos<long> s;
		s.Options(choice);
	}
	else if (choice == 2)
	{
		SortAlgos<float> s;
		s.Options(choice);
	}
	else if (choice == 3)
	{
		SortAlgos<string> s;
		s.Options(choice);
	}
	else
	{
		cout << "Invalid Entry.Please enter again." << endl;
		goto Again;
	}
	return 0;
}