#pragma once
#ifndef Heap_h
#define Heap_h
#include <fstream>
#include <iostream>

using namespace std;

class Heap
{
	int size;
	int* heap_array;
	int next_index;

	static int parent(int child);
	int left(int parent) const;
	int right(int parent) const;
	static int parentv2(int child);
	void heapify_up(int index) const;
	void heapify_down(int in, int n);
	int heap_size() const;
	void delete_element(int index);
	void add_element(const int nowy);


public:
	Heap() : size(1), heap_array(new int[size]), next_index(0)
	{
		fstream plik("saved_heap.txt");
	}
	Heap(const Heap& heap) : size(heap.size), next_index(heap.next_index)
	{
	}

	~Heap()
	{
		delete[] heap_array;
	}

	void insert(int data);
	void delete_min(int index);
	void display_heap() const;
	void heap_sort(bool if_reverse);
	void print_smaller(int x, int pos = 0);
	void save_array() const;
	void reverse();
	static void clear();
	int choice();
};
#endif
