#include "geo.h"


int main(){
    Triangle ABC;
    if(ABC.read_Triangle("test.txt")){
        ABC.print_Triangle("ans.txt");
    }
    return 0;
}
