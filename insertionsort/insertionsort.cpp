#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <string>

// ListType is an STL container
template <typename ValueType, typename IterType>
void display_list(IterType b, IterType e, const std::string& msg, std::ostream& os)
{
		os << msg;
		std::copy(b, e, std::ostream_iterator<ValueType>(os, " "));
		os << std::endl;
}

void out_of_place_sort()
{
		int numbers[] = {13, 7, 88, 43, 7, 9, 95, 37, 16, 14};
		std::list<int> unsorted;
		
		std::copy(numbers, numbers + sizeof(numbers)/sizeof(int),
						std::back_inserter(unsorted));
		display_list<int, std::list<int>::const_iterator >(unsorted.begin(), unsorted.end(), "Unsorted list: ", std::cout);

		std::list<int> sorted;

		std::list<int>::const_iterator pos_unsorted = unsorted.begin(),
				end_unsorted = unsorted.end();

		for (; pos_unsorted != end_unsorted; ++pos_unsorted)
		{
				std::list<int>::iterator pos_sorted = sorted.begin(),
						end_sorted = sorted.end();
				while (pos_sorted != end_sorted && *pos_sorted < *pos_unsorted) ++pos_sorted;
				sorted.insert(pos_sorted, *pos_unsorted);
		}
		display_list<int, std::list<int>::const_iterator >(sorted.begin(), sorted.end(), "Sorted list: ", std::cout);
}

void in_place_sort()
{
		int numbers[] = {13, 7, 88, 43, 7, 9, 95, 37, 16, 14};
		int length = sizeof(numbers) / sizeof(int);

		display_list<int, int*>(numbers, numbers + length, "Unsorted list: ", std::cout); 

		for (int j = 1; j < length; ++j)
		{
				int key = numbers[j];
				int i = j - 1;
				while (i >= 0 && numbers[i] > key)
				{
						numbers[i + 1] = numbers[i];
						--i;
				}
				numbers[i + 1] = key;
		}

		display_list<int, int*>(numbers, numbers + length, "Sorted list: ", std::cout); 
}

int main(int, char*[])
{
		out_of_place_sort();
		in_place_sort();
		return 0;
}

