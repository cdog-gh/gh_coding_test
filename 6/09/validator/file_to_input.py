"""
validator 작성이 쉽지 않기 때문에 (특히 token parsing)
parsing 후 다시 data rebuild한 결과 input'과 input을 비교한 것.
local에서는 input_to_file -> file_to_input으로 compare.
"""
name = ""
team = ""
group = ""
pp = list()
rr = list()
flag = 0
# name Group group Team team
while True:
    try:
        s = input()
    except EOFError:
        break
    if s.startswith('---'):
        flag = 1
        continue
    if s.startswith("group: "):
        s = s.replace("group: ", "")
        group = s
    elif s.startswith("team : "):
        s = s.replace("team : ", "")
        team = s
    elif s.startswith("name : "):
        s = s.replace("name : ", "")
        name = s
        ss = f"{name} Group {group} Team {team}"
        if flag:
            rr.append(ss)
        else:
            pp.append(ss)
print(" ".join(pp))
print(" ".join(rr))
