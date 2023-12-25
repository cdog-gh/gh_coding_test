"""
validator 작성이 쉽지 않기 때문에 (특히 token parsing)
parsing 후 다시 data rebuild한 결과 input'과 input을 비교한 것.
local에서는 input_to_file -> file_to_input으로 compare.
"""


def able(c):
    if 'a' <= c <= 'z':
        return True
    if 'A' <= c <= 'Z':
        return True
    if '0' <= c <= '9':
        return True
    if c == ' ':
        return True
    return False


def work(target: str):
    dat_list = list()
    new_target = target.strip()
    if new_target != target:
        print('no!')
        exit(0)
    for item in target:
        if not able(item):
            print('no 2!')
            exit(0)
    li = target.split(' ')
    member_name = list()
    group_name = ''  # Group ~
    team_name = ''  # Team ~
    lo = 0
    while True:
        if lo == len(li):
            break
        if li[lo] == 'Group':
            # lo + 1 == group_name
            # lo + 2 == Team
            if li[lo + 2] != 'Team':
                print('no 3!')
                exit(0)
            # lo + 3 == team_name
            group_name = li[lo + 1]
            team_name = li[lo + 3]
            mem_name = " ".join(member_name)

            if not group_name:
                print('no 4!')
                exit(0)

            if not team_name:
                print('no 5!')
                exit(0)

            if not mem_name:
                print('no 6!')
                exit(0)

            if 'Group' in group_name or 'Group' in team_name or 'Group' in mem_name:
                print('no 4!')
                exit(0)

            if 'Team' in group_name or 'Team' in team_name or 'Team' in mem_name:
                print('no 5!')
                exit(0)

            dat_list.append(f"{group_name}#{team_name}#{mem_name}")
            # print(f"{group_name}#{team_name}#{mem_name}")

            member_name = list()
            lo += 4
        else:
            member_name.append(li[lo])
            lo += 1
    if len(member_name) != 0:
        print('no 9!')
        exit(0)

    return dat_list


pp = input()
rr = input()
p = work(pp)
r = work(rr)
p_s = {k for k in p}
r_s = {k for k in r}

if len(p) != len(r):
    print('no 6!')
    exit(0)

if len(p_s) != len(r_s):
    print('no 7!')
    exit(0)

for i, item in enumerate(p):
    if 'Team' in item or 'Group' in item:
        print('no 8!!')
        exit(0)
    arr = item.split("#")
    ran = i + 1
    if i != 0:
        print()
    print(f"rank : {ran}")
    print(f"group: {arr[0]}")
    print(f"team : {arr[1]}")
    print(f"name : {arr[2]}")
print("---")
for i, item in enumerate(r):
    arr = item.split("#")
    ran = i + 1
    if i != 0:
        print()
    print(f"rank : {ran}")
    print(f"group: {arr[0]}")
    print(f"team : {arr[1]}")
    print(f"name : {arr[2]}")