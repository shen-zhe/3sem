#include "geo.h"
//----------Point----------------------
Point Point :: operator=(const Point& p) {
        x = p.x;
        y = p.y;
        return *this;
    }

Point :: Point(const Point& p){
        x = p.x;
        y = p.y;
    }

double Point::getX() const {
        return x;
    }

double Point::getY() const {
        return y;
    }
//-----------Circle--------------------

Circle::Circle(const Point& c, double r) : center(c), radius(r) {}

Circle::Circle(const Circle& other){
        radius = other.radius;
        center = other.center;
    }

double Circle::getRadius() {
        return radius;
    }

Point Circle::getCenter() {
        return center;
    }

 void Circle::findIntersection(const Circle& other, Point& intersection1 /*Point& intersection2*/) const {
        // первая окружность с центром (0,0), вторая с центром (x2, y2)
        double a, b, c;
        a = -2 * other.center.getX();
        b = -2 * other.center.getY();
        c = other.center.getX()*other.center.getX() + other.center.getY()*other.center.getY() + radius*radius - other.radius*other.radius;

        double x0 = -a*c/(a*a+b*b),  y0 = -b*c/(a*a+b*b);

        double d = radius*radius - c*c/(a*a + b*b);
        double mult = sqrt(d / (a*a + b*b));
        intersection1 = Point(center.getX() + x0 + b * mult, center.getY() + y0 - a * mult);
        //intersection2 = Point(center.getX() + x0 - b * mult, center.getY() + y0 + a * mult);
    }

Circle Circle :: operator =(const Circle& p) {
        radius = p.radius;
        center = p.center;
        return *this;
    }

//-----------Triangle------------------

Point Triangle::getA(){
    return A;
    }

Point Triangle::getB(){
    return B;
}

Point Triangle::getC(){
    return C;
}

void Triangle::print_Triangle(const string& filename) const{
        ofstream file(filename);
        if (file.is_open()){
            file << "%section\n";
            file << 0 << " " << -10 << " \n";
            file << AB << " " << -10 << " \n\n";
            file << 0 << " " << -11 << " \n";
            file << BC << " " << -11 << " \n\n";
            file << 0 << " " << -12 << " \n";
            file << AC << " " << -12 << " \n\n";

            file << "%triangle\n";
            file << A.getX() << " " << A.getY() << "\n";
            file << B.getX() << " " << B.getY() << "\n";
            file << C.getX() << " " << C.getY() << "\n";
            file << A.getX() << " " << A.getY() << "\n";

            file << "\n";
            file << "%circle\n";

            double eps = 0.01;
            
            int numPoints = static_cast<int>(2 * M_PI * AC / eps);
            for(int i = 0; i < numPoints; ++i){
                double angle = i * 2 * M_PI / numPoints;
                double x = A.getX() + AC * cos(angle);
                double y = A.getY() + AC * sin(angle);
                file << x << " " << y << "\n";
            }

             file << "\n";
            
            numPoints = static_cast<int>(2 * M_PI * BC / eps);
            for(int i = 0; i < numPoints; ++i){
                double angle = i * 2 * M_PI / numPoints;
                double x = B.getX() + BC * cos(angle);
                double y = B.getY() + BC * sin(angle);
                file << x << " " << y << "\n";
            }

            file.close();
        } else { 
            cerr << "could not open the file " << filename << "\n"; 
        }

    }

bool Triangle::read_Triangle(const string& namefile){
        ifstream fin(namefile);
        double nAB, nBC, nAC;
        if(fin.is_open()){
            if (fin >> nAB >> nBC >> nAC){
                if(is_Triangle(nAB, nBC, nAC)){
                    set_Triangle(nAB, nBC, nAC);
                    return true;
                } else {
                    cerr << "does not form a triangle";
                }
                
            } else {
                cerr << "failed to read\n";
            }
            fin.close();
        } else {
            cerr << " could not open the file " << namefile << "\n";
        }
        return false;  
    } 

bool Triangle::is_Triangle(double AB, double BC, double AC){
        return (AB + BC > AC) && (AC + BC > AB) && ( AC + AB > BC);    
    }

void Triangle::set_Triangle(double nAB, double nBC, double nAC){
        AB = nAB;
        BC = nBC;
        AC = nAC;
        A = Point(0.0,0.0);
        B = Point(AB, 0.0);
        Circle c1 = Circle(A, AC); 
        Circle c2 = Circle(B, BC);
        Point intersection;
        c1.findIntersection(c2, intersection);
        C = intersection;
    }

    