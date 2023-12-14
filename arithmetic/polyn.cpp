#include "poly.h"

int sign(double x)
{
    if (x > 0) return 1;
    else if (x < 0) return -1;
    return 0;
}
// конструктор без параметров: создается полином нулевой степени
// с коэффициентом при нулевой степени равным нулю
Polynom::Polynom(){
    deg=0;
    koef=new double[deg+1];
    koef[0]=0.0;
}
 
// конструктор с параметрами
// new_deg - степень создаваемого полинома
// newkoef - указатель на new_deg+1 - элементный массив с коэффициентами 
//           полинома, где newkoef[i] - коффициент при i-й степени
//           и newkoef[0] - коэффициент при нулевой степени
// В результате степень полинома будет наибольшим номером ненулевого
// элемента массива new_koef и меньше или равна new_deg (по определению степени полинома)
Polynom::Polynom(unsigned int new_deg, double *new_koef){
    deg=0;
    for(int i = 0;i <= new_deg;i++)
        if(new_koef[i]!=0) deg=i;   //инициализация переменной степени
    koef=new double[deg+1];
    for(int i = 0;i<=deg;i++)
        koef[i]=new_koef[i]; //инициализация массива коэффициентов
}
 
//копирующий конструктор
Polynom::Polynom(const Polynom &f){
    deg=f.deg;
    koef=new double[deg+1];
    for(int i=0;i<=deg;i++)
        koef[i]=f.koef[i];
}
 
//деструктор
Polynom::~Polynom(){
    delete[] koef;
}
// функция получения степени полинома
unsigned int Polynom::GetDeg(){
    return deg;
}
 
// функция получения коэффициента при i-й степени
double Polynom::GetKoef(unsigned int i){
    if(i<=deg) 
        return koef[i];
    else 
        return 0.0;
}
 
// функция задания коэффициента при i-й степени
unsigned int Polynom::SetKoef(double new_koef, unsigned int i){
    if(i<=deg) koef[i]=new_koef;
    else return deg;
    CorrectDeg();   
    return deg;
}
 
//оператор сложения двух полиномов
Polynom Polynom::operator + (const Polynom &t){
    int i;
    Polynom *result;
 
    if(deg>=t.deg){ //если степень первого полинома больше степени второго
        result=new Polynom(deg,koef);
        for(i=0;i<=t.deg;i++)
            result->koef[i]=result->koef[i]+t.koef[i];
    }
    else{                   //если степень второго полинома больше степень первого
        result=new Polynom(t.deg,t.koef);
        for(i=0;i<=deg;i++)
            result->koef[i]=result->koef[i]+koef[i];
    }
    result->CorrectDeg();
    return *result;
}
 
//оператор присваивания
Polynom Polynom::operator = (const Polynom &t){
    deg=t.deg;
    delete[] koef;
    koef=new double[deg+1];
    for(int i=0;i<=deg;i++)
        koef[i]=t.koef[i];
    return *this;
}

//значение производной в точке
double Polynom::value_Polynom(double x){
    double s  = 0.0;
    for(int i=0; i<=deg; i++){
        s += koef[i] * pow(x,i);
    }
    return s;

}

//значение многочлена в точке
double Polynom::value_derPolynom(double x){
    double s = 0.0;
    for(int i=1;i<=deg;i++){
        s += koef[i] * pow(x, (i - 1));
    }
    return s;
}

 
//функция реализующая умножение полинома на число
Polynom MultConst(double K, Polynom &t){
    if(K==0){
        Polynom result;
        return result;
    }
    else{
        int deg=t.deg;
        double *tmp_koef=new double[deg+1];
        for(int i=0;i<=deg;i++)
            tmp_koef[i]=K*t.koef[i];
        Polynom result(deg,tmp_koef);
        delete[] tmp_koef;
        return result;
    }
}
 
// функция корректировки степени полинома: коэффициент 
// при максимальной степени должен быть ненулевым
void Polynom::CorrectDeg(){
    if(koef[deg]==0){
        do{                                 
            deg--;
        }while(deg && koef[deg]==0);
    }
}
 
//функция ввода полинома
void Polynom::InputPolynom(){
    cout << "Input degree: ";
    cin >> deg;
    delete[] koef;
    koef=new double[deg+1];
    for(int i=0;i<deg;i++){
        cout << "K" << i << " = ";
        cin >> koef[i];
    }
    do{
        cout << "K" << deg << " = ";
        cin >> koef[deg];
        if(koef[deg]==0)
            cout << "K" << deg << " must not be zero!!!\n";
    }while(!koef[deg]);
}
//функция вывода полинома
void Polynom::OutputPolynom(){
    if(koef[deg]==1)
        cout << "X^" << deg;
    else if(koef[deg]==-1)
        cout << "-X^" << deg;
    else
        cout << koef[deg] << "X^" << deg;
 
    for(int i=deg-1;i>0;i--){
        if(koef[i]>0){
            if(koef[i]==1)
                cout << " + " << "X^" << i;
            else
                cout << " + " << koef[i] << "X^" << i;
        }else if(koef[i]<0)
            if(koef[i]==-1)
                cout << " - " << "X^" << i;
            else
                cout << " - " << (-1)*koef[i] << "X^" << i;
    }
 
    if(koef[0]>0)
        cout << " + " << koef[0] << "\n";
    else if(koef[0]<0)
        cout << " - " << (-1)*koef[0] << "\n";
}

//поиск корня на отрезке, с помощью метода хорд
int Polynom::root_chords(double *x, double a, double b){
    double epsilon = 0.0001;
    double fa,fb,fc,c[2];
    int i = 0,ifa,ifb,ifc,k;
    c[0]=a; c[1]=b; fa = value_Polynom(a); fb = value_Polynom(b);
    // Проверка условий запуска итераций:
    if(fabs(fa)<epsilon){*x = a; return 1;}
    if(fabs(fb)<epsilon){*x = b; return 1;}
    ifa = sign(fa); 
    ifb = sign(fb);
    if(ifa*ifb != -1) return 0;
    for(k=1; fabs(c[1]-c[0])>epsilon; k++){
    // последовательное сохранение промежуточной точки
        i=!i;
        c[i]=(a*fb-b*fa)/(fb-fa);
        fc= value_Polynom(c[i]); 
        ifc=sign(fc);
        // если значение функции мало:
        if(fabs(fc)<epsilon){
            *x=c[i]; 
            return k+1;
        }
        // выбор подотрезка [a,c] или [c,b] :
        if(ifc*ifa==1){
            a=c[i]; 
            fa=fc;
        }
        else {
            b=c[i]; 
            fb=fc;
        }
    }
    *x=c[i]; // возвращается последнее значение величины С
    return k; // возвращается число итераций
}