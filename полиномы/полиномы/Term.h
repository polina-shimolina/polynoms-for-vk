#pragma once
#include <iostream>

using namespace std;

class Term
{
	friend class Polynomial;
private:
	int k, s;
public:
	Term() { // конструктор
        k = 0; s = 0;
    }
    Term(int a) { // конструктор с параметром
        k = a;
        s = 0;
    }
    Term(int a, int b) { // конструктор с двумя параметрами
        k = a;
        s = b;
    }
    Term(char ch[10]) // конструктор для ввода
    {
        int sign = 0, i = 1, pom = 1, p = 1;
        if (ch[0] == '+')
            sign = 1;
        else
            sign = -1;

        if (ch[i] == 'x')
            k = 1;
        else
        {
            k = 0;
            pom = int(ch[i]);
            for (p = i; (pom >= 48) && (pom <= 57); p++)
            {
                k = 10 * k + (pom - 48);
                pom = int(ch[p + 1]);
            }
        }
        i = p;
        k *= sign;
        s = 1;
        if (ch[i] == 'x')
        {
            i += 2;
            pom = int(ch[i]);
            if ((pom < 48) || (pom > 57))
                s *= 1;
            else
            {
                s = 0;
                pom = int(ch[i]);
                for (p = i; ((pom >= 48) && (pom <= 57)); p++)
                {
                    s = 10 * s + (pom - 48);
                    pom = int(ch[p + 1]);
                }
            }
        }
        else
            s = 0;
    }
	//копирования
    Term operator = (Term trm) { // оператор присваивания
        k = trm.k;
        s = trm.s;
        return *this;
    }

    Term operator - () const
    {
        return Term(k, -s);
    }

    friend Term& operator + (Term& a, Term& b) { // оператор сложения двух термов
        int n_kt, n_st;
        n_kt = a.k + b.k;
        n_st = a.s;
        Term l = Term(n_kt, n_st);
        return l;
    }

    friend Term& operator * (Term& a, Term& b) { // оператор умножения двух термов
        int n_kt, n_st;
        n_kt = a.k * b.k;
        n_st = a.s + b.s;
        Term l = Term(n_kt, n_st);
        return l;
    }
    friend ostream& operator << (ostream& out, Term& a) { // вывод на экран
        if (a.k != 0)
        {
            if (a.s == 0)
            {
                out << a.k;
                return out;
            }
            if (a.k == 1)
            {
                if (a.s == 1)
                    out << " x ";
                else
                    out << " x^" << a.s;
                return out;
            }
            if (a.k == -1)
            {
                if (a.s == 1)
                    out << "- x ";
                else
                    out << "- x^" << a.s;
                return out;
            }
            if (a.s == 1)
            {
                out << a.k << "x ";
                return out;
            }
            out << a.k << "x^" << a.s << " ";
            return out;
        }
    }
    bool operator == (const Term& trm)const
    {
        return k == trm.s && s == trm.s;
    }
	bool bigger_0() {
        return k > 0;
    }
};







