#include <iostream>
#include <vector>

void arrangeinarr(std::vector<int> &arr, int num)
{
	int rem, temp = num;

	while(temp > 0)
	{
		rem = temp % 10;
		temp /= 10;
		arr.push_back(rem);
	}
}

std::vector<int> multiplyarraywith(std::vector<int> arr, int num)
{
	std::vector<int> array;
	int mult = 0;

	for(int i = 0; i < arr.size(); ++i)
	{
		mult = mult + arr[i] * num;

		array.push_back(mult % 10);

		mult /= 10;
	}

	arrangeinarr(array, mult);

	return array;
}

int main()
{
	std::vector<int> arr;

	int factof;

	//std::cout << "Calculate factorial of: ";
	std::cin >> factof;

	arrangeinarr(arr, factof);

	for(int i = factof - 1; i >= 2; --i)
	{
		arr = multiplyarraywith(arr, i);
	}

	for(std::vector<int>::reverse_iterator it = arr.rbegin(); it != arr.rend(); it++)
		std::cout << *it;

	std::cout << "\n";

	return 0;
}
