#ifndef CRYPTO_H_INCLUDED
#define CRYPTO_H_INCLUDED
#include<math.h>
#include<bits/stdc++.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#define RAND_MAX 100
namespace std{


//////////////////Utils///////////////////
class Utils{
friend class Crypto;

bool isPrime(long int n){
    long int n_05=int(sqrt(n))+1;
    if(n==0||n==1){
        return false;
    }

    for(long int i=2;i<=n_05;i++){

        if(n%i==0){
            return false;
        }

    }
    return true;
}



bool areCoprime(long int a,long int b){
        using namespace std;
     if ( __gcd(a, b) == 1)
        return true;
    else
        return false;;
}
int power(int x, unsigned int y, int p)
{
    int res = 1;

    x = x % p;
    if (x == 0) return 0;

    while (y > 0)
    {

        if (y & 1)
            res = (res*x) % p;


        y = y>>1;
        x = (x*x) % p;
    }
    return res;
}

long int rand_prime(long int lower, long int upper) {

  long int spread = upper - lower + 1;
  while(1) {
    long int p = 1 | (rand() % spread + lower);
    if (isPrime(p)) return p;
  }
}



long int totient(long int a,long int b)
{
    using namespace std;
    long int result=(a-1)*(b-1);
    return result;
}

long int totient(long int m){
    using namespace std;
      long int result = 1;
    for (long int i = 2; i < m; i++)
        if (__gcd(i, m) == 1)
            result++;
    return result;


}

long int modInverse(int a, int m)
{
    a = a % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
}
};

//////////////////Crypto///////////////////
class Crypto{
    Utils u;


  unsigned long long int encode_integer( unsigned long  long int msg,unsigned long long int nonce, unsigned long   long int enc){
    using namespace std;
    unsigned long  long int res;

    res=u.power((int)msg,(unsigned int)enc,(int) nonce);
    return res;
}

long int decode_integer(long int crypt,long int nonce,long int dec){
    using namespace std;
    unsigned long  long int res;
    res=u.power((int)crypt,(unsigned int)dec,(int) nonce);
    return res;
}
public:


  long int * generateKeys(){
    long int a,b;
    srand(time(NULL));
    a=u.rand_prime(20,50);
    b=u.rand_prime(50,70);



    long int nonce=a*b;

    static   long int result[3];

    result[0]=(long int)nonce;

    long int t=u.totient(a,b);

    using namespace std;

    while(true){

        long int r=rand();
        if(r<t&&u.areCoprime(r,t)){
            result[1]=r;
            break;
        }
    }
    result[2]=u.modInverse((int)result[1],(int)t);

    return result;

}


    long int * inputKeys(){
         static   long int result[3];
         result[0]=-1;
         result[1]=-1;
         result[2]=-1;
         cout<<"Enter keys. Input -1 where parameter is not applicable."<<endl;
        cout<<"Enter nonce: ";
        cin>>result[0];
        cout<<"Enter encoder: ";
        cin>>result[1];
        cout<<"Enter decoder: ";
        cin>>result[2];

        return result;
    }


    void encode_str(char input[81],unsigned long long int nonce, unsigned long   long int enc,int target[81]){
        for(int i=0;i<81;i++){
        if(input[i]!='\0'){
        target[i]=encode_integer(int(input[i]),nonce,enc);}
        else{
             for(int j=i;j<81;j++){
              target[j]=int('\0');
             }
            break;
        }
    }


}

void decode_str(int crypt[81],long int nonce,long int dec,char target[81]){
    for(int i=0;i<81;i++){
        target[i]=(char)((int)decode_integer(crypt[i],nonce,dec));
    }
}

};

//////////////////CryptoFileHandler///////////////////
class CryptoFileHandler: public Crypto{

    #include <fstream>
    #include <iostream>
    #include<string>
    #include<string.h>
    #include <stdio.h>
    #include<strings.h>
    ofstream outfile;
    ifstream infile;

    void writeEncrytedToFile(int arr[81],string location){
        outfile.open(location);


        for(int i=0;i<81;i++){
            if(arr[i]!=0){
            outfile<<arr[i]<<"\n";
            }
        }
        outfile<<"-1";
        outfile.close();
    }

    vector<int> readf(string location){
    std::vector<int> myintArray;

    std::string line;
    std::ifstream myfile(location);

    for (int result; std::getline(myfile, line); result = std::stoi(line))
    {
        myintArray.push_back(result);


    }
    return myintArray;
}

    void readEncryptedFromFile(string location,int target[81]){


        vector<int> encrypted_vector=readf(location);
        int n = encrypted_vector.size();

        //int crypt[81];

        for (int i = 0; i < n-1; i++){
            target[i] = encrypted_vector[i+1];
        }
        for (int i = n-1; i < 81; i++){
            target[i] = 0;
        }
    }
public:

    CryptoFileHandler(){}

     void encryptToFile(char message[81],string location,long int * keys){

         int crypt[81];
         encode_str(message,(unsigned long long int)*(keys),(unsigned long long int)*(keys+1),crypt);
         writeEncrytedToFile(crypt,location);
     }

    void decryptToArray(string location,char target[81],long int * keys){
        int crypt[81];
        readEncryptedFromFile(location,crypt);
        decode_str(crypt,( long int)*(keys),(long int)*(keys+2),target);

    }
};
}


#endif // CRYPTO_H_INCLUDED
