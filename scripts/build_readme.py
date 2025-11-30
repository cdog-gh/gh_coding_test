from API import (
    build_gh_problem,
    build_init_data
)
from db import gh_contest_db
from util import min_to_string

pre_init_data = build_init_data()
gh_data = []
for i, item in enumerate(gh_contest_db):
    problems = item.get("problems", [])
    gh_data.append(build_gh_problem(problems, pre_init_data))
for t in range(1, len(gh_data)):
    item = gh_data[t]
    with open(f"{t}/README.md", "w", encoding="utf8") as f:
        f.write(f"""## {t}회 [바로 가기](https://www.acmicpc.net/contest/view/{gh_contest_db[t]['id']})\n""")
        f.write(f"""{gh_contest_db[t]['yyyy']}년 {gh_contest_db[t]['mm']:02d}월 {gh_contest_db[t]['dd']:02d}일 """)
        ss_str = min_to_string(gh_contest_db[t]['start'])
        ee_str = min_to_string(gh_contest_db[t]['end'])

        f.write(f"""{ss_str}부터 {ee_str}까지 {t}회 코딩테스트가 열렸습니다.\n""")
        f.write(f"""\n""")
        f.write(f"""|문제 번호|제목|풀러 가기|힌트|난이도|\n""")
        f.write(f"""|:------:|:-------------:|:-----:|:-----:|:-----:|\n""")
        for i, data in enumerate(gh_data[t]):
            ch = chr(ord('A') + i)
            problem_title = data["title"]
            problem_link = f"""https://www.acmicpc.net/problem/{data["problemNo"]}"""
            hint_link = f"""https://github.com/cdog-gh/gh_coding_test/tree/main/1/{i + 1}"""
            img_script = f"""<img height="25px" width="25px" src="https://static.solved.ac/tier_small/{data["lv"]}.svg"></img>"""
            f.write(f"""|{ch}|{problem_title}|[바로가기]({problem_link})|[힌트]({hint_link})| {img_script} |\n""")

        from datetime import datetime
        from datetime import timezone

        f.write(f"\n마지막 업데이트 날짜 : {str(datetime.now(timezone.utc)).replace('+00:00', 'Z')}")