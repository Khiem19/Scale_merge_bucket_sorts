#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <iomanip>

using namespace std;

////////////////////////// struct/////////////////////////////////////////////

struct element
{
	string movie;
	int rating;
};

//////////////////////// Read CSV to vector ////////////////////////////////////

vector<element> readfile()
{
	vector<element> blabla;

	ifstream myFile;
	myFile.open("projekt2_dane.csv");
	string line;
	getline(myFile, line);
	while (getline(myFile, line, ','))
	{
		element bloblo;
		line.erase();

		getline(myFile, line);

		vector<string> v;
		stringstream ss(line);

		while (ss.good())
		{
			string substr;
			getline(ss, substr, ',');
			v.push_back(substr);
		}

		for (int i = v.size() - 2; i >= 0; i--)
		{
			bloblo.movie = v[i] + bloblo.movie;
		}

		if (!v[v.size() - 1].empty()) {
			bloblo.rating = stoi(v[v.size() - 1]);
		}

		blabla.push_back(bloblo);
	}
	return blabla;
}

///////////////////// Merge ///////////////////////////////////////

// the interval from [s to m] and [m+1 to e] in v are sorted
// the function will merge both of these intervals
// such the interval from [s to e] in v becomes sorted

void MergeSortedIntervals(vector<element> &v, int s, int m, int e)
{
	// temp is used to temporary store the vector obtained by merging
	// elements from [s to m] and [m+1 to e] in v
	vector<element> temp;
	int i, j;
	i = s;
	j = m + 1;

	while (i <= m && j <= e)
	{
		if (v[i].rating <= v[j].rating)
		{
			temp.push_back(v[i]);
			++i;
		}
		else
		{
			temp.push_back(v[j]);
			++j;
		}
	}
	while (i <= m)
	{
		temp.push_back(v[i]);
		++i;
	}
	while (j <= e)
	{
		temp.push_back(v[j]);
		++j;
	}
	for (int i = s; i <= e; ++i)
	{
		v[i] = temp[i - s];
	}
}

// the MergeSort function
// Sorts the array in the range [s to e] in v using
// merge sort algorithm

void MergeSort(vector<element> &v, int s, int e)
{
	if (s < e)
	{
		int m = (s + e) / 2;
		MergeSort(v, s, m);
		MergeSort(v, m + 1, e);
		MergeSortedIntervals(v, s, m, e);
	}
}

///////////////////// Quick Sort /////////////////////////////////

// void swap(element *a, element *b)
// {
//     element t = *a;
//     *a = *b;
//     *b = t;
// }

// // last element is taken as pivot
// int partition(vector<element> &v, int l, int h)
// {
//     int x = v[h].rating;
//     int i = (l - 1);
 
//     for (int j = l; j <= h - 1; j++) {
//         if (v[j].rating <= x) {
//             i++;
//             swap(&v[i], &v[j]);
//         }
//     }
//     swap(&v[i + 1], &v[h]);
//     return (i + 1);
// }

// void Quicksort(vector<element> &v, int l, int h)
// {
//     // Create an auxiliary stack
//     int stack[h - l + 1];
 
//     // initialize top of stack
//     int top = -1;
	
//     // push initial values of l and h to stack
//     stack[++top] = l;
//     stack[++top] = h;
 
//     // Keep popping from stack while is not empty
//     while (top >= 0) {
//         // Pop h and l
//         h = stack[top--];
//         l = stack[top--];
 
//         // Set pivot element at its correct position
//         // in sorted array
//         int p = partition(v, l, h);
 
//         // If there are elements on left side of pivot,
//         // then push left side to stack
//         if (p - 1 > l) {
//             stack[++top] = l;
//             stack[++top] = p - 1;
//         }
 
//         // If there are elements on right side of pivot,
//         // then push right side to stack
//         if (p + 1 < h) {
//             stack[++top] = p + 1;
//             stack[++top] = h;
//         }
//     }
// }

// last element is taken as pivot
 int Partition(vector<element> &v,  int start,  int end){
	
	 int pivot = end;
	 int j = start;
	for( int i=start;i<end;++i){
		if(v[i].rating < v[pivot].rating){
			swap(v[i],v[j]);
			++j;
		}
	}
	swap(v[j],v[pivot]);
	return j;
}

void Quicksort(vector<element> &v,  int start,  int end ){   
	if(start<end){
		 int p = Partition(v,start,end);
		Quicksort(v,start,p-1);
		Quicksort(v,p+1,end);
	}	
}

//////////////////////////////Bucket sort ///////////////////////////

