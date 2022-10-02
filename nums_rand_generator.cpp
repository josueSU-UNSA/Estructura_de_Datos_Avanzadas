#include<iostream>
#include<fstream>
#include<random>

using namespace std;


int get_num_rand(){
    return rand();
}
int main(){
    ofstream file_to_write;
    file_to_write.open("inputs_random.txt");
    srand(time(0));
    for(int i=0;i<10000;i++)file_to_write<<get_num_rand()<<endl;
    return 0;
}