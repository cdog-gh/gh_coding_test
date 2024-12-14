from API import build_gh_problem


gh_1_problem = [21771, 21772, 21773, 21774, 21775, 21776, 21777, 21778]
gh_1_data = build_gh_problem(gh_1_problem)

gh_2_problem = [22232, 22233, 22234, 22238, 22235, 22236, 22237, 22239]
gh_2_data = build_gh_problem(gh_2_problem)

gh_3_problem = [24336, 24337, 24339, 24338, 24340]
gh_3_data = build_gh_problem(gh_3_problem)

gh_4_problem = [25238, 25239, 25240, 25243, 25242, 25241, 25244]
gh_4_data = build_gh_problem(gh_4_problem)

gh_5_problem = [27880, 27885, 27883, 27884, 27881, 27888, 27882, 27887, 27886]
gh_5_data = build_gh_problem(gh_5_problem)

gh_6_problem = [30791, 30792, 30793, 30794, 30796, 30801, 30797, 30799, 30795, 30798, 30800]
gh_6_data = build_gh_problem(gh_6_problem)

gh_7_problem = [32775, 32776, 32777, 32778, 32779, 32780, 32786, 32781, 32783, 32784, 32785, 32782]
gh_7_data = build_gh_problem(gh_7_problem)


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

    from datetime import datetime
    from datetime import timezone
    f.write(f"\n마지막 업데이트 날짜 : {str(datetime.now(timezone.utc)).replace('+00:00', 'Z')}")


with open("2/README.md", "w", encoding="utf8") as f:
    f.write(f"""## 2회 [바로 가기](https://www.acmicpc.net/contest/view/658)\n""")
    f.write(f"""7월 18일 13시부터 18시까지 2회 코딩테스트가 열렸습니다.\n""")
    f.write(f"""\n""")
    f.write(f"""|문제 번호|제목|풀러 가기|힌트|난이도|\n""")
    f.write(f"""|:------:|:-------------:|:-----:|:-----:|:-----:|\n""")
    for i, data in enumerate(gh_2_data):
        ch = chr(ord('A') + i)
        problem_title = data["title"]
        problem_link = f"""https://www.acmicpc.net/problem/{data["problemNo"]}"""
        hint_link = f"""https://github.com/cdog-gh/gh_coding_test/tree/main/2/{i+1}"""
        img_script = f"""<img height="25px" width="25px" src="https://static.solved.ac/tier_small/{data["lv"]}.svg"></img>"""
        f.write(f"""|{ch}|{problem_title}|[바로가기]({problem_link})|[힌트]({hint_link})| {img_script} |\n""")

    from datetime import datetime
    from datetime import timezone
    f.write(f"\n마지막 업데이트 날짜 : {str(datetime.now(timezone.utc)).replace('+00:00', 'Z')}")


with open("3/README.md", "w", encoding="utf8") as f:
    f.write(f"""## 3회 [바로 가기](https://www.acmicpc.net/contest/view/755)\n""")
    f.write(f"""1월 23일 13시부터 18시 10분까지 3회 코딩테스트가 열렸습니다.\n""")
    f.write(f"""\n""")
    f.write(f"""|문제 번호|제목|풀러 가기|힌트|난이도|\n""")
    f.write(f"""|:------:|:-------------:|:-----:|:-----:|:-----:|\n""")
    for i, data in enumerate(gh_3_data):
        ch = chr(ord('A') + i)
        problem_title = data["title"]
        problem_link = f"""https://www.acmicpc.net/problem/{data["problemNo"]}"""
        hint_link = f"""https://github.com/cdog-gh/gh_coding_test/tree/main/3/{i+1}"""
        img_script = f"""<img height="25px" width="25px" src="https://static.solved.ac/tier_small/{data["lv"]}.svg"></img>"""
        f.write(f"""|{ch}|{problem_title}|[바로가기]({problem_link})|[힌트]({hint_link})| {img_script} |\n""")

    from datetime import datetime
    from datetime import timezone
    f.write(f"\n마지막 업데이트 날짜 : {str(datetime.now(timezone.utc)).replace('+00:00', 'Z')}")