void bucketSort(vector<element> &v, int n)
{
	// 1) Create n empty buckets
	vector<element> bucket1;
	vector<element> bucket2;
	vector<element> bucket3;

	// 2) Put array elements in different buckets
	for (int i = 0; i < n; i++)
	{
		if (v[i].rating <= 3)
		{
			bucket1.push_back(v[i]);
		}
		else if (v[i].rating > 3 && v[i].rating <= 7)
		{
			bucket2.push_back(v[i]);
		}
		else
		{
			bucket3.push_back(v[i]);
		}
	}

	// 3) and sort them
	MergeSort(bucket1, 0, bucket1.size() - 1);
	MergeSort(bucket2, 0, bucket2.size() - 1);
	MergeSort(bucket3, 0, bucket3.size() - 1);

	// 4) Merge them
	v.clear();
	v.reserve(bucket1.size() + bucket2.size() + bucket3.size());
	v.insert(v.end(), bucket1.begin(), bucket1.end());
	v.insert(v.end(), bucket2.begin(), bucket2.end());
	v.insert(v.end(), bucket3.begin(), bucket3.end());
}

//////////////////////////// Display vector //////////////////////////

void PrintVector(vector<element> &v, int n)
{
	fstream new_txt;
	new_txt.open("Testing.txt", ios::out); // otworzyc nowy *.txt
	if (new_txt.is_open())
	{
		for (int i = 0; i < n; ++i)
		{
			new_txt << v[i].movie << " "
					<< "[" << v[i].rating << "]" << endl;
		}
	}
	new_txt.close();
}
////////////////////////// A V E R A G E R A T I N G ////////////////

void average_rate(vector<element> &v, int n)
{
	int sum = 0;
	float average;
	for (int i = 0; i < n; i++)
	{
		sum += v[i].rating;
	}
	average = (float)sum / (float)n;
	cout << "Average: " << average << endl;
}

/////////////////////////M E D I A N/////////////////////////////

void median_rate(vector<element> &v, int n){
	int median;
	
	median = (v[n/2].rating + v[(n/2)+1].rating)/2;
	cout << "Median ocen:" << median << endl;
	
}

////////////////////////////// M E N U //////////////////////////////

void menuScale(vector<element> &v)
{

	int choiceScale;

	do
	{
		cout << endl;
		cout << "\t\tMENU :" << endl;
		cout << "Wybieraj ilosc danych z pliku excel:" << endl;
		cout << "[1] 10k" << endl;
		cout << "[2] 100k" << endl;
		cout << "[3] 500k" << endl;
		cout << "[4] 1M" << endl;
		cout << "[5] EXIT" << endl;
		cout << "Twoj wybor: ";

		cin >> choiceScale;
		int n;
		clock_t start, end;
		switch (choiceScale)
		{
		case 1:
		{
			n = 10000;
			vector<element> temp;
			for (int i = 0; i < n; i++)
			{
				temp.push_back(v[i]);
			}
			start = clock();
			MergeSort(temp, 0, n - 1);
			end = clock();
			average_rate(temp, n);
			median_rate(temp, n);
			PrintVector(temp, n);
			break;
		}
		case 2:
		{
			n = 100000;
			vector<element> temp;
			for (int i = 0; i < n; i++)
			{
				temp.push_back(v[i]);
			}
			start = clock();
			MergeSort(temp, 0, n - 1);
			end = clock();
			average_rate(temp, n);
			median_rate(temp, n);
			// PrintVector(temp, n);
			break;
		}

		case 3:
		{
			n = 500000;
			vector<element> temp;
			for (int i = 0; i < n; i++)
			{
				temp.push_back(v[i]);
			}
			start = clock();
			MergeSort(temp, 0, n - 1);
			end = clock();
			average_rate(temp, n);
			median_rate(temp, n);
			// PrintVector(temp, n);
			break;
		}

		case 4:
		{
			n = 1000000;
			vector<element> temp;
			for (int i = 0; i < n; i++)
			{
				temp.push_back(v[i]);
			}
			start = clock();
			MergeSort(temp, 0, n - 1);
			end = clock();
			average_rate(temp, n);
			median_rate(temp, n);
			// PrintVector(temp, n);
			

			break;
		}

		case 5:
			break;

		default:
			break;
		}

		double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
		cout << "Time taken by program is : " << fixed
			 << time_taken << setprecision(3);
		cout << " sec " << endl;

	} while (choiceScale != 5);
}

