// Sorting.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>

using namespace std;

void swapping(int& a, int& b) { 
    int temp;
    temp = a;
    a = b;
    b = temp;
}
void merge(int* array, int l, int m, int r) {
    int i = 0; 
    int j = 0;
    int k = 0;
    int nl = 0;
    int nr = 0;
    //size of left and right sub-arrays
    nl = m - l + 1; nr = r - m;
    int* larr = new int[nl];
    int* rarr= new int[nr];
    //fill left and right sub-arrays
    for (i = 0; i < nl; i++)
    { 
        larr[i] = array[l + i];
    }
        
    for (j = 0; j < nr; j++)
    {
        rarr[j] = array[m + 1 + j];
    }
        
    i = 0; j = 0; k = l;
    
    while (i < nl && j < nr) {
        if (larr[i] <= rarr[j]) {
            array[k] = larr[i];
            i++;
        }
        else {
            array[k] = rarr[j];
            j++;
        }
        k++;
    }
    while (i < nl) {       //extra element in left array
        array[k] = larr[i];
        i++; k++;
    }
    while (j < nr) {     //extra element in right array
        array[k] = rarr[j];
        j++; k++;
    }
}
void mergeSort(int* array, int l, int r) {
    int m;
    if (l < r) {
        int m = (r + l) / 2;
        mergeSort(array, l, m);
        mergeSort(array, m + 1, r);
        merge(array, l, m, r);
    }
}

void bublesort(int* &theNumbers, int size)
{
    for (unsigned int i = 0; i < size - 1; i++)
    {
        for (unsigned int j = 0; j < size - i - 1; j++)
        {  //compare an element and its adjacent element
            if (theNumbers[j] > theNumbers[j + 1])
            {
                int a = theNumbers[j + 1];
                theNumbers[j + 1] = theNumbers[j];
                theNumbers[j] = a;
            }
        }
    }
}

void selection(int* theNumbers, int size)
{
    for (unsigned int i = 0; i < size - 1; i++)
    {
        int min;
        for (unsigned int j = i + 1; j < size; j++)
        {
            min = i;
            if (theNumbers[min] > theNumbers[j])
            {
                min = j;
                int temp = theNumbers[j];
                theNumbers[j] = theNumbers[i];
                theNumbers[i] = temp;
            }
        }
    }
}

void menu(int* arr1, int* arr2, int* arr3, int* arr4, int* arr5, int size)
{ 
   cout << "1.bubleSort 2.selectionSort 3.mergeSort " << endl;
    int input;
    cin >> input;
    if (input == 0)
    {
        exit(0);
    }
    else if (input == 1) 
    {
        cout << "bubble Sort"<<endl;
        auto start1 = chrono::steady_clock::now();
        bublesort(arr1, size);
        auto end1 = chrono::steady_clock::now();
       // auto start2 = chrono::steady_clock::now();
        bublesort(arr2, size);
        auto end2 = chrono::steady_clock::now();
        //auto start3 = chrono::steady_clock::now();
        bublesort(arr3, size);
        auto end3 = chrono::steady_clock::now();
        bublesort(arr4, size);
        auto end4 = chrono::steady_clock::now();
        bublesort(arr5,size);
        auto end5 = chrono::steady_clock::now();
        auto t1 = chrono::duration_cast<chrono::microseconds>(end1 - start1).count();
        auto t2 = chrono::duration_cast<chrono::microseconds>(end2 - end1).count();
        auto t3 = chrono::duration_cast<chrono::microseconds>(end3 - end2).count();
        auto t4 = chrono::duration_cast<chrono::microseconds>(end4 - end3).count();
        auto t5 = chrono::duration_cast<chrono::microseconds>(end5 - end4).count();
        cout << "size  :" << size << endl;
        cout << "Elapsed time in microseconds : " << (t1 + t2 + t3 + t4 + t5) / 5 << " µs" << endl;
    }
    else if (input == 2) 
    {
        cout << "selection Sort" << endl;
        auto start1 = chrono::steady_clock::now();
        selection(arr1, size);
        auto end1 = chrono::steady_clock::now();
        //auto start2 = chrono::steady_clock::now();
        selection(arr2, size);
        auto end2 = chrono::steady_clock::now();
        //auto start3 = chrono::steady_clock::now();
        selection(arr3, size);
        auto end3 = chrono::steady_clock::now();
        selection(arr4,size);
        auto end4 = chrono::steady_clock::now();
        selection(arr5, size);
        auto end5 = chrono::steady_clock::now();
        auto t1 = chrono::duration_cast<chrono::microseconds>(end1 - start1).count();
        auto t2 = chrono::duration_cast<chrono::microseconds>(end2 - end1).count();
        auto t3 = chrono::duration_cast<chrono::microseconds>(end3 - end2).count();
        auto t4 = chrono::duration_cast<chrono::microseconds>(end4 - end3).count();
        auto t5 = chrono::duration_cast<chrono::microseconds>(end5 - end4).count();
        cout << "size  :" << size << endl;
        cout << "Elapsed time in microseconds : " << (t1 + t2 + t3 + t4 + t5) / 5 << " µs" << endl;
    }
    else if (input == 3) 
    {
        cout << "merge Sort" << endl;
        auto start1 = chrono::steady_clock::now();
        mergeSort(arr1, 0, size-1);
        auto end1 = chrono::steady_clock::now();
        //auto start2 = chrono::steady_clock::now();
        mergeSort(arr2, 0, size-1);
        auto end2 = chrono::steady_clock::now();
        //auto start3 = chrono::steady_clock::now();
        mergeSort(arr3, 0, size-1);
        auto end3 = chrono::steady_clock::now();
        mergeSort(arr4, 0, size - 1);
        auto end4 = chrono::steady_clock::now();
        mergeSort(arr5, 0, size - 1);
        auto end5 = chrono::steady_clock::now();
        auto t1 = chrono::duration_cast<chrono::microseconds>(end1 - start1).count();
        auto t2 = chrono::duration_cast<chrono::microseconds>(end2 - end1).count();
        auto t3 = chrono::duration_cast<chrono::microseconds>(end3 - end2).count();
        auto t4 = chrono::duration_cast<chrono::microseconds>(end4 - end3).count();
        auto t5 = chrono::duration_cast<chrono::microseconds>(end5 - end4).count();
        cout << "size  :" << size << endl;
        cout << "Elapsed time in microseconds : " << (t1 + t2 + t3+t4+t5) / 5 << " µs" << endl;
    }
}

