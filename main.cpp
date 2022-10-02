#include<iostream>
#include<fstream>
#include<ctime>
#define MAX_TIME_SECS 40
using namespace std;

//------------------------------------------------------------------------
//--------------------INSTRUCTION TO COMPUTE THE TIME---------------------
//unsigned t0, t1;
//t0=clock();//Inicio del cronometro
//........Algorithm............................
//t1 = clock();//Final del cronometro
//double time = (double(t1-t0)/CLOCKS_PER_SEC);//calculo del tiempo en sec
//------------------------------------------------------------------------


void fill_arr(int *arr_input,int size){
    ifstream file_to_read;
    file_to_read.open("inputs_random.txt");

    for (int i=0;i<size;i++)file_to_read>>arr_input[i];

    file_to_read.close();
}


int main(){
    
    return 0;
}