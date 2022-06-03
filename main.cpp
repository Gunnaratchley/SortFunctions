#include <functional>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <vector>

// Very good visualization of these sorts - 
// https://www.hackerearth.com/practice/algorithms/sorting/bubble-sort/tutorial/

// Another good visualization of sorts - 
// http://algostructure.com/index.php


template <typename T>
void bubble_sort(std::vector<T>& list)
{
	for (auto index = 0U; index < list.size() - 1; index++) {
		for (auto inner_index = 0U; inner_index < list.size() - index - 1; inner_index++) {
			if (list[inner_index] > list[inner_index + 1]) {
				std::swap(list[inner_index], list[inner_index + 1]);
			} // else, the items are in order, do_nothing();
		}
	}
}

/**
 * cocktail (shaker) sort (bidirectional bubble sort)
 * No real improvements over the bubble sort, sorts the bubbles both ways.
 */
template <typename T>
void cocktail_sort(std::vector<T>& list) {
	auto was_swapped = false;
	auto index = 0U;
	while (index < list.size() / 2 || !was_swapped) {
		for (auto up_index = index; up_index < list.size() - index - 1; up_index++) { //one way
			if (list[up_index] < list[up_index + 1]) {
				std::swap(list[up_index], list[up_index + 1]);
				was_swapped = true;
			} // else, the values are in order, do_nothing();
		}

		for (auto down_index = list.size() - 2 - index; down_index > index; --down_index) { //and back
			if (list[down_index] > list[down_index - 1]) {
				std::swap(list[down_index], list[down_index - 1]);
				was_swapped = true;
			} // else, the values are in order, do_nothing();
		}

		index++;
	}
}


/**
 * Internal method that merges two sorted halves of a sub array.
 * list is an array of Comparable items.
 * temp is an array to place the merged result.
 * left_index is the left-most index of the sub array.
 * right_index is the index of the start of the second half.
 * right_end_index is the right-most index of the sub array.
 */
template <typename Comparable>
void merge(std::vector<Comparable>& list,
	std::vector<Comparable>& temp,
	int left_index, int right_index, int right_end_index)
{
	const auto left_end_index = right_index - 1;
	auto temp_index = left_index;
	const auto num_elements = right_end_index - left_index + 1;

	while (left_index <= left_end_index && right_index <= right_end_index) {
		if (list[left_index] <= list[right_index]) {
			temp[temp_index++] = std::move(list[left_index++]);
		}
		else {
			temp[temp_index++] = std::move(list[right_index++]);
		}
	}
	while (left_index <= left_end_index) {   // Copy rest of first half
		temp[temp_index++] = std::move(list[left_index++]);
	}

	while (right_index <= right_end_index) { // Copy rest of right half
		temp[temp_index++] = std::move(list[right_index++]);
	}

	for (auto index = 0; index < num_elements; ++index, --right_end_index) {
		list[right_end_index] = std::move(temp[right_end_index]);
	}
}

/**
 * Internal method that makes recursive calls.
 * list is an vector of Comparable items.
 * temp is an vector to place the merged result.
 * left is the left-most index of the sub array.
 * right is the right-most index of the sub array.
 */
template <typename Comparable>
void merge_sort(std::vector<Comparable>& list,
	std::vector<Comparable>& temp, int left, int right)
{
	if (left < right) {
		auto center = (left + right) / 2;
		merge_sort(list, temp, left, center);
		merge_sort(list, temp, center + 1, right);
		merge(list, temp, left, center + 1, right);
	} // else, left is past right, nothing to merge, do_nothing();
}

/**
 * Mergesort algorithm (This is the method we call which actually drives the sort).
 */
template <typename Comparable>
void merge_sort(std::vector<Comparable>& list)
{
	std::vector<Comparable> temp(list.size());
	merge_sort(list, temp, 0, list.size() - 1);
}

// Very good visualization
// https://www.cs.usfca.edu/~galles/visualization/RadixSort.html
template <typename T>
void radix_sort(std::vector<T>& list, const int digit_count = 10)
{
	const int radix = 10;
	auto vector_index = 0U;
	auto queue_index = 0;
	std::queue<T> queues[radix];
	for (auto digit_index = 0, factor = 1; digit_index < digit_count; factor *= radix, digit_index++) {
		for (vector_index = 0; vector_index < list.size(); vector_index++) {
			queues[(list[vector_index] / factor) % radix].push(list[vector_index]);
		}
		for (vector_index = queue_index = 0; vector_index < radix; vector_index++) {
			while (!queues[vector_index].empty()) {
				list[queue_index++] = queues[vector_index].front();
				queues[vector_index].pop();
			}
		}
	}
}


// Also know as a Shell Sort with a gap of 1. 
// This sort is O(n^2), however, it is VERY fast if the data is almost sorted. 
// Good for (N <= 10)
// https://www.khanacademy.org/computing/computer-science/algorithms/insertion-sort/a/insertion-sort
template <typename T>
void insertion_sort(std::vector<T>& list)
{
	for (auto outer_index = 1; outer_index < list.size(); ++outer_index) {
		auto temp = std::move(list[outer_index]);

		auto inner_index = 0;
		for (inner_index = outer_index;
			inner_index > 0 && temp < list[inner_index - 1];
			--inner_index) {
			list[inner_index] = std::move(list[inner_index - 1]);
		}

		list[inner_index] = std::move(temp);
	}
}

