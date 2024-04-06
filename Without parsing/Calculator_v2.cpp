#include <iostream>
#include <list>

typedef struct element {
    int coeff;
    int deg;
} element;

typedef std::list<element> Poly_Exp;
typedef std::list<element>::iterator Poly_Exp_Itr;
typedef std::list<element>::reverse_iterator Poly_Exp_RItr;

void input(Poly_Exp &exp) {
    int max_deg, deg, coeff;
    
    std::cout << "Enter highest degree: ";
    std::cin >> max_deg;

    for (deg = max_deg; deg >= 0; --deg) {
        std::cout << "Coeff of x^" << deg << ": ";
        std::cin >> coeff;
        exp.push_back({coeff, deg});
    }
}

void print(Poly_Exp &exp) {
    Poly_Exp_Itr itr;
    int no_coeff, size;

    no_coeff = 1;
    size = exp.size();

    for (itr = exp.begin(); itr != exp.end(); ++itr) {
        if (itr->coeff != 0) no_coeff = 0;  // if any coeff is not zero

        if (itr->deg == size - 1 && itr->coeff > 0)
            std::cout << " ";
        else if (itr->coeff > 0)
            std::cout << " +";
        else if (itr->coeff < 0)
            std::cout << " -";
        else
            continue;

        if (itr->deg == 0)
            std::cout << abs(itr->coeff);
        else if (itr->deg == 1)
            std::cout << abs(itr->coeff) << "x";
        else
            std::cout << abs(itr->coeff) << "x^" << itr->deg;
    }
    if (no_coeff) std::cout << "0";
    std::cout << std::endl;
}

Poly_Exp add(Poly_Exp &exp1, Poly_Exp &exp2) {
    Poly_Exp sum;
    Poly_Exp_RItr itr1, itr2;

    itr1 = exp1.rbegin();
    itr2 = exp2.rbegin();

    while (itr1 != exp1.rend() && itr2 != exp2.rend()) {
        sum.push_front({itr1->coeff + itr2->coeff, itr1->deg});
        itr1++;
        itr2++;
    }
    while (itr1 != exp1.rend()) {
        sum.push_front({itr1->coeff, itr1->deg});
        itr1++;
    }
    while (itr2 != exp2.rend()) {
        sum.push_front({itr2->coeff, itr2->deg});
        itr2++;
    }

    return sum;
}

Poly_Exp sub(Poly_Exp &exp1, Poly_Exp &exp2) {
    Poly_Exp diff;
    Poly_Exp_RItr itr1, itr2;

    itr1 = exp1.rbegin();
    itr2 = exp2.rbegin();

    while (itr1 != exp1.rend() && itr2 != exp2.rend()) {
        diff.push_front({itr1->coeff - itr2->coeff, itr1->deg});
        itr1++;
        itr2++;
    }
    while (itr1 != exp1.rend()) {
        diff.push_front({itr1->coeff, itr1->deg});
        itr1++;
    }
    while (itr2 != exp2.rend()) {
        diff.push_front({0 - itr2->coeff, itr2->deg});
        itr2++;
    }

    return diff;
}

Poly_Exp mul(Poly_Exp &exp1, Poly_Exp &exp2) {
    Poly_Exp prod;
    Poly_Exp_Itr itr1, itr2, itr;
    int max_deg, i;

    max_deg = exp1.front().deg + exp2.front().deg;

    for (i = max_deg; i >= 0; --i) {
        prod.push_back({0, i});
    }

    for (itr1 = exp1.begin(); itr1 != exp1.end(); ++itr1) {
        for (itr2 = exp2.begin(); itr2 != exp2.end(); ++itr2) {
            itr = prod.end();
            itr = std::next(itr, -(itr1->deg + itr2->deg + 1));
            itr->coeff += itr1->coeff * itr2->coeff;
        }
    }

    return prod;
}

std::pair<Poly_Exp, Poly_Exp> div(Poly_Exp &exp1, Poly_Exp &exp2) {
    Poly_Exp quot, rem;

    if (exp1.front().deg < exp2.front().deg) {
        quot.push_back({0, 0});
        rem = exp1;
        return {quot, rem};
    } else {
        // quot.push_back({0, 0});
        // rem.push_back({0, 0});
        return {quot, rem};
    }
}

int main() {
    Poly_Exp exp1, exp2, sum, diff, prod;
    std::pair<Poly_Exp, Poly_Exp> division_result;

    std::cout << "Enter polynomial expression 1:" << std::endl;
    input(exp1);
    std::cout << "Enter polynomial expression 2:" << std::endl;
    input(exp2);
    
    std::cout << "Polynomial expression 1:";
    print(exp1);
    std::cout << "Polynomial expression 2:";
    print(exp2);

    sum = add(exp1, exp2);
    std::cout << "Polynomial expression after addition:";
    print(sum);

    diff = sub(exp1, exp2);
    std::cout << "Polynomial expression after subtraction:";
    print(diff);

    prod = mul(exp1, exp2);
    std::cout << "Polynomial expression after multiplication:";
    print(prod);

    division_result = div(exp1, exp2);
    std::cout << "Quotent:";
    print(division_result.first);

    std::cout << "Remainder:";
    print(division_result.second);

    return 0;
}