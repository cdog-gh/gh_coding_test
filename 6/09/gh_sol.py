p_in = input().split()
r_in = input().split()

p_dict = {}
r_dict = {}


def read_in(target: list, dic: dict):
    temp_name = list()
    i = 0
    cur_rank = 1
    while i < len(target):
        token = target[i]
        if token != 'Group':
            temp_name.append(token)
            i += 1
            continue
        people_name = " ".join(temp_name)
        temp_name = list()
        group_name = target[i+1]
        team_name = target[i+3]
        dic[f"{group_name}#{team_name}#{people_name}"] = cur_rank
        i += 4
        cur_rank += 1


def get_tier(r: int):
    return (r-1) // 16 + 1
    

read_in(p_in, p_dict)
read_in(r_in, r_dict)
k = 0
for item in p_dict:
    p_rank = p_dict.get(item, 81)
    c_rank = r_dict.get(item, 81)
    p_tier = get_tier(p_rank)
    c_tier = get_tier(c_rank)
    if p_tier == 1 and c_tier > 1:
        k += 30000

sin = -1
rr = 90
ans = ""
for item in r_dict:
    p_rank = p_dict.get(item, 81)
    c_rank = r_dict.get(item, 81)
    # print(f"{p_rank} {c_rank}")
    ret = 0
    if c_rank == 81:
        continue
    p_tier = get_tier(p_rank)
    c_tier = get_tier(c_rank)
    
    # 1
    if p_tier > c_tier:
        ret = 10000 * (p_tier - c_tier)
    
    # 2
    if p_tier > 1 and c_tier == 1:
        ret += k
    
    # 3
    if c_rank % 16 == 1:
        ret += 10000
        if p_tier > c_tier:
            ret += 10000
    
    if ret > sin:
        sin = ret
        ans = item
        # print(f"{p_rank} {c_rank} : {item} :: {ret}")
        rr = c_rank # 90
    elif ret == sin and c_rank < rr:
        # print(f"!{c_rank} {rr}")
        rr = c_rank
        # print(f"!{p_rank} {c_rank} {item} :: {ret}")
        ans = item
ans = ans.replace("#", "\n")
print(ans)
