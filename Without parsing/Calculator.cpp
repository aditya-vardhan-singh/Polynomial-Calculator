#include <iostream>
#include <bits/stdc++.h>

void input(std::list<std::pair<int, int>>& exp) {
    int max_deg, deg, coeff;
    
    std::cout << "Enter highest degree: ";
    std::cin >> max_deg;

    for (deg = max_deg; deg >= 0; --deg) {
        std::cout << "Coeff of x^" << deg << ": ";
        std::cin >> coeff;
        exp.push_back({coeff, deg});
    }
}

void print(std::list<std::pair<int, int>> exp) {
    std::pair<int, int> element;
    int no_coeff = 1, size = exp.size();

    while (!exp.empty()) {
        element = exp.front();
        exp.pop_front();

        if (element.first != 0) no_coeff = 0;

        if (element.second == size - 1 && element.first > 0)
            std::cout << " ";
        else if (element.first > 0)
            std:: cout << " +";
        else if (element.first < 0)
            std::cout << " -";
        else
            continue;
        
        if (element.second == 0)
            std::cout << abs(element.first);
        else if (element.second == 1)
            std::cout << abs(element.first) << "x";
        else
            std::cout << abs(element.first) << "x^" << element.second;
            
    }
    if (no_coeff) std::cout << "0";
    std::cout << std::endl;
}

std::list<std::pair<int, int>> add(std::list<std::pair<int, int>> exp1, std::list<std::pair<int, int>> exp2) {
    std::list<std::pair<int, int>> sum;
    std::pair<int, int> element1, element2;

    while(!exp1.empty() && !exp2.empty()) {
        element1 = exp1.back();
        exp1.pop_back();
        element2 = exp2.back();
        exp2.pop_back();

        sum.push_front({element1.first + element2.first, element1.second});
    }
    while (!exp1.empty()) {
        sum.push_front(exp1.back());
        exp1.pop_back();
    }
    while (!exp2.empty()) {
        sum.push_front(exp2.back());
        exp2.pop_back();
    }

    return sum;
}

std::list<std::pair<int, int>> sub(std::list<std::pair<int, int>> exp1, std::list<std::pair<int, int>> exp2) {
    std::list<std::pair<int, int>> diff;
    std::pair<int, int> element1, element2;

    while(!exp1.empty() && !exp2.empty()) {
        element1 = exp1.back();
        exp1.pop_back();
        element2 = exp2.back();
        exp2.pop_back();

        diff.push_front({element1.first - element2.first, element1.second});
    }
    while (!exp1.empty()) {
        diff.push_front(exp1.back());
        exp1.pop_back();
    }
    while (!exp2.empty()) {
        diff.push_front({0 - exp2.back().first, exp2.back().second});
        exp2.pop_back();
    }

    return diff;
}

std::list<std::pair<int, int>> mul(std::list<std::pair<int, int>> exp1, std::list<std::pair<int, int>> exp2) {
    std::list<std::pair<int, int>> mul;
}

int main() {
    std::list<std::pair<int, int>> exp1, exp2, sum, diff;
    
    std::cout << "Enter polynomial 1:" << std::endl;
    input(exp1);
    std::cout << "Enter polynomial 2:" << std::endl;
    input(exp2);

    std::cout << "Polynomial 1:";
    print(exp1);
    std::cout << "Polynomial 2:";
    print(exp2);

    sum = add(exp1, exp2);
    std::cout << "Polynomial after addition:";
    print(sum);

    diff = sub(exp1, exp2);
    std::cout << "Polynomial after subtraction:";
    print(diff);

    return 0;
}