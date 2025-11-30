def min_to_string(m: int):
    hh = m // 60
    mm = m % 60
    if mm == 0:
        return f"{hh:02d}시"
    return f"{hh:02d}시 {mm:02d}분"