int main()
{
    //vector<int> theData = readarray();
    ifstream file1;
    ofstream ofile;
    string filename = "rand10.txt";
    int input = 5;
    int size=0;
    int* arr=nullptr;
    int* arr2 = nullptr;
    int* arr3 = nullptr;
    int* arr4 = nullptr;
    int* arr5 = nullptr;
    int i = 0;
    int a;
    
        cout << "What is the file size?" << endl;
        cout << "0.example 1.10000 2.20000 3.50000 4.100000" << endl;
        cin >> input;
        if (input == 0)
        {
            size = 10;
            arr = new int[size];
            filename = "rand10.txt";
            file1.open("bin/" + filename);
            while (file1 >> a)
            {
                arr[i]=a;
                i++;
            }
        }
        else if (input == 1)
        {
            size = 10000;
            arr = new int[size];
            filename = "rand10000.txt";
            file1.open("bin/" + filename);
            for (int i = 0; i < size; i++)
            {
                file1 >> a;
                arr[i]=a;
            }
        }
        else if (input == 2)
        {
            size = 20000;
            arr = new int[size];
            filename = "rand20000.txt";
            file1.open("bin/" + filename);
            for (int i = 0; i < size; i++)
            {
                file1 >> a;
                arr[i] = a;
            }
        }
        else if (input == 3)
        {
            size = 50000;
            arr = new int[size];
            filename = "rand50000.txt";
            file1.open("bin/" + filename);
            for (int i = 0; i < size; i++)
            {
                file1 >> a;
                arr[i] = a;
            }
        }
        else if (input == 4)
        {
            size = 100000;
            arr = new int[size];
            filename = "rand100000.txt";
            file1.open("bin/" + filename);
            for (int i = 0; i < size; i++)
            {
                file1 >> a;
                arr[i] = a;
            }
        }
        arr2 = new int[size]; arr3 = new int[size];
        arr4 = new int[size]; arr5 = new int[size];
        for (int i=0; i<size;i++) 
        {
            arr2[i] = arr[i]; arr3[i] = arr[i];
            arr4[i] = arr[i]; arr5[i] = arr[i];
        }

        menu(arr, arr2, arr, arr, arr, size);

        file1.close();
        ///saves output
        ofile.open("output/" + filename);
        for (int j = 0; j < size; j++)
        {
            ofile << arr[j] << endl;
        }
        i = 0;
        ofile.close();
}