//
//  main.cpp
//  Task-3.1-Async
//
//  Created by Маргарет  on 30.06.2024.
//

#include <iostream>
#include <future>
#include <vector>
#include <climits>

int min_el(int *arr, int size,int start_i, std::promise<int> &pr) {
    int min = INT_MAX;
    
    for (int i = start_i; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    
    std::cout << "Если индекс начала поиска равен " << start_i << ", то минимальный элемент равен " << min << "\n";
    
    pr.set_value(min);
    
    return min;
}

void sort_arr(int *arr, int size) {
    int i, j, min_i;
    for (i = 0; i < size - 1; i++) {
        
        std::promise<int> pr;
        std::future<int> ft = pr.get_future();
        auto res = std::async(min_el, std::ref(arr), size, i, std::ref(pr));
        ft.wait();
        auto min = ft.get();
        min_i = i;
        for (j = i + 1; j < size; j++) {
            if (arr[j] < arr[min_i]) {
                min_i = j;
            }
        }
        
        if(min_i != i) {
            std::cout << "Если индекс начала поиска равен " << i << ", то выталкиваем наименьший элемент " << arr[min_i] << "\n";
            std::swap(arr[min_i],arr[i]);
        }
    }
}

int main(int argc, const char * argv[]) {
    const int size = 10;
    int arr[size] = {4, 2 , 10, 5, 4, 12, 8, 3, 11, 20};
    
    std::cout << "Неотсортированный массив: ";
    
    for(int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
    
    sort_arr(arr, size);
    
    std::cout << "Отсортированный массив: ";
    for(int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }


    return 0;
}
