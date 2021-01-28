#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

int main(int argc, char* argv[])
{
 
        vector<string> vec;
        
        string line;
        string a,b,c;
        ifstream myfile ("input.txt");
        if (myfile.is_open())
        {
            while ( getline (myfile,line))
            {
                vec.push_back(line);
            }
            myfile.close();
        }
        else{
            /*Condition for not a file*/
            std::cerr<<"Bad file error";
            return -1;
            
        }
        
        int i=0;
        for(i=0;i<vec.size();i++)
            cout<< vec.at(i);
        
       
        
  
    return 0;
    }

