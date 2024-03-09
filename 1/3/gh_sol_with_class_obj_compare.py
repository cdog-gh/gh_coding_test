import heapq
import sys


class Process:
    prio: int
    id: int
    time: int

    def __init__(self, prio: int, idx: int, time: int):
        self.prio = prio
        self.id = idx
        self.time = time
    
    def __lt__(self, other):
        if self.prio != other.prio:
            return self.prio > other.prio
        return self.id < other.id


T, n = map(int, sys.stdin.readline().split())
pq = []
for i in range(n):
    p_id, p_time, p_prio = map(int, sys.stdin.readline().split())
    heapq.heappush(pq, Process(prio=p_prio, time=p_time, idx=p_id))

for i in range(T):
    item = heapq.heappop(pq)
    p_time = item.time - 1
    p_prio = item.prio - 1
    p_id = item.id
    sys.stdout.write(f'{p_id}\n')
    if p_time != 0:
        heapq.heappush(pq, Process(prio=p_prio, time=p_time, idx=p_id))
