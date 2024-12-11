from collections import defaultdict

notion_dic = defaultdict(list)
shinkansen_st = [
    "Tokyo",  # 0
    "Shinagawa",  # 1
    "Shin-Yokohama",  # 2 시발만 가능.
    "Odawara",  # 3
    "Atami",  # 4
    "Mishima",  # 5
    "Shin-Fuji",  # 6
    "Shizuoka",  # 7
    "Kakegawa",  # 8
    "Hamamatsu",  # 9
    "Toyohashi",  # 10
    "Mikawa-Anjo",  # 11
    "Nagoya",  # 12
    "Gifu-Hashima",  # 13
    "Maibara",  # 14
    "Kyoto",  # 15
    "Shin-Osaka",  # 16
]
shinkansen_se = [
    ("Tokyo", 0),
    ("Shinagawa", 1),  # 시발만 가능
    ("Shin-Yokohama", 2),  # 시발만 가능
    ("Mishima", 5),  # 출근 시간에 이 역에서 시발하는 경우 존재. 이 경우, 동행으로만 진행한다.
    ("Shizuoka", 7),  # 시발, 종착
    ("Hamamatsu", 9),  # 시발, 종착
    ("Nagoya", 12),  # 시발, 종착 (단, 시발 + 서행으로 진행하는 경우, 신오사카역을 경유한다.)
    ("Shin-Osaka", 16)  # 시발, 종착
]

direct_dic = {v: i for i, v in enumerate(shinkansen_st)}


def build(st1: int, st2: int, stop_set: list, grade):
    li = list()
    if st1 < st2:
        for i in range(st1, st2 + 1):
            if shinkansen_st[i] not in stop_set:
                continue
            li.append(shinkansen_st[i])
    else:
        for i in range(st1, st2 - 1, -1):
            if shinkansen_st[i] not in stop_set:
                continue
            li.append(shinkansen_st[i])
    k = "=>".join(li)
    notion_dic[k].append(grade)


def kodama():
    stop_possible = [k for k in shinkansen_st]
    # 조건 : 모든 열차에 대해, 시발역에서 종착역으로 이동하는 데 요금은 5000원 이상이다.
    # 단, 고속 요금 임율이 적용되는 구간에서만 운행하는 경우 33000원 이상이며, 경유하는 역은 4개 이상이다.
    k_possible = {
        0: [7, 9, 12, 16],
        1: [7, 9, 12, 16],
        2: [0, 7, 9, 12, 16],
        5: [0],
        7: [0, 12, 16],
        9: [0, 16],
        12: [7, 0],
        16: [9, 7, 0]
    }

    for s in k_possible:
        for e in k_possible[s]:
            build(s, e, stop_possible, "kodama")


def build_pat_2_to_12(dat: list):
    res = {
        "Rapid": [],
        "Normal": []
    }
    for i in range(2 ** len(dat)):
        li = []
        for j in range(len(dat)):
            if i & (1 << j):
                li.append(dat[j][0])
        if len(li) <= 2:
            res["Rapid"].append(li)
        elif li[-1] == "Mishima":
            res["Rapid"].append(li)
        elif "Shizuoka" not in li:
            res["Rapid"].append(li)
        else:
            res["Normal"].append(li)
    return res


def hikari_build(
    s: int, e: int, p_2_to_12, p_12_to_15
):
    is_reverse = False
    if s > e:
        (s, e) = (e, s)
        is_reverse = True
    if e == 12:
        for g1 in ["Normal"]:
            mid_list_1 = p_2_to_12[g1]
            for mid1 in mid_list_1:
                te = [k for k in shinkansen_st[s:3]]
                te.extend(mid1)
                te.extend([k for k in shinkansen_st[12:12 + 1]])
                if is_reverse:
                    te = [k for k in reversed(te)]
                k = "=>".join(te)
                notion_dic[k].append("hikari")
    else:
        for g1 in ["Normal", "Rapid"]:
            for g2 in ["Normal", "Rapid"]:
                if g1 == "Rapid" and g2 == "Rapid":
                    continue
                mid_list_1 = p_2_to_12[g1]
                mid_list_2 = p_12_to_15[g2]
                for mid1 in mid_list_1:
                    for mid2 in mid_list_2:
                        te = [k for k in shinkansen_st[s:3]]
                        te.extend(mid1)
                        te.extend([k for k in shinkansen_st[12:12+1]])
                        te.extend(mid2)
                        te.extend([k for k in shinkansen_st[15:16+1]])
                        if is_reverse:
                            te = [k for k in reversed(te)]
                        k = "=>".join(te)
                        notion_dic[k].append("hikari")