/**
 * Internal insertion sort routine for sub lists used by quick_sort.
 * left is the left-most index of the sub list.
 * right is the right-most index of the sub list.
 */
template <typename T>
void insertion_sort(std::vector<T>& list, int left, int right)
{
	for (auto outer_index = left + 1; outer_index <= right; ++outer_index)
	{
		auto temp = std::move(list[outer_index]);
		auto inner_index = 0;

		for (inner_index = outer_index;
			inner_index > left && temp < list[inner_index - 1];
			--inner_index) {
			list[inner_index] = std::move(list[inner_index - 1]);
		}

		list[inner_index] = std::move(temp);
	}
}



/**
 * Shell sort, using Shell's (poor) increments.
 * Many different types of gaps that can be used. The best seems to be a set defined by
 * Ciura 2001 - 1,4,10,23,57,132,301, 701 - The actual running time is unknown
 * and those gaps are defined experimentally
 * http://sun.aei.polsl.pl/~mciura/publikacje/shellsort.pdf
 * My favourite short (good for N < 10,000)
 * The Shell sort is the generalization of insertion sort which
 * mitigates the slowness of the insertion sort by comparing elements
 * separated by a gap of several positions.
 * Remember, the insertion sort is very fast for values which are ALMOST sorted.
 * The insertion sort is the shell sort with a gap of 1. The shell sort sorts every
 * nth element. So as it run the data becomes more and more sorted to the point that each element
 * is very close to its final position so the insertion sort can then run (gap = 1) very fast.
 */
template <typename T>
void shell_sort(std::vector<T>& list)
{
	for (auto gap = list.size() / 2; gap > 0; gap /= 2) {
		for (auto outer_index = gap; outer_index < list.size(); ++outer_index) {
			auto temp = std::move(list[outer_index]);
			auto inner_index = outer_index;

			for (; inner_index >= gap && temp < list[inner_index - gap]; inner_index -= gap) {
				list[inner_index] = std::move(list[inner_index - gap]);
			}

			list[inner_index] = std::move(temp);
		}
	}
}


/**
 * Return median of left, center, and right.
 * Order these and hide the pivot.
 */
template <typename T>
const T& median_of_three(std::vector<T>& list, int left, int right)
{
	auto center = (left + right) / 2;

	if (list[center] < list[left]) {
		std::swap(list[left], list[center]);
	} // else, they are in order, do_nothing();

	if (list[right] < list[left]) {
		std::swap(list[left], list[right]);
	} // else, they are in order, do_nothing();

	if (list[right] < list[center]) {
		std::swap(list[center], list[right]);
	} // else, they are in order, do_nothing();

	// Place pivot at position right - 1
	std::swap(list[center], list[right - 1]);
	return list[right - 1];
}

/**
 * Internal quick_sort method that makes recursive calls.
 * Uses median-of-three partitioning and a cutoff of 10.
 * a is an array of T items.
 * left is the left-most index of the sub list.
 * right is the right-most index of the sub list.
 * https://www.khanacademy.org/computing/computer-science/algorithms/quick-sort/a/overview-of-quicksort
 */
template <typename T>
void quick_sort(std::vector<T>& list, int left, int right)
{
	if (left + 5 <= right)
	{
		const auto& pivot = median_of_three(list, left, right);

		// Begin partitioning
		auto left_index = left, right_index = right - 1;
		auto isStillPartitioning = true;
		while (isStillPartitioning) {
			while (list[++left_index] < pivot) {}
			while (pivot < list[--right_index]) {}
			if (left_index < right_index) {
				std::swap(list[left_index], list[right_index]);
			}
			else {
				isStillPartitioning = false;
			}
		}

		std::swap(list[left_index], list[right - 1]);  // Restore pivot
		quick_sort(list, left, left_index - 1);     // Sort small elements
		quick_sort(list, left_index + 1, right);    // Sort large elements
	}
	else {  // Do an insertion sort on the sub list the size is small enough to use it
		insertion_sort(list, left, right);
	}
}

/**
 * Quick sort algorithm (driver).
 * This is the best general purpose sorting algorithm we have
 * Depending on the implementation we have to be aware of inversely sorted data.
 * The best sorting algorithm we have (general purpose) is the tim_sort developed
 * in 2002 by Tim Peter.
 */
template <typename T>
void quick_sort(std::vector<T>& list)
{
	quick_sort(list, 0, list.size() - 1);
}

void fill_vector(std::vector<int>& list, const size_t size)
{
	list.clear();
	std::srand(std::time(nullptr));
	for (auto index = 0U; index < size; index++) {
		list.push_back(std::rand() % 100);
	}
}

template <typename T>
void display_list(const std::vector<T>& list)
{
	for (auto element : list) {
		std::cout << element << " ";
	}
	std::cout << std::endl;
}

int main()
{

	std::vector<int> list;
	fill_vector(list, 20);
	display_list(list);
	//radix_sort(list, 2);
	//merge_sort(list);
	//bubble_sort(list);
	cocktail_sort(list);
	display_list(list);
	return 0;
}