import requests
base = "https://solved.ac/api/v3"
gh_5_problem = [
    ("A", 27880),
    ("B", 27885),
    ("C", 27883),
    ("D", 27884),
    ("E", 27881),
    ("F", 27888),
    ("G", 27882),
    ("H", 27887),
    ("I", 27886),
]
gh_5_data = list()
for _, problem_num in gh_5_problem:
    try:
        r = requests.get(f"{base}/search/problem", params={
            "query": problem_num
        }).json()
        gh_5_data.append({
            "lv": r["items"][0]["level"],
            "title": r["items"][0]["titleKo"],
            "problemNo": r["items"][0]["problemId"]
        })
    except:
        assert False, "request error"

with open("5/README.md", "w", encoding="utf8") as f:
    f.write(f"""## 5회 [바로 가기](https://www.acmicpc.net/contest/view/946)\n""")
    f.write(f"""4월 2일 13시부터 18시 10분까지 5회 코딩테스트가 열렸습니다.\n""")
    f.write(f"""\n""")
    f.write(f"""|문제 번호|제목|풀러 가기|힌트|난이도|\n""")
    f.write(f"""|:------:|:-------------:|:-----:|:-----:|:-----:|\n""")
    for i, data in enumerate(gh_5_data):
        ch = chr(ord('A') + i)
        problem_title = data["title"]
        problem_link = f"""https://www.acmicpc.net/problem/{data["problemNo"]}"""
        hint_link = f"""https://github.com/cdog-gh/gh_coding_test/tree/main/5/{i+1}"""
        img_script = f"""<img height="25px" width="25px" src="https://static.solved.ac/tier_small/{data["lv"]}.svg"></img>"""
        f.write(f"""|{ch}|{problem_title}|[바로가기]({problem_link})|[힌트]({hint_link})| {img_script} |\n""")

    from datetime import datetime
    from datetime import timezone
    f.write(f"\n마지막 업데이트 날짜 : {str(datetime.now(timezone.utc)).replace('+00:00', 'Z')}")
