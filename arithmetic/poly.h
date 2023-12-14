

//поиск корня многочлена на отрезке, мне нужны операции +-, умножения на числа,
#include <iostream>
#include <memory>
#include <cmath>

 

using namespace std;
//класс Polynom
class Polynom{
private:
    unsigned int deg; //степень полинома
    double *koef; //указатель на массив коэффициентов полинома
                  //koef[i] - коэффициент при i-й степени,
                  //koef[0] - коэффициент при нулевой степени
    void CorrectDeg(); // функция корректировки степени полинома
 
public:
    Polynom(); //конструктор без параметров
    Polynom(unsigned int, double*); //конструктор с параметрами
    Polynom(const Polynom &); //копирующий контсруктор
    ~Polynom(); //деструктор
 
    unsigned int GetDeg(); //функция получения степени полинома
    double GetKoef(unsigned int); //функция получения коэффициента при i-й степени
    unsigned int SetKoef(double, unsigned int); //функция задания коэффициента при i-й 
                                                //степени, возвращает степень полинома
    Polynom operator + (const Polynom &);   //оператор сложения двух полиномов
    Polynom operator = (const Polynom &);   //оператор присваивания
    friend Polynom MultConst(double, Polynom &); //дружественная функция умножения полинома
                                              //на константу
    void InputPolynom();    //функция ввода полинома
    void OutputPolynom();   //функция вывода полинома
    double value_derPolynom(double x);
    double value_Polynom(double x);

    int root_chords(double *x, double a, double b);
};
 
