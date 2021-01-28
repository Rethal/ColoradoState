#include <iostream>
#include <fstream>
#include <cstring>


using namespace std;

int main(void){
char word[81];
do{
bool palindrome=true;




cout << "Please enter a word" << endl;
cin>>word;
int length = strlen(word);
int(length/2);
if (length>0){
for(int i=0;i<(length);i++)
{
if(word[0]!=word[length-1-i]) 
palindrome=false;
} 
}
if(palindrome==true)
{ 
cout << "The word is a palindrome" << endl; 
}
else
{
cout << "The word is not a palindrome" << endl; 
}

}while (word != "END"); 

return(0) ;

}
