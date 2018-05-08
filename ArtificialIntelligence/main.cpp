#include <iostream>
#include "State.h"

using namespace std;

int main(){
    State st("123456780");
    st.print();
    st.getLeft()->print();
    return 0;
}
