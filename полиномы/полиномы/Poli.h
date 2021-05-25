#pragma once
#include "Term.h"

class Polynomial
{
	friend class Term;
private:
	Term poly[6];
	int degree;
	int n;
	void Order() {
        int nj;
        for (int i = 1; i <= (n); i++) // сортировка по убыванию степеней
        {
            nj = i;
            for (int j = i + 1; j <= n; j++)
                if (poly[j].s > poly[nj].s)
                    nj = j;
            if (i != nj)
                swap(poly[i], poly[nj]);
        }
        for (int i = 1; i < n; i++) // сокращение термов одной степени
        {
            if (poly[i].s == poly[i + 1].s)
            {
                poly[i] = poly[i] + poly[i + 1];
                for (int j = i + 1; j <= n; j++)
                    poly[j] = poly[j + 1];
                n--;
                i--;
            }
        }
        int new_n_term = n;
        for (int i = 1; i <= n; i++)
        {
            if (poly[i] == Term(0, 0))
                new_n_term--;
        }
        n = new_n_term;
        if (n == 0)
        {
            degree = 0;
            return;
        }
        for (int i = 1; i <= n; i++) // сокращение термов с коэффициентом 0
            if (poly[i].k == 0)
            {
                for (int j = i; j <= n; j++)
                    poly[j] = poly[j + 1];
                n--;
            }
        degree = 0;
        for (int i = 1; i < 10; i++)
            if (poly[i].k != 0)
            {
                degree = poly[i].s;
                break;
            }
    }
public:
	Polynomial() { // конструктор без параметров
        n = 0;
        degree = 0;
    }
	Polynomial(int a) { // конструктор с одним параметром
        n = 1;
        poly[n] = Term(a);
        degree = 0;
    }
    Polynomial(int a, int b) {
        n = 1;
        poly[n] = Term(a, b);
        degree = b;
    }
	Polynomial(Term& term) {  // конструктор с одним параметром термом
        n = 1;
        poly[n] = term;
        degree = poly[n].s;
    }
	Polynomial(Polynomial& pol) { // конструктор копирования
        n = pol.n;
        degree = pol.degree;
        for (int i = 1; i <= n; i++)
            poly[i] = pol.poly[i];
    }
    Polynomial operator = (Polynomial& pol) { // оператор присваивания
        n = pol.n;
        degree = pol.degree;
        for (int i = 1; i <= n; i++)
            poly[i] = pol.poly[i];
        return *this;
    }
    Polynomial& operator = (const Polynomial& pol) { // оператор присваивания
        n = pol.n;
        degree = pol.degree;
        for (int i = 1; i <= n; i++)
            poly[i] = pol.poly[i];
        return *this;
    }

    
    friend Polynomial operator + (Polynomial& pl1, const Polynomial& pl2) {
        Polynomial res;
        res.n = pl1.n + pl2.n;
        for (int i = 1; i <= pl1.n; i++)
            res.poly[i] = pl1.poly[i];
        for (int i = (pl1.n + 1); i <= (pl1.n + pl2.n); i++)
            res.poly[i] = pl2.poly[i - pl1.n];
        res.Order();
        return res;
    }
    friend Polynomial operator - (Polynomial& pl1, const Polynomial& pl2) {
        Polynomial res;
        res.n = pl1.n + pl2.n;
        for (int i = 1; i <= pl1.n; i++)
            res.poly[i] = pl1.poly[i];
        for (int i = (pl1.n + 1); i <= (pl1.n + pl2.n); i++)
            res.poly[i] = -pl2.poly[i - pl1.n];
        res.Order();
        return res;
    }
    Polynomial operator += (Polynomial& pl) {
        *this = *this + pl;
        return *this;
    }
    Polynomial& operator += (const Polynomial& pl) {
        *this = *this + pl;
        return *this;
    }
    friend Polynomial operator * (Polynomial& pl1, Polynomial& pl2) {
        Polynomial res;
        int pom = 0;
        res.n = pl1.n * pl2.n;
        for (int i = 1; i <= pl1.n; i++)
            for (int j = 1; j <= pl2.n; j++)
            {
                pom++;
                res.poly[pom] = pl1.poly[i] * pl2.poly[j];
            }
        res.Order();
        return res;
    }
    Polynomial operator *= (Polynomial& pl) {
        return (*this = *this * pl);
    }
    friend ostream& operator << (ostream& out, Polynomial& pl) // Помещение в поток
    {
        if (pl.n == 0)
            out << "0";
        else
            for (int i = 1; i <= pl.n; i++)
            {
                if (i != 1)
                {
                    if (pl.poly[i].bigger_0())
                        out << "+";
                }
                out << pl.poly[i];
            }
        return out;
    }
    void enter() {
        char vyr[81] = {}, buf[50] = {}, pom[6] = {};
        int i = 0, j = 0; // j - длина полученного массива полинома
        gets_s(vyr);
        while (vyr[i] != '\0')
        {
            if (vyr[i] != ' ')
            {
                buf[j] = vyr[i];
                j++;
            }
            i++;
        }
        if ((buf[0] != '+') && (buf[0] != '-'))
        {
            for (i = j; i > 0; i--)
                buf[i] = buf[i - 1];
            buf[0] = '+';
        }
        for (int p = 0; p <= j; p++)
            if (buf[p] == '+' || buf[p] == '-')
            {
                for (int i = 0; i < 6; i++)
                    pom[i] = ' ';
                i = p;
                do
                {
                    pom[i - p] = buf[i];
                    i++;
                } while ((buf[i] != '+') && (buf[i] != '-') && i <= j);
                Term p = Term(pom);
                *this += Polynomial(p);
                Order();
            }
        Order();
    }
};

//- степени и -