#include "mdfile.h"
void test(){
assert(er("base.txt", "error.txt") == 1);
assert(er("base.tx", "error.txt") == 12);
std::cout<<"Test OK"<<std::endl;
}
int main(){
test();
return 0;
}