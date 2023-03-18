import requests
base = "https://solved.ac/api/v3"
gh_1_problem = [
    ("A", 21771),
    ("B", 21772),
    ("C", 21773),
    ("D", 21774),
    ("E", 21775),
    ("F", 21776),
    ("G", 21777),
    ("H", 21778)
]
gh_1_data = list()
for _, problem_num in gh_1_problem:
    try:
        r = requests.get(f"{base}/search/problem", params={
            "query": problem_num
        }).json()
        gh_1_data.append({
            "lv": r["items"][0]["level"],
            "title": r["items"][0]["titleKo"],
            "problemNo": r["items"][0]["problemId"]
        })
    except:
        assert False, "request error"

with open("1/README.md", "w", encoding="utf8") as f:
    f.write(f"""## 1회 [바로 가기](https://www.acmicpc.net/contest/view/644)\n""")
    f.write(f"""5월 23일 13시부터 18시까지 1회 코딩테스트가 열렸습니다.\n""")
    f.write(f"""\n""")
    f.write(f"""|문제 번호|제목|풀러 가기|힌트|난이도|\n""")
    f.write(f"""|:------:|:-------------:|:-----:|:-----:|:-----:|\n""")
    for i, data in enumerate(gh_1_data):
        ch = chr(ord('A') + i)
        problem_title = data["title"]
        problem_link = f"""https://www.acmicpc.net/problem/{data["problemNo"]}"""
        hint_link = f"""https://github.com/cdog-gh/gh_coding_test/tree/main/1/{i+1}"""
        img_script = f"""<img height="25px" width="25px" src="https://static.solved.ac/tier_small/{data["lv"]}.svg"></img>"""
        f.write(f"""|{ch}|{problem_title}|[바로가기]({problem_link})|[힌트]({hint_link})| {img_script} |\n""")
