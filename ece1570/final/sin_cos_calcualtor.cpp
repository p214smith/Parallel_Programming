#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <bitset>
#include <climits>
using namespace std;

unsigned short convert_float_to_bfloat(float f){
    union
    {
        float input; 
        int   output;
    } data;
	data.input = f;
	bitset<sizeof(float) * CHAR_BIT> bits(data.output);
    bool a[16] ;
    int j = 0;
    for (int i = 31; i > 15; i--){
        a[j] = int(bits[i]);
        cout << a[j];
        j++;
    }
    
    cout <<endl<< bits << endl;
    unsigned short store = 0;
    for (int i = 0; i < 15; i++ , j--)
    store += pow(a[i]*2,j);
    if (a[15] == 1)
    store += 1;
    cout << " bfloat is " << store << endl;
    return store;
    
}
float convert_bfloat_to_float(unsigned short bf){
    float store = 0;
    float a[16];
    for(int i=15; i>=0; i--)    
{    
a[i]=bf%2;    
bf= bf/2;  
}  
for (int i = 0; i < 16; i++)
cout << a[i];
cout << endl;

unsigned short exp =  pow(2*a[1],7)+  pow(2*a[2],6)+ pow(2*a[3],5)+ pow(2*a[4],4)+ pow(2*a[5],3)+ pow(2*a[6],2)+ pow(2*a[7],1);
if ( a[8] == 1)
exp += 1;
cout << " exponent is " << exp << endl;
float mantissa = 1.0 + a[9]/2 + a[10]/4 + a[11]/8 + a[12]/16 + a[13]/32 + a[14]/64 + a[15]/128;
cout << " mantissa is " << mantissa << endl;
store = pow(-1,a[0]) * pow(2,exp-127) * mantissa;
return store;
}
unsigned short get_sin(unsigned short opp,unsigned short hyp){
    float opposite = convert_bfloat_to_float(opp);
    cout << "opposite is " << opposite << endl;
    float hypotenuse = convert_bfloat_to_float(hyp);
    cout << "hypotenuse is " << hypotenuse << endl;
    if (hypotenuse < opposite)
        return 0;
    float result = opposite / hypotenuse;
    cout << "result is" << result << endl;
    unsigned short store = convert_float_to_bfloat(result);
    return store;
}
unsigned short get_cos(unsigned short adj,unsigned short hyp){
    float adjacent = convert_bfloat_to_float(adj);
    cout << "adjacent is " << adjacent << endl;
    float hypotenuse = convert_bfloat_to_float(hyp);
    cout << "hypotenuse is " << hypotenuse << endl;
    if (hypotenuse < adjacent)
        return 0;
    float result = adjacent / hypotenuse;
    cout << "result is " << result << endl;
    unsigned short store = convert_float_to_bfloat(result);
    return store;
}
int main (){
    unsigned short a;
    unsigned short b;
    cout << "Enter value between 0 and 65535:" << endl;
    cin >> a;
    cout << "Enter value between 0 and 65535:" << endl;
    cin >> b;
    unsigned short sine = get_sin(a,b);
    cout << "sin result is " << sine << endl;
    unsigned short cos = get_cos(a,b);
    cout << "cos result is " << cos << endl;
    return 0;

};
