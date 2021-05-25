
#include <iostream>
#include "Poli.h"

int main()
{
    locale::global(locale("rus"));
    Polynomial x;
    cout << "Введите полином 1: ";
    x.enter();
    Polynomial y;
    cout << "Введите полином 2: ";
    y.enter();
    cout << "Введенные полиномы:" << x << ", " << y << endl;
    Polynomial z;
    z = x - y;
    cout << "Разность: " << z << endl;
    z = x * y;
    cout << "Произведение: " << z << endl;
    

}