with open("4/README.md", "w", encoding="utf8") as f:
    f.write(f"""## 4회 [바로 가기](https://www.acmicpc.net/contest/view/819)\n""")
    f.write(f"""6월 6일 13시부터 18시 00분까지 4회 코딩테스트가 열렸습니다.\n""")
    f.write(f"""\n""")
    f.write(f"""|문제 번호|제목|풀러 가기|힌트|난이도|\n""")
    f.write(f"""|:------:|:-------------:|:-----:|:-----:|:-----:|\n""")
    for i, data in enumerate(gh_4_data):
        ch = chr(ord('A') + i)
        problem_title = data["title"]
        problem_link = f"""https://www.acmicpc.net/problem/{data["problemNo"]}"""
        hint_link = f"""https://github.com/cdog-gh/gh_coding_test/tree/main/4/{i+1}"""
        img_script = f"""<img height="25px" width="25px" src="https://static.solved.ac/tier_small/{data["lv"]}.svg"></img>"""
        f.write(f"""|{ch}|{problem_title}|[바로가기]({problem_link})|[힌트]({hint_link})| {img_script} |\n""")

    from datetime import datetime
    from datetime import timezone
    f.write(f"\n마지막 업데이트 날짜 : {str(datetime.now(timezone.utc)).replace('+00:00', 'Z')}")


with open("5/README.md", "w", encoding="utf8") as f:
    f.write(f"""## 5회 [바로 가기](https://www.acmicpc.net/contest/view/946)\n""")
    f.write(f"""4월 2일 13시부터 18시 00분까지 5회 코딩테스트가 열렸습니다.\n""")
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


with open("6/README.md", "w", encoding="utf8") as f:
    f.write(f"""## 6회 [바로 가기](https://www.acmicpc.net/contest/view/1201)\n""")
    f.write(f"""12월 3일 19시부터 23시 00분까지 6회 코딩테스트가 열렸습니다.\n""")
    f.write(f"""\n""")
    f.write(f"""|문제 번호|제목|풀러 가기|힌트|난이도|\n""")
    f.write(f"""|:------:|:-------------:|:-----:|:-----:|:-----:|\n""")
    for i, data in enumerate(gh_6_data):
        ch = chr(ord('A') + i)
        problem_title = data["title"]
        problem_link = f"""https://www.acmicpc.net/problem/{data["problemNo"]}"""
        hint_link = f"""https://github.com/cdog-gh/gh_coding_test/tree/main/6/{i+1:02d}"""
        img_script = f"""<img height="25px" width="25px" src="https://static.solved.ac/tier_small/{data["lv"]}.svg"></img>"""
        f.write(f"""|{ch}|{problem_title}|[바로가기]({problem_link})|[힌트]({hint_link})| {img_script} |\n""")

    from datetime import datetime
    from datetime import timezone
    f.write(f"\n마지막 업데이트 날짜 : {str(datetime.now(timezone.utc)).replace('+00:00', 'Z')}")


with open("7/README.md", "w", encoding="utf8") as f:
    f.write(f"""## 7회 [바로 가기](https://www.acmicpc.net/contest/view/1415)\n""")
    f.write(f"""11월 30일 19시부터 23시 00분까지 7회 코딩테스트가 열렸습니다.\n""")
    f.write(f"""\n""")
    f.write(f"""|문제 번호|제목|풀러 가기|힌트|난이도|\n""")
    f.write(f"""|:------:|:-------------:|:-----:|:-----:|:-----:|\n""")
    for i, data in enumerate(gh_7_data):
        ch = chr(ord('A') + i)
        problem_title = data["title"]
        problem_link = f"""https://www.acmicpc.net/problem/{data["problemNo"]}"""
        hint_link = f"""https://github.com/cdog-gh/gh_coding_test/tree/main/7/{i+1:02d}"""
        img_script = f"""<img height="25px" width="25px" src="https://static.solved.ac/tier_small/{data["lv"]}.svg"></img>"""
        f.write(f"""|{ch}|{problem_title}|[바로가기]({problem_link})|[힌트]({hint_link})| {img_script} |\n""")

    from datetime import datetime
    from datetime import timezone
    f.write(f"\n마지막 업데이트 날짜 : {str(datetime.now(timezone.utc)).replace('+00:00', 'Z')}")