void menuQuick(vector<element> &v)
{

	int choiceQuick;

	do
	{
		cout << endl;
		cout << "\t\tMENU :" << endl;
		cout << "Wybieraj ilosc danych z pliku excel:" << endl;
		cout << "[1] 10k" << endl;
		cout << "[2] 100k" << endl;
		cout << "[3] 500k" << endl;
		cout << "[4] 1M" << endl;
		cout << "[5] EXIT" << endl;
		cout << "Twoj wybor: ";

		cin >> choiceQuick;
		int n;
		clock_t start, end;
		switch (choiceQuick)
		{
		case 1:
		{
			n = 10000;
			vector<element> temp;
			for (int i = 0; i < n; i++)
			{
				temp.push_back(v[i]);
			}
			start = clock();
			Quicksort(temp, 0, n - 1); 
			end = clock();
			average_rate(temp, n);
			median_rate(temp, n);
			// PrintVector(temp, n);
			break;
		}

		case 2:
		{
			n = 100000;
			vector<element> temp;
			for (int i = 0; i < n; i++)
			{
				temp.push_back(v[i]);
			}
			start = clock();
			Quicksort(temp, 0, n - 1);
			end = clock();
			average_rate(temp, n);
			median_rate(temp, n);
			// PrintVector(temp, n);
			break;
		}

		case 3: 
		{
			n = 200000;
			vector<element> temp;
			for (int i = 0; i < n; i++)
			{
				temp.push_back(v[i]);
			}
			start = clock();
			Quicksort(temp, 0, temp.size() - 1); 
			end = clock();
			average_rate(temp, n);
			median_rate(temp, n);
			// PrintVector(temp, n);
			break;
		}

		case 4: 
		{
			n = 1000000;
			vector<element> temp;
			for (int i = 0; i < n; i++)
			{
				temp.push_back(v[i]);
			}
			start = clock();
			Quicksort(temp, 0, temp.size() - 1);
			end = clock();
			average_rate(temp, n);
			median_rate(temp, n);
			// PrintVector(temp, n);
			break;
		}

		case 5:
			break;

		default:
			break;
		}

		double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
		cout << "Time taken by program is : " << fixed
			 << time_taken << setprecision(3);
		cout << " sec " << endl;

	} while (choiceQuick != 5);
}

void menuBucket(vector<element> &v)
{

	int choiceBucket;

	do
	{
		cout << endl;
		cout << "\t\tMENU :" << endl;
		cout << "Wybieraj ilosc danych z pliku excel:" << endl;
		cout << "[1] 10k" << endl;
		cout << "[2] 100k" << endl;
		cout << "[3] 500k" << endl;
		cout << "[4] 1M" << endl;
		cout << "[5] EXIT" << endl;
		cout << "Twoj wybor: ";

		cin >> choiceBucket;
		int n;
		clock_t start, end;
		switch (choiceBucket)
		{
		case 1:
		{
			n = 10000;
			vector<element> temp;
			for (int i = 0; i < n; i++)
			{
				temp.push_back(v[i]);
			}
			start = clock();
			bucketSort(temp, n);
			end = clock();
			average_rate(temp, n);
			median_rate(temp, n);
			// PrintVector(temp, n);
			break;
		}

		case 2:
		{
			n = 100000;
			vector<element> temp;
			for (int i = 0; i < n; i++)
			{
				temp.push_back(v[i]);
			}
			start = clock();
			bucketSort(temp, n);
			end = clock();
			average_rate(temp, n);
			median_rate(temp, n);
			// PrintVector(temp, n);
			break;
		}

		case 3:
		{
			n = 500000;
			vector<element> temp;
			for (int i = 0; i < n; i++)
			{
				temp.push_back(v[i]);
			}
			start = clock();
			bucketSort(temp, n);
			end = clock();
			average_rate(temp, n);
			median_rate(temp, n);
			// PrintVector(temp, n);
			break;
		}

		case 4:
		{
			n = 1000000;
			vector<element> temp;
			for (int i = 0; i < n; i++)
			{
				temp.push_back(v[i]);
			}
			start = clock();
			bucketSort(temp, n);
			end = clock();
			average_rate(temp, n);
			median_rate(temp, n);
			// PrintVector(temp, n);
			break;
		}

		case 5:
			break;

		default:
			break;
		}

		double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
		cout << "Time taken by program is : " << fixed
			 << time_taken << setprecision(3);
		cout << " sec " << endl;

	} while (choiceBucket != 5);
}

///////////////////////// M A I N ///////////////////////////
int main()
{
	vector<element> bleble = readfile();
	int choice2;

	do
	{

		cout << endl;
		cout << "\t\tMENU :" << endl;
		cout << "Wybieraj Algorytmy:" << endl;
		cout << "[1] Scalanie" << endl;
		cout << "[2] Quicksort" << endl;
		cout << "[3] Kubelkowe" << endl;
		cout << "[5] EXIT" << endl;
		cout << "Twoj wybor: ";

		int n;
		cin >> choice2;

		switch (choice2)
		{
		case 1:
		{
			vector<element> temp = bleble;
			menuScale(temp);
			break;
		}
		case 2:
		{
			vector<element> temp = bleble;
			menuQuick(temp);
			break;
		}
		case 3:
		{
			vector<element> temp = bleble;
			menuBucket(temp);
			break;
		}
		case 5:
			break;

		default:
			break;
		}
	} while (choice2 != 5);
	return 0;
}