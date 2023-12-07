#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;
char notes[20202];
char in[20202];
vector <int> nn;
vector <int> ii;
int input_note(const char *str, int p);
void process(const char *str);
void process2(const char *str2);
int main(void)
{
    scanf("%s\n%s", notes, in);
    process(notes);
    process2(in);
    if((int)nn.size() > (int)ii.size()){
        printf("No\n");
        return 0;
    }
    int sz = (int)nn.size();
    int pos = 0;
    // int lo = (int)ii.size() - (int)nn.size();
    
    for(int i=0; i<(int)ii.size(); i++)
    {
        //모두 일치한 상태에서 키를 친 경우
        if(pos == sz) pos = 0;
        //왜 또 체크할까?
        if(ii[i] == nn[pos]) pos++;
        else pos = 0;
    }
    if(pos == sz)
        printf("Yes\n");
    else
        printf("No\n");
}
int input_note(const char *str, int p)
{
    char ch1 = str[p++];
    int dir = -1;
    if(ch1 == 'L')
    {
        char ch2 = str[p++];
        if(ch2 == 'U') dir = 0; 
        else dir = 6;    
    }
    else if(ch1 == 'R')
    {
        char ch2 = str[p++];
        if(ch2 == 'U') dir = 2;
        else dir = 4;
    }
    else if(ch1 == 'W') dir = 1;
    else if(ch1 == 'D') dir = 3;
    else if(ch1 == 'S') dir = 5;
    else if(ch1 == 'A') dir = 7;
    if(str[p] == '!') {p++; dir = (dir + 4) % 8;}
    nn.push_back(dir);
    return p;
}
void process(const char *str)
{
    int k = 0;
    for(int p=0; str[p];){
        p = input_note(str, p); k++;
    }
}
void process2(const char *str)
{
    for(int i=0; str[i]; i++)
    {
        if(str[i] == '7') ii.push_back(0);
        else if(str[i] == 'W' || str[i] == '8') ii.push_back(1);
        else if(str[i] == '9') ii.push_back(2);
        else if(str[i] == 'D' || str[i] == '6') ii.push_back(3);
        else if(str[i] == '3') ii.push_back(4);
        else if(str[i] == 'S' || str[i] == '2') ii.push_back(5);
        else if(str[i] == '1') ii.push_back(6);
        else ii.push_back(7);
    }
}