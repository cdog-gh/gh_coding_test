#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;
struct moo
{
    int permission;
    int owner;
    int group;
};
typedef struct moo moo;
char str[205];
vector <string> temp_tok;
unordered_map <string, int> user;
unordered_map <string, int> group;
unordered_map <string, moo> files;
vector <int> con[1005050];
void tok()
{
    for(int i=0; str[i]; i++)
        if(str[i] == ',') str[i] = ' ';
}
void tokenizer()
{
    temp_tok.clear();
    const char *t = strtok(str, " ");
    while(t != NULL)
    {
        temp_tok.push_back(string(t));
        t = strtok(NULL, " ");
    }
}
int get_group_no(string s)
{
    if(group.find(s) == group.end()){
        int t = (int)group.size();
        group[s] = t;
    }
    return group[s];
}
int is_group_include(int user_num, int group_num)
{
    for(int i=0; i<(int)con[user_num].size(); i++)
    {
        if(con[user_num][i] == group_num)
            return 1;
    }
    return 0;
}
int chk(int per, char x)
{
    if(x == 'R')
        return (per & 4) != 0;
    if(x == 'W')
        return (per & 2) != 0;
    return (per & 1) != 0;
}
int main(void)
{
    int n, f, q; scanf("%d%d\n", &n, &f);
    for(int i=0; i<n; i++)
    {
        fgets(str, 205, stdin);
        int leni = strlen(str);
        if(str[leni - 1] == '\n') str[leni - 1] = 0;
        tok(); //, to space
        tokenizer();
        //유저 i번
        user[temp_tok[0]] = i;
        //printf("%s : %d\n", temp_tok[0].c_str(), i);
        for(int j=0; j<(int)temp_tok.size(); j++)
        {
            int gn = get_group_no(temp_tok[j]);
            con[i].push_back(gn);
            //printf("%d : %d\n", i, gn);
        }
    }
    for(int i=0; i<f; i++)
    {
        fgets(str, 205, stdin);
        
        int leni = strlen(str);
        if(str[leni - 1] == '\n') str[leni - 1] = 0;
        
        tokenizer();
        //file_name 755 soyuja soyugroup
        moo I;
        I.permission = stoi(temp_tok[1]);
        I.owner = user[string(temp_tok[2])];
        I.group = group[string(temp_tok[3])];
        files[string(temp_tok[0])] = I;
    }
    scanf("%d\n", &q);
    for(int i=0; i<q; i++)
    {
        fgets(str, 205, stdin);
        tokenizer();
        
        //user file operation
        int un = user[temp_tok[0]];
        string file = temp_tok[1];
        char oper = temp_tok[2][0];
        
        int owner = files[file].owner;
        int gn = files[file].group;
        int file_permission = files[file].permission;
        int one = file_permission/100;
        int two = (file_permission % 100)/10;
        int three = file_permission % 10;
        //printf("<%d %d>\n", un, gn);
        //맨 앞에 숫자를 뽑음.
        if(un == owner)
            printf("%d\n", chk(one, oper));
        
        //두 번째 숫자를 뽑음.
        else if(is_group_include(un, gn))
            printf("%d\n", chk(two, oper));
        //세 번째 숫자를 뽑음.
        else
            printf("%d\n", chk(three, oper));
    }
}