#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cmath>
#include<iomanip>
using namespace std;
int main()
{
    fstream file,result;
    file.open("./Milestone1/Input/Testcase1.txt",ios::in);
    char ch ;
    vector<int>inputs;
    if(file){
    while(!file.eof())
    {
        ch=file.get();
        if(ch==':')
        {
            string str="";
            do
            {
                ch=file.get();
                if(isdigit(ch))
                {
                    str+=ch;
                }
                else
                break;
            } while (isdigit(ch));
            inputs.push_back(stoi(str));
        }
    } 
    file.close();
    }
    else
        cout<<"File not found..!";
    float rad=float(inputs[0])/2.0;
    int n=inputs[1];
    float ang=inputs[2];
    float dia=float(inputs[0])/float(n-1);
    vector<pair<float,float>> coordinates;
        ang=ang*(3.14159/180);//angle conversion
    float x=rad*cos(ang);
    float y=rad*sin(ang);

    for(int k=0;k<n;k++)
    {

            coordinates.push_back({x,y});
            rad-=dia;
            x=rad*cos(ang);
            y=rad*sin(ang);
            if(y==-0)
            {
                y=0;
            } 
    }
    result.open("output.txt",ios::out);
    
    for(auto m:coordinates)
    {
        result<<"("<<m.first<<","<<m.second<<")\n";
    }
    result.close();



    return 0;
}