def hikari():
    # hikari 조건 : 시발 ~ 종착역 간, Nozomi와 동일 정차 패턴을 가지지 않는다.
    # 급행: 2 to 12에서
    # 2개 이하의 역에 정차한다.
    # 시즈오카시에 있는 역에 정차하지 않는다.
    # 무정차 거리가 200km가 넘는다.
    # 단 나고야에서 시발하거나 종착하는 경우, Rapid 패턴으로 운행하지 않는다.

    # hikari 조건 : Maibara 역에 멈추지 않으면, Gifu-Hashima 역에도 멈추지 않는다.
    # Nagoya ~ Kyoto 구간에서 노조미와 동일한 정차 패턴을 가지는 경우 급행이라고 한다.
    from_2_to_12 = [
        ("Odawara", 3),
        ("Atami", 4),
        ("Mishima", 5),
        ("Shizuoka", 7),
        ("Hamamatsu", 9),
        ("Toyohashi", 10),
    ]
    pat_2_to_12 = build_pat_2_to_12(from_2_to_12)
    pat_12_to_15 = {
        "Rapid": [[]],
        "Normal": [["Gifu-Hashima", "Maibara"], ["Maibara"]]
    }
     # 0 to 12, 15
    hikari_build(0, 12, pat_2_to_12, pat_12_to_15)
    hikari_build(1, 12, pat_2_to_12, pat_12_to_15)
    hikari_build(2, 12, pat_2_to_12, pat_12_to_15)
    hikari_build(0, 16, pat_2_to_12, pat_12_to_15)
    hikari_build(1, 16, pat_2_to_12, pat_12_to_15)
    hikari_build(2, 16, pat_2_to_12, pat_12_to_15)

    # 12 to 0
    hikari_build(12, 0, pat_2_to_12, pat_12_to_15)

    # 15 to 0
    hikari_build(16, 0, pat_2_to_12, pat_12_to_15)


def nozomi():
    # 노조미 조건
    # 하위 등급의 열차와 시발역에서부터 종착역까지 정차역이 같은 경우는 없다.
    stop_possible = [
        "Tokyo", "Shinagawa", "Shin-Yokohama", "Nagoya", "Kyoto", "Shin-Osaka"
    ]
    n_possible = {
        0: [12, 16],
        1: [12, 16],
        2: [12, 16],
        12: [0],
        16: [0]
    }

    for s in n_possible:
        for e in n_possible[s]:
            build(s, e, stop_possible, "nozomi")


def process():
    # 에러 출력 형식
    # 도카이도 신칸센에 없는 역이 나오면 ERROR 200
    # 한 역을 2번 이상 방문한 경우 ERROR 300
    # 시발역에서 종착역으로 가는 도중에 진행 방향이 바뀌면 ERROR 400
    # 그 외에는 hikari인지 nozomi인지 kodama인지 출력한다. 출력할 수 없으면 ERROR 500.
    n = int(input())
    st_list = list()
    visit = dict()
    ini = list()
    err_list = []
    for _ in range(n):
        ini.append(input().strip())
    for i in range(n):
        st = ini[i].split()
        if st[-1] == "station":
            st = st[:len(st) - 1]
        st_info = " ".join(st)
        if st_info not in direct_dic:
            err_list.append(200)
        if st_info in visit:
            err_list.append(300)
        visit[st_info] = 1
        st_list.append(st_info)
    d0 = direct_dic.get(st_list[0], 0)
    d1 = direct_dic.get(st_list[1], 0)

    for e in range(1, len(st_list)):
        de = direct_dic.get(st_list[e], 0)
        dp = direct_dic.get(st_list[e-1], 0)
        if (d1 - d0) * (de - dp) < 0:
            err_list.append(400)
    key = "=>".join(st_list)
    v = notion_dic.get(key)
    if not v:
        err_list.append(500)
    err_list = sorted(err_list)
    if not err_list:
        print(v[0])
    else:
        print(f"ERROR {err_list[0]}")


kodama()
hikari()
nozomi()

q = int(input())
for _ in range(q):
    process()
