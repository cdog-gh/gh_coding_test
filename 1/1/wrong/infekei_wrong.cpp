/*
author : infikei
*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int R, C, Rg, Cg, Rp, Cp;
vector<string> room;

void input() {
    cin >> R >> C;
    cin >> Rg >> Cg >> Rp >> Cp;
    for (int i = 0; i < R; i++) {
        string tmp;
        cin >> tmp;
        room.push_back(tmp);
    }
}

int solve() {
    int Rp_begin = 0, Cp_begin = 0;
    for (int i = 0; i < R; i++) {
        // 'P'를 발견한 경우, Rp_begin에 넣음.
        // 밑에 break 때문에 무조건 빠져 나오게 되어 있음.
        if (room[i].find('P') != string::npos) {
            Rp_begin = i;
            for (int j = 0; j < C; j++) {
                // Cp_begin 은 row 에서 'P'가 시작하는 위치임.
                if (room[i][j] == 'P') {
                    Cp_begin = j;
                    break;
                }
            }
            break;
        }
    }
    
    /*
    이 경우 베개가 차지하고 있는 영역은 Rp_begin, Cp_begin 부터 Rp, Cp만큼임.
    그런데 이 전제가 과연 맞을까?
    */
    int Rp_end = Rp_begin + Rp;
    int Cp_end = Cp_begin + Cp;
    for (int i = Rp_begin; i < Rp_end; i++) {
        /*
        한 가지 추가 에러. 만약에 탐색 범위 내에 모두 'P'가 들어가 있는데
        C 범위를 넘어서까지 탐색한다면? 이 경우 0이 리턴되는데 틀리는 경우가 있음. (infikei_wrong_1.in)
        본질적인 원인은 좌상단을 잘못 가정해서 생긴 것으로 코너 4쪽에 붙이면 저격 데이터를 생성할 수 있음.
        
        좌상, 좌하, 우하에 대해서 잘못 찾는 것도 비슷하게 저격 가능.
        */
        if (i >= R) {
            return 0;
        }
        for (int j = Cp_begin; j < Cp_end; j++) {
            if (j >= C) {
                return 0;
            }

            if (room[i][j] != 'P') {
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false); // C++와 C 두 표준 입출력 동기화를 해제한다.
    cout.tie(NULL);
    cin.tie(NULL); // 입력과 출력이 묶여있는 것을 풀어준다.

    input();

    cout << solve() << '\n';

    return 0;
}