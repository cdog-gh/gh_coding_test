import requests
import copy
base = "https://solved.ac/api/v3"


# get gh problem
def build_gh_problem(target: list):
    try:
        res = requests.get(f"{base}/search/problem", params={
            "query": "가희"
        }).json()
        gh_problem_data = {
            k["problemId"]: {
                "lv": k["level"], "title": k["titleKo"], "problemNo": k["problemId"]
            } for k in res["items"]
        }

        build_data = [gh_problem_data.get(k, dict()) for k in target]
        temp_data = copy.deepcopy(build_data)
        for i, item in enumerate(temp_data):
            if item:
                continue
            problem_num = target[i]
            res = requests.get(f"{base}/search/problem", params={
                "query": problem_num
            }).json()
            build_data[i] = {
                "lv": res["items"][0]["level"],
                "title": res["items"][0]["titleKo"],
                "problemNo": res["items"][0]["problemId"]
            }
        return build_data
    except:
        assert False, "request error"
