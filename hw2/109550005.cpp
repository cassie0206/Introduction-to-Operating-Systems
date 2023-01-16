# include <iostream>
# include <thread>
# include <unistd.h>
#include <algorithm>
#include <vector>
using namespace std;

# define MAX 500
#define int long long

int matA[MAX][MAX];
int matB[MAX][MAX];
int matC[MAX][MAX]; // Result of Addition
int matD[MAX][MAX]; // Result of Multiplication
vector<int> sumE, sumF;

int num = 20;
int NumOfSingleThread, mode;
vector<int> s(num), e(num);

int sum_C = 0, sum_D = 0;

void Addition(int s, int e){
    // Addition -> matC
    for (int i = s; i < e; i++) {
        for (int j = 0; j < MAX; j++){
            matC[i][j] = matA[i][j] + matB[i][j];
        }   
    }
}
void Multiplication(int s, int e){
    // Multiplication -> matD
    for (int i = s; i < e; i++) {
        for (int j = 0; j < MAX; j++) {
            matD[i][j] = 0;
            for (int k = 0; k < MAX; k++) {
                matD[i][j] += matA[i][k] * matB[k][j];
            }
        }
    }
}

// child threading function
void* child_thread(void* data){
    //sleep(1);
    // cout << "Child Pthread ID - " << pthread_self() << endl;
    int index = (int) data; // get data "Child"

    Addition(s[index], e[index]);
    Multiplication(s[index], e[index]);

    pthread_exit(NULL); // exit child thread 
}

void sumC(int index, int s, int e){
    for (int i = s; i < e; i++) {
        for (int j = 0; j < MAX; j++)
            sumE[index] +=  matC[i][j];     
    }
}

void sumD(int index, int s, int e){
    for (int i = s; i < e; i++) {
        for (int j = 0; j < MAX; j++)
            sumF[index] += matD[i][j];
    }
}

void* child_thread1(void* data){
    //sleep(1);
    // cout << "Child Pthread ID - " << pthread_self() << endl;
    int index = (int) data; // get data "Child"

    sumC(index, s[index], e[index]);
    sumD(index, s[index], e[index]);

    pthread_exit(NULL); // exit child thread 
}


signed main()
{   
    cin.tie(0);
    cin.sync_with_stdio(0);
    //get input
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            cin >> matA[i][j];
        }
    }
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            cin >> matB[i][j];
        }
    }

    vector<pthread_t>  v(num), v_out(num); 
    NumOfSingleThread = 500 / num;
    mode = 500 % num;

    for(int i=0;i<num; i++){
        int ta = NumOfSingleThread;
        if(i < mode){ ta++; }

        if(i == 0){
            s[i] = 0;
            e[i] = ta;
        }
        else{
            s[i] = e[i - 1];
            e[i] = e[i - 1] + ta;
        }

        pthread_create(&v[i], NULL, child_thread,(void *) i);
    } 

    for(int i=0;i<num;i++){
        pthread_join(v[i], NULL);
    }

    sumE.resize(num, 0);
    sumF.resize(num, 0);
    for(int i=0;i<num; i++){
        pthread_create(&v_out[i], NULL, child_thread1,(void *) i);
    }
    for(int i=0;i<num;i++){
        pthread_join(v_out[i], NULL);
    }
    for(int i=0;i<num;i++){
        sum_C += sumE[i];
        sum_D += sumF[i];
    }

    cout << sum_C << '\n';
    cout << sum_D << '\n';

    return 0;
}
