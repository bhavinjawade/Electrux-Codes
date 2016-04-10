#include <iostream>
#include <cstdlib>

int main()
{
    system("cls");
    int arr[10] = {10,20,30,40,50,60,70,80,90,100}, lb = 0, ub = (10-1), beg = lb, end = ub, mid = (beg+end)/2, data, pos = -1;

    std::cout << "Enter what to search: ";
    std::cin >> data;
    //START BINARY SEARCH
    while (beg <= end) {
        std::cout << "Array to be searched in for value:" << beg << " " << end  << "\n";
        for(int i = beg; i <= end; i++)
        {
            std::cout << arr[i] << "\t";
        }
        std::cout << "\n";
        if(arr[mid] == data)
        {
            pos = mid + 1;
            break;
        }
        else
        {
            if(data < arr[mid])
            {
                end = mid - 1;
            }
            else
            {
                beg = mid + 1;
            }
        }
        mid = (beg+end)/2;
    }

    if(pos == -1)
    {
        std::cout << "\nElement not found in the array.";
    }
    else
    {
        std::cout << "\nElement found in array at " << pos << "th position.\n";
    }
    system("pause");
    return 0;
}
