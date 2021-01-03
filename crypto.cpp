#include<iostream>
#include "crypto.h"

using namespace std;
int main(){

    Crypto  c;
    CryptoFileHandler cf;
    char target[81],input[81];
    int crypt[81];

    long int * keys;
    keys=c.generateKeys();
    cout<<"Nonce: "<<*(keys)<<endl;
    cout<<"Encoder: "<<*(keys+1)<<endl;
    cout<<"Decoder: "<<*(keys+2)<<endl;
    cout<<endl;


    cout<<"Enter string: ";
    cin.getline(input,sizeof(input));
    cout<<endl;

    cf.encryptToFile(input,"test.txt",keys);
    delete keys;

    long int * newkeys;
    newkeys=c.inputKeys();

    cf.decryptToArray("test.txt",target,newkeys);

    cout<<endl;
    cout<<"Decrypted text: ";
    cout<<target<<endl;

    return 0;
}
