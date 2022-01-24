#include "Heap.h"

#include <fstream>
#include <iostream>

	int Heap::parent(int child)
	{
		return (child - 1) / 2;
	}

	int Heap::left(int parent) const
	{
		const int l = 2 * parent + 1;
		if (l < size)
			return l;
		else
			return -1;
	}

	int Heap::right(int parent) const
	{
		const int r = 2 * parent + 2;
		if (r < size)
			return r;
		else
			return -1;
	}

	int Heap::parentv2(int child)
	{
		int p = (child - 1) / 2;
		if (child == 0)
			return -1;
		else
			return p;
	}

	void Heap::heapify_up(int index) const
	{
		while (index > 0)
		{
			if (heap_array[parent(index)] > heap_array[index])
			{
				const int temp = heap_array[parent(index)];
				heap_array[parent(index)] = heap_array[index];
				heap_array[index] = temp;
			}
			index = parent(index);
		}
	}

	void Heap::heapify_down(int in, int n)
	{

		int child = left(in);
		const int child1 = right(in);
		if (child >= 0 && child1 >= 0 && heap_array[child] > heap_array[child1] && child < n)
		{
			child = child1;
		}
		if (child > 0 && heap_array[child] < heap_array[in] && child <= n)
		{
			const int temp = heap_array[in];
			heap_array[in] = heap_array[child];
			heap_array[child] = temp;

			heapify_down(child, n);
		}
	}

	int Heap::heap_size() const
	{
		return size;
	}

	void Heap::delete_element(int index)
	{
		if (index >= 0 && index <= size)
		{
			for (int i = index; i < size; ++i)
				heap_array[i] = heap_array[i + 1];
			size = size - 1;
			int* new_heap_array = new int[size];
			for (int i = 0; i < size; i++)
				new_heap_array[i] = heap_array[i];
			delete[] heap_array;
			heap_array = new_heap_array;
			next_index--;
		}
		else
			cout << "Wrong index" << endl;
	}

	void Heap::add_element(const int nowy)
	{
		if (next_index == size) {
			size = size + 1;
			int* new_heap_array = new int[size];
			for (int i = 0; i < size - 1; i++)
				new_heap_array[i] = heap_array[i];
			delete[] heap_array;
			heap_array = new_heap_array;
		}
		heap_array[next_index++] = nowy;
	}

	void Heap::insert(int data)
	{
		add_element(data);
		heapify_up(heap_size() - 1);
	}

	void Heap::delete_min(int index)
	{
		if (size == 0)
		{
			cout << "Heap is Empty" << endl;
			return;
		}
		heap_array[index] = heap_array[size - 1];
		delete_element(size - 1);
		heapify_down(index, heap_size() - 1);
	}

	void Heap::display_heap() const
	{
		cout << "Heap -->  ";
		for (int i = 0; i <= size - 1; i++)
			cout << heap_array[i] << " ";
		cout << endl;
	}

	void Heap::heap_sort(bool if_reverse)
	{
		int* new_heap_array = new int[size];
		if (size > 0)
		{
			for (int i = 0; i < size; i++)
				new_heap_array[i] = heap_array[i];
			int end = heap_size() - 1;
			while (end > 0)
			{
				const int temp = heap_array[0];
				heap_array[0] = heap_array[end];
				heap_array[end] = temp;
				end--;
				heapify_down(0, end);
			}
			if (if_reverse == false)
				display_heap();
			else
			{
				reverse();
				display_heap();
			}
			for (int i = 0; i < size; i++)
				heap_array[i] = new_heap_array[i];
			delete[] new_heap_array;
		}
	}

	void Heap::print_smaller(int x, int pos)
	{
		if (pos >= size)
			return;

		if (heap_array[pos] >= x)
			return;

		cout << heap_array[pos] << " ";

		print_smaller(x, (2 * pos + 1));
		print_smaller(x, (2 * pos + 2));
	}

	void Heap::save_array() const
	{
		ofstream myfile("saved_heap.txt");
		if (myfile.is_open())
		{
			for (int count = 0; count < size; count++) {
				myfile << heap_array[count] << " ";
			}
			myfile.close();
			cout << "File saved" << endl;
		}
		else cout << "Unable to open the file";
	}

	void Heap::reverse()
	{
		int i = 0;
		int j = size - 1;

		while (i < j)
		{
			int temp = heap_array[i];
			heap_array[i] = heap_array[j];
			heap_array[j] = temp;
			i++;
			j--;
		}
	}

	void Heap::clear()
	{
#if defined _WIN32
		system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
		system("clear");
#elif defined (__APPLE__)
		system("clear");
#endif
	}

	int Heap::choice()
	{
		while (true)
		{
			cout << "------------------" << endl;
			cout << "Choose The Operation on Heap" << endl;
			cout << "------------------" << endl;
			cout << "1.Insert Element" << endl;
			cout << "2.Delete Minimum Element" << endl;
			cout << "3.Delete Element With Chosen Index" << endl;
			cout << "4.Sort From Max to Min" << endl;
			cout << "5.Sort From Min to Max" << endl;
			cout << "6.Print Heap" << endl;
			cout << "7.Print all nodes less than..." << endl;
			cout << "8.Save heap to file" << endl;
			cout << "9.Exit" << endl;

			int choice;
			cout << "Enter your choice: ";
			cin >> choice;
			switch (choice)
			{
				int element;
			case 1:
				cout << "Enter the element to be inserted: ";
				cin >> element;
				insert(element);
				clear();
				break;
			case 2:
				delete_min(0);
				clear();
				break;
			case 3:
				int chosen_index;
				cin >> chosen_index;
				if (chosen_index <= heap_size() - 1)
					delete_min(chosen_index);
				else
					cout << "Wrong Index" << endl;
				clear();
				break;
			case 4:
				clear();
				heap_sort(false);
				break;
			case 5:
				clear();
				heap_sort(true);
				break;
			case 6:
				clear();
				cout << "Displaying elements of Heap:  ";
				display_heap();
				break;
			case 7:
				cout << "Choose: " << endl;
				cin >> element;
				clear();
				cout << "Smaller than " << element << " are: ";
				print_smaller(element);
				cout << endl;
				break;
			case 8:
				clear();
				save_array();
				break;
			case 9:
				return 0;
			default:
				clear();
				cout << "Enter Correct Choice" << endl;
			}
		}
	}

