//
//  main.cpp
//  Task-3.1-Async
//
//  Created by Маргарет  on 30.06.2024.
//

#include <iostream>
#include <future>
#include <vector>

int min_num(int *arr, int size, std::promise<int> & pr) {
    int i, j, min;
    for (i = 0; i < size - 1; i++) {
        min = i;
        for (j = i + 1; j < size; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        
        if(min != i) {
            std::swap(arr[min],arr[i]);
        }
        
    }
    
    pr.set_value(arr[0]);
    return arr[0];
}

int main(int argc, const char * argv[]) {
    std::promise<int> pr;
    std::future<int> ft = pr.get_future();
    
    const int size = 10;
    int arr[size] = {4, 2 , 10, 5, 1, 0, 8, 3, 11, 20};
    std::cout << "Неотсортированный массив: ";
    
    for(int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
    
    auto res = std::async(min_num, std::ref(arr), size, std::ref(pr));
    ft.wait();
    auto min = ft.get();
    std::cout << "Отсортированный массив: ";
    for(int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
    std::cout << "Наименьший элемент: " << min << "\n";
    
    
    
    
    return 0;
}
